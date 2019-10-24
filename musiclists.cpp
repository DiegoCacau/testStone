#include "musiclists.h"
#include <QDebug>

MusicLists::MusicLists()
{

}

MusicLists::~MusicLists(){

}


bool MusicLists::listExist(QString listName){
    if(this->lists.contains(listName))
        return true;

    return false;
}

//levantar warning caso lista já exista
void MusicLists::addList(QString listName){
    if(!this->listExist(listName)){
        QMap<QString, QString> musics;
        QMap< QString, QMap<QString, QString> > list;
        this->lists.insert(listName, musics);
    }

    //qDebug() << this->lists;
}

int MusicLists::count(){
    return this->lists.count();
}

void MusicLists::addMusicToList(QString listName, QString id, QString music){
    if(this->listExist(listName)){
        this->lists.find(listName)->insert(id, music);
    }
    qDebug()<<this->lists;
}

QStringList MusicLists::getMusicsFromList(QString listName){

   QStringList musicList;
    QMap<QString, QString>::iterator i;
    for (i = this->lists.find(listName)->begin(); i != this->lists.find(listName)->end(); ++i){
        musicList << i.value();
    }

    return musicList;
}
