#ifndef LOGGEDWINDOW_H
#define LOGGEDWINDOW_H

#include <QWidget>
#include <QCompleter>
#include <spofity.h>

namespace Ui {
class LoggedWindow;
}

class LoggedWindow : public QWidget
{
    Q_OBJECT
    QCompleter *completer;
    Spofity *sptf;

public:
    explicit LoggedWindow(Spofity *sptf, QWidget *parent = nullptr);
    ~LoggedWindow();

private slots:
    void on_lineEdit_2_textChanged(const QString &arg1);

private:
    Ui::LoggedWindow *ui;
};

#endif // LOGGEDWINDOW_H
