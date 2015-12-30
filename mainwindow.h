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
    void load_playlist();
    void continue_playing();
    void keyPressEvent(QKeyEvent *);
    void fill_genders();
    void fill_authors();
    void fill_songs();

public slots:
    void play_song();
    void on_player_positionChanged(qlonglong);
    void on_player_stateChanged();
    void coin_inserted();
    void on_gender_changed(int);
    void on_author_changed(int);

private:
    Ui::MainWindow *ui;
    RockoSettings settings;
    QMediaPlayer* player;
    QMediaPlayer* effects_player;
    QList<QString> playlist;
    QList<int> song_ids;
    QQueue<int> song_data;

    int creditos;
    PlaylistLoader playlist_loader;

    void moveListIndex(QListWidget*, bool);
};

#endif // MAINWINDOW_H
