#ifndef SPOFITY_H
#define SPOFITY_H
#include <QOAuth2AuthorizationCodeFlow>
#include <QOAuthHttpServerReplyHandler>
#include <QMainWindow>
#include <QNetworkReply>
#include <QObject>
#include <secretkeys.h>


class Spofity: public QObject
{
    Q_OBJECT

private:
    QOAuth2AuthorizationCodeFlow connection;
    bool isLogged;
    QString token;
    QString username;
    QList< QMap< QString, QMap<QString, QString> > > musicList;

public:
    Spofity();
    ~Spofity();
    void grant();
    QOAuth2AuthorizationCodeFlow* getConnection();
    void setToken(QString);
    void getUserData();
    QStringList searchMusic(QString);

private:
    void login();

private slots:
    void authStatusChanged(QAbstractOAuth::Status status);
    void granted();

signals:
   void openAfterLogin();
};

#endif // SPOFITY_H
