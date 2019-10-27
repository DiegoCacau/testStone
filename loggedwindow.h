#ifndef LOGGEDWINDOW_H
#define LOGGEDWINDOW_H

#include <QWidget>
#include <QCompleter>
#include <spofity.h>
#include <QStringListModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMessageBox>
#include "ui_loggedwindow.h"
#include <QAbstractItemView>
#include <QModelIndex>
#include <QWidget>

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
    QMessageBox msgBox;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QString playerStatus;
    QStringListModel* musicsModel;
    QString selected;

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

    // stop player
    void on_pushButton_6_clicked();

    // update elapsed music time
    void positionChangedByPlayer(qint64);

    // update music position
    void positionChangedByUser(int);

    // update music label and listview row based on playing music
    void updateMusicPlaying(int);

    // change playlist to next music
    void on_pushButton_10_clicked();

    // change playlist to previous music
    void on_pushButton_9_clicked();

    // display an warning
    void showWarningMessage(QString);

    // stop player
    void stopPlayer();

    // change window name
    void updateWindowName();

    // update selected music name
    void completerSelected(const QString &index);

private:
    Ui::LoggedWindow *ui;
};

#endif // LOGGEDWINDOW_H
