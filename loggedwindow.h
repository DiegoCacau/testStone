#ifndef LOGGEDWINDOW_H
#define LOGGEDWINDOW_H

#include <QWidget>
#include <QCompleter>
#include <spofity.h>
#include <QStringListModel>

namespace Ui {
class LoggedWindow;
}

class LoggedWindow : public QWidget
{
    Q_OBJECT
    QCompleter *completer;
    Spofity *sptf;
    QStringListModel *listNames;
    QStringListModel *musicNames;
    QModelIndex selectedList;

public:
    explicit LoggedWindow(Spofity *sptf, QWidget *parent = nullptr);
    ~LoggedWindow();

private slots:
    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_pushButton_clicked();
    void on_listView_clicked(const QModelIndex &index);
    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::LoggedWindow *ui;
};

#endif // LOGGEDWINDOW_H
