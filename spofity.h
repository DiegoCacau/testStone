#ifndef SPOFITY_H
#define SPOFITY_H
#include <QOAuth2AuthorizationCodeFlow>
#include <QOAuthHttpServerReplyHandler>
#include <QMainWindow>
#include <QNetworkReply>
#include <QObject>
#include <secretkeys.h>

#include <musiclists.h>


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
    QStringList getMusicsFromList(QString);

    // remove music from playlist
    bool removeMusic(QString, QString);

    // return music url using it's id
    void addMusicUrl(QString);

    QList<QMediaContent> getMediaFromList(QString);

    void playMusic(QString);

private:
    void login();

private slots:
    // change connection status
    void authStatusChanged(QAbstractOAuth::Status status);
    void granted();

signals:
   void openAfterLogin();
};

#endif // SPOFITY_H
