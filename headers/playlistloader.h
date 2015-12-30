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
    QList<QString> getGenders();
    QList<QString> getAuthors();
    QList<QString> getAuthorsByGender(QString gender);
    QList<Song> getSongsByAuthorGender(QString, QString);
    Song readSong(int);
private:
    RockoSettings settings;
    QSqlDatabase createConnection();

};

#endif // PLAYLISTLOADER_H
