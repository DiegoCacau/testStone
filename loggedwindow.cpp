#include "loggedwindow.h"
#include "ui_loggedwindow.h"
#include <QAbstractItemView>

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

        this->ui->listView->setCurrentIndex(index);
    }
}
