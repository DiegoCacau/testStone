#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <spofity.h>
#include "loggedwindow.h"
#include "ui_mainwindow.h"
#include"spofity.h"
#include <QtNetworkAuth>
#include <QJsonDocument>
#include <QDesktopServices>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // call login method
    void on_pushButton_clicked();

    // change window
    void openLoggedWindow();

private:
    Ui::MainWindow *ui;
    Spofity *sptf;
    LoggedWindow *loggedWindow;

public:
    // Although it is not safe this method is plublic for make it easy to test LoggedWindow object
    LoggedWindow* getLoggegWindow();

signals:
   // signal to make it easy to test this app
   void hidding();
};
#endif // MAINWINDOW_H
