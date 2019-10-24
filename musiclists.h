#ifndef MUSICLISTS_H
#define MUSICLISTS_H

#include <QObject>
#include <QString>
#include <QMap>

class MusicLists : public QObject
{
    Q_OBJECT

private:
    QMap< QString, QMap<QString, QString> > lists;
    QString activeList;

public:
    MusicLists();
    ~MusicLists();
    bool listExist(QString);
    void addList(QString);
    int count();
    void addMusicToList(QString, QString, QString);
    QStringList getMusicsFromList(QString);


signals:

public slots:
};

#endif // MUSICLISTS_H
