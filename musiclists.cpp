#include "musiclists.h"

MusicLists::MusicLists()
{

}

MusicLists::~MusicLists(){
    this->lists.clear();
    this->musics.clear();
}


bool MusicLists::listExist(QString listName){
    if(this->lists.contains(listName))
        return true;

    return false;
}

Music* MusicLists::musicExists(QString id){
    for ( int i=0; i<this->musics.count(); i++ ) {
        if(this->musics[0]->id == id)
            return this->musics[0];
    }

    return new Music();
}

void MusicLists::addList(QString listName){
    if(!this->listExist(listName)){
        QList<Music*> musics;
        this->lists.insert(listName, musics);
    }
}

int MusicLists::count(){
    return this->lists.count();
}

void MusicLists::addMusicToList(QString listName, QString id, QString name){
    Music *music = this->musicExists(id);
    if(music->id.isEmpty()){
        music->id = id;
        music->name = name;

        this->musics.push_back(music);
    }

    if(this->listExist(listName)){
        this->lists.find(listName)->push_back(music);
    }
}

QStringList MusicLists::getMusicsFromList(QString listName){

    QStringList musicList;
    QList<Music*> list = this->lists.find(listName).value();

    for ( auto music : list ) {
        musicList << music->name;
    }

    return musicList;
}

bool MusicLists::removeMusic(QString listName, QString musicName){
    if(this->listExist(listName)){

        QList<Music*> list = this->lists.find(listName).value();

        for(int i=0; i<list.count(); i++){
            if(list[i]->name == musicName){
                this->lists.find(listName).value().removeAt(i);
                return true;
            }
        }
    }

    return false;
}


void MusicLists::addUrlToMusic(QString id, QString url){
    for(int i=0; i<this->musics.count(); i++){
        if(this->musics[i]->id == id){
            this->musics[i]->url = url;
            return;
        }
    }
}

QList<QMediaContent> MusicLists::getMediaFromList(QString listName){
    QList<QMediaContent> content;

    QList<Music*> list = this->lists.find(listName).value();

    for(int i=0; i<list.count(); i++){
        content.push_back(QUrl(list[i]->url));
    }

    return content;

}
