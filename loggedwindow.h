#ifndef LOGGEDWINDOW_H
#define LOGGEDWINDOW_H

#include <QWidget>
#include <QCompleter>
#include <spofity.h>
#include <QStringListModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>

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
    QStringListModel *activeList;
    QModelIndex selectedList;

    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QString playerStatus;

public:
    explicit LoggedWindow(Spofity *sptf, QWidget *parent = nullptr);
    ~LoggedWindow();

private slots:
    // on lineEdit change call API and search musics
    void on_lineEdit_2_textChanged(const QString &arg1);

    // create new playlist
    void on_pushButton_clicked();

    // change playlist
    void on_listView_clicked(const QModelIndex &index);

    // add music to playlist
    void on_pushButton_3_clicked();

    // play music
    void on_pushButton_5_clicked();

    // open playlist to edit
    void on_pushButton_7_clicked();

    // play list
    void on_pushButton_2_clicked();

    // change music at player tab
    void on_listView_3_clicked(const QModelIndex &index);

    // remove selected music from playlist
    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void positionChangedByPlayer(qint64);

    void positionChangedByUser(int);

    void updateMusicPlaying(int);

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::LoggedWindow *ui;
};

#endif // LOGGEDWINDOW_H
