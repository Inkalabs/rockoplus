#include "headers/song.h"

Song::Song(){
    id = 0;
}

Song::Song(const Song& p){
    name = p.name;
    id = p.id;
    path = p.path;
    author = p.author;
    gender = p.gender;
}

Song& Song::operator =(const Song& p){
    name = p.name;
    id = p.id;
    path = p.path;
    author = p.author;
    gender = p.gender;
    return *this;
}
