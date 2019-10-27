#include "loggedwindow.h"


LoggedWindow::LoggedWindow(Spofity *sptf, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoggedWindow)
{
    this->ui->setupUi(this);
    this->sptf = sptf;

    this->playerStatus = "pause";

    this->listNames = new QStringListModel(this);
    this->ui->listView->setModel(this->listNames);
    this->ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->musicNames = new QStringListModel(this);
    this->ui->listView_2->setModel(this->musicNames);
    this->ui->listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->activeList = new QStringListModel(this);
    this->ui->listView_3->setModel(this->activeList);
    this->ui->listView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->player = new QMediaPlayer(this);
    this->playlist = new QMediaPlaylist(this->player);
    this->player->setPlaylist(this->playlist);

    QWidget* w = this->ui->tabWidget->findChild<QWidget*>("tab_2");
    this->ui->tabWidget->setCurrentWidget(w);

    connect(this->player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChangedByPlayer(qint64)));
    connect(this->ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(positionChangedByUser(int)));
    connect(this->playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(updateMusicPlaying(int)));
    connect(this->sptf, &Spofity::openAfterLogin, this, &LoggedWindow::updateWindowName);

    this->ui->horizontalSlider->setRange(0,1000);

    this->musicsModel = new QStringListModel();
    this->completer = new QCompleter(this->musicsModel, this);
    this->completer->setCaseSensitivity(Qt::CaseInsensitive);
    this->completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    this->ui->lineEdit_2->setCompleter(this->completer);
    connect(this->completer, SIGNAL(activated(const QString &)), this, SLOT(completerSelected(const QString &)));
    connect(this->completer, SIGNAL(highlighted(const QString &)), this, SLOT(completerSelected(const QString &)));
}

LoggedWindow::~LoggedWindow()
{
    delete this->completer;
    delete this->listNames;
    delete this->musicNames;
    delete this->activeList;
    delete this->player;
    delete this->ui;
}

void LoggedWindow::on_lineEdit_2_textChanged(const QString &arg1)
{

    if(!this->selectedList.isValid()){
        this->ui->lineEdit_2->clear();

        this->showWarningMessage("Antes de continuar, crie e selecione uma playlist.");
    }


    if(arg1.size() > 2){
        musicsModel->setStringList(this->sptf->searchMusic(arg1));
    }
}

void LoggedWindow::on_pushButton_clicked()
{
    QString name = this->ui->lineEdit->text();

    if(name.size() < 1){
        this->showWarningMessage("Preencha o campo com o nome da playlist.");
        return;
    }

    if(this->sptf->addList(name)){
        this->listNames->insertRow(this->listNames->rowCount());
        QModelIndex index = this->listNames->index(this->listNames->rowCount() - 1);
        listNames->setData(index, name);

        this->ui->lineEdit->clear();
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
        this->musicNames->insertRow(this->musicNames->rowCount());
        QModelIndex index = this->musicNames->index(this->musicNames->rowCount() - 1);
        this->musicNames->setData(index, name);
    }
}

void LoggedWindow::on_pushButton_3_clicked()
{
    QString name = this->ui->lineEdit_2->text();

    QStringList auxList = this->musicNames->stringList();

    if(this->selected != name){
        this->showWarningMessage("Música não encontrada. Tente fazer nova busca.");
        return;
    }

    if(this->selectedList.isValid() && !auxList.contains(name)){


       this->sptf->addMusicToList(this->listNames->itemData(this->selectedList)[0].toString(), name);

        this->musicNames->insertRow(this->musicNames->rowCount());
        QModelIndex index = this->musicNames->index(this->musicNames->rowCount() - 1);
        this->musicNames->setData(index, name);

        this->ui->lineEdit_2->clear();
    }
}


void LoggedWindow::on_pushButton_7_clicked()
{
    this->selectedList = this->ui->listView->currentIndex();

    if(!this->selectedList.isValid()){
        this->showWarningMessage("Antes de continuar, crie e selecione uma playlist.");
        return;
    }

    QString rowValue = this->listNames->itemData(this->selectedList)[0].toString();
    QStringList musicsNames = this->sptf->getMusicsFromList(rowValue);

    this->musicNames->setStringList( QStringList{} );

    for ( const auto& name : musicsNames  )
    {
        this->musicNames->insertRow(this->musicNames->rowCount());
        QModelIndex index = this->musicNames->index(this->musicNames->rowCount() - 1);
        this->musicNames->setData(index, name);
    }
}

void LoggedWindow::on_pushButton_2_clicked()
{
    this->selectedList = this->ui->listView->currentIndex();

    if(!this->selectedList.isValid()){
        this->showWarningMessage("Antes de continuar, crie e selecione uma playlist.");
        return;
    }

    QString rowValue = this->listNames->itemData(this->selectedList)[0].toString();
    QStringList musicsNames = this->sptf->getMusicsFromList(rowValue);

    this->activeList->setStringList( QStringList{} );

    for ( const auto& name : musicsNames  )
    {
        this->activeList->insertRow(this->activeList->rowCount());
        QModelIndex index = this->activeList->index(this->activeList->rowCount() - 1);
        this->activeList->setData(index, name);
    }

    QList<QMediaContent> content = this->sptf->getMediaFromList(rowValue);
    playlist->addMedia(content);

    QWidget* w = this->ui->tabWidget->findChild<QWidget*>("tab_3");
    this->ui->tabWidget->setCurrentWidget(w);

    this->player->play();
}

void LoggedWindow::on_listView_3_clicked(const QModelIndex &index)
{
    this->playlist->setCurrentIndex(index.row());

}


void LoggedWindow::on_pushButton_4_clicked()
{
    if(this->ui->listView_2->currentIndex().isValid()){
        QString musicName = this->musicNames->itemData(this->ui->listView_2->currentIndex())[0].toString();
         QString listName = this->listNames->itemData(this->selectedList)[0].toString();

        if(this->sptf->removeMusic(listName, musicName)){
            this->musicNames->removeRow(this->ui->listView_2->currentIndex().row());

            QStringList musicsNames = this->musicNames->stringList();
            this->activeList->setStringList( QStringList{} );

            for ( const auto& name :musicsNames  )
            {
                this->activeList->insertRow(this->activeList->rowCount());
                QModelIndex index = this->activeList->index(this->activeList->rowCount() - 1);
                this->activeList->setData(index, name);
            }

            this->stopPlayer();
        }
    }
}

void LoggedWindow::on_pushButton_6_clicked()
{
    this->stopPlayer();
}

void LoggedWindow::on_pushButton_5_clicked()
{
    if(!this->selectedList.isValid()){
        this->showWarningMessage("Antes de continuar, crie e selecione uma playlist.");
        return;
    }

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
      this->ui->horizontalSlider->setValue(currentPosition);
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
    if(this->musicNames->stringList().size() > index && index >= 0){
        this->ui->label_3->setText(this->musicNames->stringList().at(index));

        this->ui->listView_3->setCurrentIndex(this->activeList->index(index));
    }
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


void LoggedWindow::showWarningMessage(QString message){
    this->msgBox.setText(message);
    this->msgBox.exec();
    return;
}

void LoggedWindow::stopPlayer(){
    this->player->stop();
    this->playerStatus = "pause";
    this->ui->pushButton_5->setText("Tocar");
    this->ui->label_4->clear();
    this->ui->label_3->clear();
}

void LoggedWindow::updateWindowName(){
    this->setWindowTitle("Playlists de " + this->sptf->getUserName());
}

void LoggedWindow::completerSelected(const QString &name){
    if(!name.isEmpty())
        this->selected = name;
}
