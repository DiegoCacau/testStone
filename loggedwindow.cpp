#include "loggedwindow.h"
#include "ui_loggedwindow.h"
#include <QAbstractItemView>
#include <QModelIndex>

#include <QDebug>

LoggedWindow::LoggedWindow(Spofity *sptf, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoggedWindow)
{
    ui->setupUi(this);
    this->sptf = sptf;

    listNames = new QStringListModel(this);
    this->ui->listView->setModel(listNames);
    this->ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    musicNames = new QStringListModel(this);
    this->ui->listView_2->setModel(musicNames);
    this->ui->listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

        //this->ui->listView->setCurrentIndex(index);
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


void LoggedWindow::on_pushButton_5_clicked()
{
    this->sptf->playMusic("ss");
}
