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
    effectsPlayer = new QMediaPlayer;
    this->loadPlaylist();
    this->ui->progress->setMaximum(100);
    this->ui->progress->setMinimum(0);
    this->ui->progress->setValue(0);
    player->setVolume(100);

    QObject::connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(on_player_positionChanged(qlonglong)));
    QObject::connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(on_player_stateChanged()));
    this->ui->webView->setUrl(QUrl::fromLocalFile(settings.getViewerPlaceholder()));

    this->setStyleSheet("QMainWindow {background-image: url('"+settings.getBackgroundImage()+"');}");
    this->fillGenders();
    this->ui->listGenders->setCurrentRow(0);

}

void MainWindow::fillGenders(){
    QList<QString> results = playlistLoader.getGenders();
    QList<QString>::iterator it = results.begin();

    for(; it != results.end(); it++){
        this->ui->listGenders->addItem(*it);
    }

}

void MainWindow::on_gender_changed(int row){
    if (this->ui->listGenders->count() == 0)
        return;
    this->ui->authorsList->blockSignals(true);
    this->fillAuthors();
    this->fillSongs();
}

void MainWindow::fillAuthors(){
    QList<QString> results = playlistLoader.getAuthorsByGender(
                this->ui->listGenders->currentItem()->text());

    QList<QString>::iterator it = results.begin();
    this->ui->authorsList->clear();
    for(; it != results.end(); it++){
        this->ui->authorsList->addItem(*it);
    }
    this->ui->authorsList->setCurrentRow(0);
    this->ui->authorsList->blockSignals(false);

}

void MainWindow::on_author_changed(int a){
    if (this->ui->authorsList->count() == 0){
        return;
    }
    this->fillSongs();
}

void MainWindow::fillSongs(){

    if (this->ui->authorsList->count() == 0)
        return;

    if (this->ui->listGenders->count() == 0)
        return;

    this->ui->availableMusic->clear();


    QList<Song> results = playlistLoader.getSongsByAuthorGender(
        this->ui->authorsList->currentItem()->text(),
        this->ui->listGenders->currentItem()->text());

    songIds.clear();

    QList<Song>::iterator it = results.begin();
    for(; it != results.end(); it++){
        this->ui->availableMusic->addItem(it->name);
        songIds.append(it->id);
    }
    this->ui->availableMusic->setCurrentRow(0);

}

void MainWindow::on_player_positionChanged(qlonglong position){
    qlonglong duration = this->player->duration();
    this->ui->progress->setValue(position*100/duration);
}


void MainWindow::on_player_stateChanged(){
    if (this->player->state() == this->player->StoppedState){
        this->continuePlaying();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadPlaylist(){

    QList<QString>::iterator it;
    for (it = this->playlist.begin(); it != this->playlist.end(); it++){
        this->ui->availableMusic->addItem(*it);
    }
    this->ui->availableMusic->setCurrentRow(0);

}

void MainWindow::coinInserted(){
    effectsPlayer->stop();
    effectsPlayer->setMedia(QUrl::fromLocalFile(settings.getCoinInsertedSound()));
    effectsPlayer->play();
    creditos += 3;
    this->ui->creditosLabel->setText(QString::number(creditos));
}

void MainWindow::continuePlaying(){
    if (this->songData.isEmpty())
        return;
    if (player->state() == player->StoppedState){
        this->ui->currentPlaylist->takeItem(0);
        Song s = playlistLoader.readSong(songData.dequeue());
        player->setMedia(QUrl::fromLocalFile(s.path));
        player->play();
        this->ui->currentSongLabel->setText(s.author+": "+s.name);
    }
}

void MainWindow::playSong(){
    if (creditos <= 0)
        return;
    creditos -= 1;
    this->ui->creditosLabel->setText(QString::number(creditos));

    effectsPlayer->stop();
    effectsPlayer->setMedia(QUrl::fromLocalFile(settings.getSongSelectedSound()));
    effectsPlayer->play();


    int selectedPosition = this->ui->availableMusic->currentRow();

    Song s = playlistLoader.readSong(songIds[selectedPosition]);

    this->ui->currentPlaylist->addItem(s.author + ": " + s.name);

    songData.enqueue(songIds[selectedPosition]);
    this->continuePlaying();
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
        this->playSong();
        return;
    }
    // insert coin
    if(e->key() == Qt::Key_Left){
        this->moveListIndex(this->ui->listGenders, true);
        return;
    }
    if(e->key() == Qt::Key_Right){
        this->moveListIndex(this->ui->listGenders, false);
        return;
    }
    if(e->key() == Qt::Key_Up){
        this->moveListIndex(this->ui->authorsList, false);
    }
    if(e->key() == Qt::Key_Down){
        this->moveListIndex(this->ui->authorsList, true);
    }
    if(e->key() == Qt::Key_S){
        this->moveListIndex(this->ui->availableMusic, false);
    }
    if(e->key() == Qt::Key_X){
        this->moveListIndex(this->ui->availableMusic, true);
    }
    if(e->key() == Qt::Key_Shift){
        this->coinInserted();
        return;
    }

    QMainWindow::keyPressEvent(e);
}
