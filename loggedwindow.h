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

public:
    explicit LoggedWindow(Spofity *sptf, QWidget *parent = nullptr);
    ~LoggedWindow();

private slots:
    void on_lineEdit_2_textChanged(const QString &arg1);
    void on_pushButton_clicked();

private:
    Ui::LoggedWindow *ui;
};

#endif // LOGGEDWINDOW_H
