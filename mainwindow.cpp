#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QtGui>
#include <QMap>
#include <QString>
#include <QMediaPlayer>
#include <QNetworkProxyFactory>
#include <QMutex>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // load playlist

    player = new QMediaPlayer;
    effects_player = new QMediaPlayer;
    this->load_playlist();
    this->ui->progress->setMaximum(100);
    this->ui->progress->setMinimum(0);
    this->ui->progress->setValue(0);
    player->setVolume(100);

    QObject::connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(on_player_positionChanged(qlonglong)));
    QObject::connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(on_player_stateChanged()));
    this->ui->webView->setUrl(QUrl::fromLocalFile(settings.getViewerPlaceholder()));

    this->setStyleSheet("QMainWindow {background-image: url('"+settings.getBackgroundImage()+"');}");
    this->fill_genders();
    this->ui->list_genders->setCurrentRow(0);

}

void MainWindow::fill_genders(){
    QList<QString> results = playlist_loader.get_genders();
    QList<QString>::iterator it = results.begin();

    for(; it != results.end(); it++){
        this->ui->list_genders->addItem(*it);
    }

}

void MainWindow::on_gender_changed(int row){
    if (this->ui->list_genders->count() == 0)
        return;
    this->ui->authors_list->blockSignals(true);
    this->fill_authors();
    this->fill_songs();
}

void MainWindow::fill_authors(){
    QList<QString> results = playlist_loader.get_authors_by_gender(
                this->ui->list_genders->currentItem()->text());

    QList<QString>::iterator it = results.begin();
    this->ui->authors_list->clear();
    for(; it != results.end(); it++){
        this->ui->authors_list->addItem(*it);
    }
    this->ui->authors_list->setCurrentRow(0);
    this->ui->authors_list->blockSignals(false);

}

void MainWindow::on_author_changed(int a){
    if (this->ui->authors_list->count() == 0){
        return;
    }
    this->fill_songs();
}

void MainWindow::fill_songs(){

    if (this->ui->authors_list->count() == 0)
        return;

    if (this->ui->list_genders->count() == 0)
        return;

    this->ui->available_music->clear();


    QList<Song> results = playlist_loader.get_songs_by_author_gender(
        this->ui->authors_list->currentItem()->text(),
        this->ui->list_genders->currentItem()->text());

    song_ids.clear();

    QList<Song>::iterator it = results.begin();
    for(; it != results.end(); it++){
        this->ui->available_music->addItem(it->name);
        song_ids.append(it->id);
    }
    this->ui->available_music->setCurrentRow(0);

}

void MainWindow::on_player_positionChanged(qlonglong position){
    qlonglong duration = this->player->duration();
    this->ui->progress->setValue(position*100/duration);
}


void MainWindow::on_player_stateChanged(){
    if (this->player->state() == this->player->StoppedState){
        this->continue_playing();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_playlist(){

    QList<QString>::iterator it;
    for (it = this->playlist.begin(); it != this->playlist.end(); it++){
        this->ui->available_music->addItem(*it);
    }
    this->ui->available_music->setCurrentRow(0);

}

void MainWindow::coin_inserted(){
    effects_player->stop();
    effects_player->setMedia(QUrl::fromLocalFile(settings.getCoinInsertedSound()));
    effects_player->play();
    creditos += 3;
    this->ui->creditos_label->setText(QString::number(creditos));
}

void MainWindow::continue_playing(){
    if (this->song_data.isEmpty())
        return;
    if (player->state() == player->StoppedState){
        this->ui->current_playlist->takeItem(0);
        Song s = playlist_loader.read_song(song_data.dequeue());
        player->setMedia(QUrl::fromLocalFile(s.path));
        player->play();
        this->ui->current_song_label->setText(s.author+": "+s.name);
    }
}

void MainWindow::play_song(){
    if (creditos <= 0)
        return;
    creditos -= 1;
    this->ui->creditos_label->setText(QString::number(creditos));

    effects_player->stop();
    effects_player->setMedia(QUrl::fromLocalFile(settings.getSongSelectedSound()));
    effects_player->play();


    int selected_position = this->ui->available_music->currentRow();

    Song s = playlist_loader.read_song(song_ids[selected_position]);

    this->ui->current_playlist->addItem(s.author + ": " + s.name);

    song_data.enqueue(song_ids[selected_position]);
    this->continue_playing();
}

void MainWindow::moveListIndex(QListWidget* list, bool increase){
    int row = list->currentRow();
    if (increase){
        if (row == 0){
            row = list->count();
        }
        row -= 1;
    }
    else{
        row += 1;
        if (row == list->count()){
            row = 0;
        }
    }
    list->setCurrentRow(row);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Return){
        this->play_song();
        return;
    }
    // insert coin
    if(e->key() == Qt::Key_Left){
        this->moveListIndex(this->ui->list_genders, true);
        return;
    }
    if(e->key() == Qt::Key_Right){
        this->moveListIndex(this->ui->list_genders, false);
        return;
    }
    if(e->key() == Qt::Key_Up){
        this->moveListIndex(this->ui->authors_list, false);
    }
    if(e->key() == Qt::Key_Down){
        this->moveListIndex(this->ui->authors_list, true);
    }
    if(e->key() == Qt::Key_S){
        this->moveListIndex(this->ui->available_music, false);
    }
    if(e->key() == Qt::Key_X){
        this->moveListIndex(this->ui->available_music, true);
    }
    if(e->key() == Qt::Key_Shift){
        this->coin_inserted();
        return;
    }

    QMainWindow::keyPressEvent(e);
}
