#include "mainwindow.h"
#include "ui_mainwindow.h"

#include"spofity.h"
#include <QtNetworkAuth>
#include <QJsonDocument>
#include <QDesktopServices>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    sptf = new Spofity();

    loggedWindow = new LoggedWindow(sptf);

    QObject::connect(sptf, &Spofity::openAfterLogin, this, &MainWindow::openLoggedWindow);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->sptf->grant();
}

void MainWindow::openLoggedWindow(){
    hide();
    loggedWindow->show();
}
