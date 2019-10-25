#include "spofity.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QDesktopServices>
#include <QUrlQuery>
#include <QJsonArray>
#include <QVariantMap>
#include <QMediaPlayer>

#include <QDebug>

Spofity::Spofity()
{
    this->isLogged = false;
    this->login();
    this->lists = new MusicLists();


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

    this->getUserData();

    emit(this->openAfterLogin());
}

void Spofity::getUserData(){
    QUrl u ("https://api.spotify.com/v1/me");

    auto reply = this->connection.get(u);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            return;
        }
        const auto data = reply->readAll();

        const auto document = QJsonDocument::fromJson(data);
        const auto root = document.object();
        username = root.value("display_name").toString();

        reply->deleteLater();
    });
}

QStringList Spofity::searchMusic(QString word){
    QUrlQuery url ("https://api.spotify.com/v1/search?type=track&limit=20&q=" + word);

    auto reply = this->connection.get(url.toString());
    tempList.clear();


    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            return;
        }
        const auto data = reply->readAll();

        const auto document = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = document.object();
        QJsonObject jsonSubObject = jsonObject["tracks"].toObject();
        QJsonArray jsonArray = jsonSubObject["items"].toArray();

        wordList.clear();
        tempList.clear();

        foreach (const QJsonValue & value, jsonArray) {
            QJsonObject obj = value.toObject();
            QJsonArray artist = obj["artists"].toArray();
            QJsonObject ob = artist[0].toObject();

            wordList << obj["name"].toString() + " - " + ob["name"].toString();
            tempList.insert( obj["name"].toString() + " - " + ob["name"].toString(), obj["id"].toString());
        }

        reply->deleteLater();
    });

    return wordList;
}

bool Spofity::addList(QString listName){
    int countBefore = this->lists->count();
    this->lists->addList(listName);
    int countAfter = this->lists->count();

    if(countBefore < countAfter){
        return true;
    }

    return false;
}

void Spofity::addMusicToList(QString musicList, QString music){
    this->lists->addMusicToList(musicList, this->tempList.value(music), music);

    this->addMusicUrl(this->tempList.value(music));
}

QStringList Spofity::getMusicsFromList(QString listName){

    return this->lists->getMusicsFromList(listName);
}

//void Spofity::playMusic(QString id){
//    QUrl u ("https://api.spotify.com/v1/tracks/" + id);

//    auto reply = this->connection.get(u);

//    connect(reply, &QNetworkReply::finished, [=]() {
//        if (reply->error() != QNetworkReply::NoError) {
//            return;
//        }
//        const auto data = reply->readAll();
//        const auto document = QJsonDocument::fromJson(data);
//        QJsonObject jsonObject = document.object();

//        qDebug()<<jsonObject["preview_url"].toString();

//        QMediaPlayer* player = new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
//        player->setMedia(QUrl(jsonObject["preview_url"].toString()));
//        player->setVolume(80);
//        player->play();

//        reply->deleteLater();
//    });

//}

void Spofity::addMusicUrl(QString id){
    if(this->musicsWithUrl.contains(id)){
        return;
    }

    QUrl u ("https://api.spotify.com/v1/tracks/" + id);

    auto reply = this->connection.get(u);

    QString url;

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            return;
        }
        const auto data = reply->readAll();
        const auto document = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = document.object();

        //qDebug()<<jsonObject["preview_url"].toString();

        this->lists->addUrlToMusic(id, jsonObject["preview_url"].toString());

        reply->deleteLater();
    });

}

bool Spofity::removeMusic(QString listName, QString musicName){
    return this->lists->removeMusic(listName,musicName);
}

QList<QMediaContent> Spofity::getMediaFromList(QString listName){
    return this->lists->getMediaFromList(listName);
}
