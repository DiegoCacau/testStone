#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <spofity.h>
#include "loggedwindow.h"

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
    void on_pushButton_clicked();
    void openLoggedWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
