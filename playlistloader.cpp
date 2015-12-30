#include "playlistloader.h"



PlaylistLoader::PlaylistLoader(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(settings.getDatabasePath());
    db.open();
}

QList<QString> PlaylistLoader::get_genders(){
    QSqlQuery q;
    q.exec(QLatin1String("Select gender from songs group by gender;"));
    QList<QString> results;
    while(q.next()){
        results.append(q.value(0).toString());
    }
    return results;
}

QList<QString> PlaylistLoader::get_authors(){

    QSqlQuery q;
    q.exec(QLatin1String("Select author from songs group by author;"));
    QList<QString> results;
    while(q.next()){
        results.append(q.value(0).toString());
    }
    return results;
}

QList<QString> PlaylistLoader::get_authors_by_gender(QString gender){
    QSqlQuery q;
    QString query("Select author from songs where gender = '"+ gender +"'group by author;");
    q.exec(query);
    QList<QString> results;
    while(q.next()){
        results.append(q.value(0).toString());
    }
    return results;
}

QList<Song> PlaylistLoader::get_songs_by_author_gender(QString author, QString gender){
    QSqlQuery q;
    QString query("Select name, gender, author, path, id from songs where gender = '"+ gender +"' and author = '"+ author +"';");
    q.exec(query);
    QList<Song> results;
    while(q.next()){
        Song r;
        r.name = q.value("name").toString();
        r.gender = q.value("gender").toString();
        r.author = q.value("author").toString();
        r.path = q.value("path").toString();
        r.id = q.value("id").toInt();
        results.append(r);
    }
    return results;
}

Song PlaylistLoader::read_song(int id){
    QSqlQuery q;
    q.exec("Select name, gender, author, path, id from songs where id = '"+ QString::number(id) +"';");

    while(q.next()){
        Song r;
        r.name = q.value("name").toString();
        r.gender = q.value("gender").toString();
        r.author = q.value("author").toString();
        r.path = q.value("path").toString();
        r.id = q.value("id").toInt();
        return r;
    }
}


