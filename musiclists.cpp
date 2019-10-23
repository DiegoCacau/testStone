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

    qDebug() << this->lists;
}

int MusicLists::count(){
    return this->lists.count();
}
