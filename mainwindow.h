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
    Spofity *sptf;
    LoggedWindow *loggedWindow;

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
};
#endif // MAINWINDOW_H
