#ifndef PLAYLISTLOADER_H
#define PLAYLISTLOADER_H

#include <QList>
#include <QString>
#include <QtSql>

#include "rockosettings.h"
#include "song.h"

class PlaylistLoader
{
public:
    PlaylistLoader();
    QList<QString> get_genders();
    QList<QString> get_authors();
    QList<QString> get_authors_by_gender(QString gender);
    QList<Song> get_songs_by_author_gender(QString, QString);
    Song read_song(int);
private:
    RockoSettings settings;
    QSqlDatabase createConnection();

};

#endif // PLAYLISTLOADER_H
