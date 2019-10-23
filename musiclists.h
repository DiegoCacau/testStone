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

public:
    MusicLists();
    ~MusicLists();
    bool listExist(QString);
    void addList(QString);
    int count();


signals:

public slots:
};

#endif // MUSICLISTS_H
