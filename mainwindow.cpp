#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    this->ui->setupUi(this);
    this->sptf = new Spofity();

    this->loggedWindow = new LoggedWindow(this->sptf);

    connect(this->sptf, &Spofity::openAfterLogin, this, &MainWindow::openLoggedWindow);

}

MainWindow::~MainWindow()
{
    delete this->sptf;
    delete this->loggedWindow;
    delete this->ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->sptf->grant();
}

void MainWindow::openLoggedWindow(){
    this->hide();
    this->loggedWindow->show();
}
