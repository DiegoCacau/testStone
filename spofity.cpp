#include "spofity.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDesktopServices>
#include <QUrlQuery>
#include <QJsonArray>
#include <QVariantMap>

#include <QDebug>

Spofity::Spofity()
{
    this->isLogged = false;
    this->login();

    connect(this->getConnection(), &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
             &QDesktopServices::openUrl);

    connect(this->getConnection(), &QOAuth2AuthorizationCodeFlow::statusChanged,
            this, &Spofity::authStatusChanged);

    connect(this->getConnection(), &QOAuth2AuthorizationCodeFlow::granted,
            this, &Spofity::granted);

}

Spofity::~Spofity(){

}


void Spofity::login(){
    auto replyHandler = new QOAuthHttpServerReplyHandler(8080, this);
    this->connection.setReplyHandler(replyHandler);
    this->connection.setAuthorizationUrl(QUrl("https://accounts.spotify.com/authorize"));
    this->connection.setAccessTokenUrl(QUrl("https://accounts.spotify.com/api/token"));
    this->connection.setClientIdentifier(clientId);
    this->connection.setClientIdentifierSharedKey(clientSecret);
    this->connection.setScope("user-read-private user-top-read playlist-read-private playlist-modify-public playlist-modify-private");
}

void Spofity::grant(){
    this->connection.grant();
}

QOAuth2AuthorizationCodeFlow *Spofity::getConnection(){
    return &this->connection;
}

void Spofity::setToken(QString token){
    this->token = token;
}

// aqui decidir quando abrir a outra janela
void Spofity::authStatusChanged(QAbstractOAuth::Status status)
{
    QString s;
    if (status == QAbstractOAuth::Status::Granted)
        s = "granted";

    if (status == QAbstractOAuth::Status::TemporaryCredentialsReceived) {
        s = "temp credentials";
    }

}

void Spofity::granted ()
{

    QString token = this->getConnection()->token();
    this->isLogged = true;
    qDebug() << token;

    this->getUserData();

    emit(this->openAfterLogin());
}

void Spofity::getUserData(){
    QUrl u ("https://api.spotify.com/v1/me");

    auto reply = this->connection.get(u);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            //ui->teOutput->appendPlainText(reply->errorString());
            return;
        }
        const auto data = reply->readAll();
        //ui->teOutput->appendPlainText(data);

        const auto document = QJsonDocument::fromJson(data);
        const auto root = document.object();
        username = root.value("display_name").toString();

        qDebug() << username;

        reply->deleteLater();
    });
}

QStringList Spofity::searchMusic(QString word){
    QUrlQuery url ("https://api.spotify.com/v1/search?type=track&limit=20&q=" + word);
    //url.addQueryItem("track", word);

    qDebug() << "\n\n" << url.toString(QUrl::FullyEncoded);
    auto reply = this->connection.get(url.toString());

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            return;
        }
        const auto data = reply->readAll();

        const auto document = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = document.object();
        QJsonObject jsonSubObject = jsonObject["tracks"].toObject();
        QJsonArray jsonArray = jsonSubObject["items"].toArray();

        foreach (const QJsonValue & value, jsonArray) {
            QJsonObject obj = value.toObject();
//            propertyNames.append(obj["PropertyName"].toString());
//            propertyKeys.append(obj["key"].toString());
            QJsonArray artist = obj["artists"].toArray();
            QJsonObject ob = artist[0].toObject();

            qDebug() << obj["name"].toString() << ob["name"].toString() << obj["id"].toString();
        }


        reply->deleteLater();
    });

    return QStringList();
}
