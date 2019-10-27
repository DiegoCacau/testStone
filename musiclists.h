#ifndef MUSICLISTS_H
#define MUSICLISTS_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QMediaContent>

struct Music{
    QString id;
    QString name;
    QString url;
};

class MusicLists : public QObject
{
    Q_OBJECT

private:
    QMap< QString, QList<Music*> > lists;
    QList<Music*> musics;

public:
    MusicLists();
    ~MusicLists();

    // check if playlist exist by its name
    bool listExist(QString);

    Music* musicExists(QString);

    // create new playlist
    void addList(QString);

    // return playlist count
    int count();

    // add music to playlist
    void addMusicToList(QString, QString, QString);

    // return musics from playlist
    QStringList getMusicsFromList(QString);

    // add url to music
    void addUrlToMusic(QString, QString);

    // remove music from list
    bool removeMusic(QString, QString);

    // Return musics from list
    QList<QMediaContent> getMediaFromList(QString);


signals:

public slots:
};

#endif // MUSICLISTS_H
