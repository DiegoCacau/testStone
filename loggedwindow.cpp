#include "loggedwindow.h"
#include "ui_loggedwindow.h"

#include <QDebug>

LoggedWindow::LoggedWindow(Spofity *sptf, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoggedWindow)
{
    ui->setupUi(this);
    this->sptf = sptf;
}

LoggedWindow::~LoggedWindow()
{
    delete ui;
}

void LoggedWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
//    qDebug() << arg1;
    if(arg1.size() > 2){
        this->sptf->searchMusic(arg1);
    }
}
