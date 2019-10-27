#ifndef SPOFITY_H
#define SPOFITY_H
#include <QOAuth2AuthorizationCodeFlow>
#include <QOAuthHttpServerReplyHandler>
#include <QMainWindow>
#include <QNetworkReply>
#include <QObject>
#include <secretkeys.h>
#include <musiclists.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDesktopServices>
#include <QUrlQuery>
#include <QJsonArray>
#include <QVariantMap>
#include <QMediaPlayer>



class Spofity: public QObject
{
    Q_OBJECT

private:
    QOAuth2AuthorizationCodeFlow connection;
    bool isLogged;
    QString token;
    QString username;
    QStringList wordList;
    MusicLists *lists;
    QMap<QString, QString> tempList;
    QList<QString> musicsWithUrl;

public:
    Spofity();
    ~Spofity();

    // grant connection
    void grant();

    // get connection
    QOAuth2AuthorizationCodeFlow* getConnection();

    // save token
    void setToken(QString);

    // get data from user
    void getUserData();

    // search musics at Spotify API
    QStringList searchMusic(QString);

    // check if playlist exists
    bool listExist(QString);

    // create playlist
    bool addList(QString);

    // add music to playlist
    void addMusicToList(QString, QString);

    // return QStringList with music names from given list
    QStringList getMusicsFromList(QString);

    // remove music from playlist
    bool removeMusic(QString, QString);

    // return music url using it's id
    void addMusicUrl(QString);

    // return username
    QString getUserName();

    // Return musics from list
    QList<QMediaContent> getMediaFromList(QString);


private:
    // do login
    void login();

private slots:
    // save token and call getUserData
    void granted();

signals:
   // signal to open LoggedWindow after login
   void openAfterLogin();
};

#endif // SPOFITY_H
