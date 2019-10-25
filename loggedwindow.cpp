#include "loggedwindow.h"
#include "ui_loggedwindow.h"
#include <QAbstractItemView>
#include <QModelIndex>
#include <QWidget>


#include <QDebug>

LoggedWindow::LoggedWindow(Spofity *sptf, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoggedWindow)
{
    ui->setupUi(this);
    this->sptf = sptf;

    this->playerStatus = "pause";

    listNames = new QStringListModel(this);
    this->ui->listView->setModel(listNames);
    this->ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    musicNames = new QStringListModel(this);
    this->ui->listView_2->setModel(musicNames);
    this->ui->listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    activeList = new QStringListModel(this);
    this->ui->listView_3->setModel(activeList);
    this->ui->listView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->player = new QMediaPlayer(this);
    this->playlist = new QMediaPlaylist(this->player);
    this->player->setPlaylist(this->playlist);

    connect(this->player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChangedByPlayer(qint64)));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(positionChangedByUser(int)));
    connect(this->playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(updateMusicPlaying(int)));
    this->ui->horizontalSlider->setRange(0,1000);


}

LoggedWindow::~LoggedWindow()
{
    delete ui;
}

void LoggedWindow::on_lineEdit_2_textChanged(const QString &arg1)
{

    if(arg1.size() > 2){
        completer = new QCompleter(this->sptf->searchMusic(arg1), this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
        ui->lineEdit_2->setCompleter(completer);
    }
}

void LoggedWindow::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();

    if(this->sptf->addList(name)){
        listNames->insertRow(listNames->rowCount());
        QModelIndex index = listNames->index(listNames->rowCount() - 1);
        listNames->setData(index, name);
    }
}

void LoggedWindow::on_listView_clicked(const QModelIndex &index)
{
    this->selectedList = index;

    QString rowValue = this->listNames->itemData(this->selectedList)[0].toString();
    QStringList musicsNames = this->sptf->getMusicsFromList(rowValue);

    this->musicNames->setStringList( QStringList{} );

    for ( const auto& name : musicsNames  )
    {
        musicNames->insertRow(musicNames->rowCount());
        QModelIndex index = musicNames->index(musicNames->rowCount() - 1);
        musicNames->setData(index, name);
    }
}

void LoggedWindow::on_pushButton_3_clicked()
{
    QString name = this->ui->lineEdit_2->text();

    QStringList auxList = musicNames->stringList();

    if(this->selectedList.isValid() && !auxList.contains(name)){


       this->sptf->addMusicToList(this->listNames->itemData(this->selectedList)[0].toString(), name);

        musicNames->insertRow(musicNames->rowCount());
        QModelIndex index = musicNames->index(musicNames->rowCount() - 1);
        musicNames->setData(index, name);
    }
}


void LoggedWindow::on_pushButton_7_clicked()
{
    this->selectedList = ui->listView->currentIndex();

    QString rowValue = this->listNames->itemData(this->selectedList)[0].toString();
    QStringList musicsNames = this->sptf->getMusicsFromList(rowValue);

    this->musicNames->setStringList( QStringList{} );

    for ( const auto& name : musicsNames  )
    {
        musicNames->insertRow(musicNames->rowCount());
        QModelIndex index = musicNames->index(musicNames->rowCount() - 1);
        musicNames->setData(index, name);
    }
}

void LoggedWindow::on_pushButton_2_clicked()
{
    this->selectedList = ui->listView->currentIndex();

    QString rowValue = this->listNames->itemData(this->selectedList)[0].toString();
    QStringList musicsNames = this->sptf->getMusicsFromList(rowValue);

    this->activeList->setStringList( QStringList{} );

    for ( const auto& name : musicsNames  )
    {
        activeList->insertRow(activeList->rowCount());
        QModelIndex index = activeList->index(activeList->rowCount() - 1);
        activeList->setData(index, name);
    }

    QList<QMediaContent> content = this->sptf->getMediaFromList(rowValue);
    playlist->addMedia(content);

    QWidget* w = this->ui->tabWidget->findChild<QWidget*>("tab_3");
    this->ui->tabWidget->setCurrentWidget(w);
}

void LoggedWindow::on_listView_3_clicked(const QModelIndex &index)
{
//    this->selectedList = index;

//    QString rowValue = this->listNames->itemData(this->selectedList)[0].toString();
//    QStringList musicsNames = this->sptf->getMusicsFromList(rowValue);

//    this->musicNames->setStringList( QStringList{} );

//    for ( const auto& name : musicsNames  )
//    {
//        musicNames->insertRow(musicNames->rowCount());
//        QModelIndex index = musicNames->index(musicNames->rowCount() - 1);
//        musicNames->setData(index, name);
//    }
}


void LoggedWindow::on_pushButton_4_clicked()
{
    if(ui->listView_2->currentIndex().isValid()){
        QString musicName = this->musicNames->itemData(ui->listView_2->currentIndex())[0].toString();
         QString listName = this->listNames->itemData(this->selectedList)[0].toString();

        if(this->sptf->removeMusic(listName, musicName)){
            musicNames->removeRow(ui->listView_2->currentIndex().row());
        }
    }
}

void LoggedWindow::on_pushButton_6_clicked()
{
    this->player->stop();
}

void LoggedWindow::on_pushButton_5_clicked()
{
    if(this->playerStatus == "pause"){
        this->player->play();
        this->playerStatus = "playing";
        this->ui->pushButton_5->setText("Pausar");
    }
    else{
        this->playerStatus = "pause";
        this->player->pause();
        this->ui->pushButton_5->setText("Tocar");
    }

}

void LoggedWindow::positionChangedByPlayer(qint64 position) {
  QString elapsedTime = "00:00";
  double duration = this->player->duration();
  int currentPosition = 0;

  if (duration > 0) {
    currentPosition = static_cast<int>((position / duration) * 1000);

    if (currentPosition >= 0 && currentPosition <= 1000) {
      ui->horizontalSlider->setValue(currentPosition);
    }

    int minutes = static_cast<int>(position / 60000);
    int seconds = static_cast<int>(position / 1000) - minutes * 60;
    elapsedTime = QString().sprintf("%02d:%02d", minutes, seconds);
  }

  this->ui->label_4->setText(elapsedTime);
}


void LoggedWindow::positionChangedByUser(int position) {
  qint64 duration = this->player->duration();
  int changedPosition = static_cast<int>((position / 1000.0) * duration);

  if (changedPosition > 0 && changedPosition <= duration) {
    this->player->setPosition(changedPosition);
  }
}

void LoggedWindow::updateMusicPlaying(int index){
    if(this->musicNames->stringList().size() > index && index >= 0)
        this->ui->label_3->setText(this->musicNames->stringList().at(index));
}

void LoggedWindow::on_pushButton_10_clicked()
{
    if(this->playlist->nextIndex() >= 0)
        this->playlist->next();
}

void LoggedWindow::on_pushButton_9_clicked()
{
    if(this->playlist->previousIndex() >= 0)
        this->playlist->previous();
}
