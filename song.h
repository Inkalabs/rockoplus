#ifndef SONG_H
#define SONG_H

#include <QString>

class Song
{
public:
    QString name;
    QString author;
    QString gender;
    QString path;
    int id;

    Song();
    Song(const Song &);

    Song& operator = (const Song&);

};

#endif // SONG_H
