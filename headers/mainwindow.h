#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rockosettings.h"
#include "playlistloader.h"

#include <QMainWindow>
#include <QMap>
#include <QString>
#include <QMediaPlayer>
#include <QQueue>
#include <QListWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadPlaylist();
    void continuePlaying();
    void keyPressEvent(QKeyEvent *);
    void fillGenders();
    void fillAuthors();
    void fillSongs();

public slots:
    void playSong();
    void coinInserted();

    void on_player_positionChanged(qlonglong);
    void on_player_stateChanged();
    void on_gender_changed(int);
    void on_author_changed(int);

private:
    Ui::MainWindow *ui;
    RockoSettings settings;
    QMediaPlayer* player;
    QMediaPlayer* effectsPlayer;
    QList<QString> playlist;
    QList<int> songIds;
    QQueue<int> songData;

    int creditos;
    PlaylistLoader playlistLoader;

    void moveListIndex(QListWidget*, bool);
};

#endif // MAINWINDOW_H
