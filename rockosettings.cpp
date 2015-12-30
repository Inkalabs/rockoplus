#include "rockosettings.h"

RockoSettings::RockoSettings(){

}

QString RockoSettings::getCoinInsertedSound(){
    return "/Users/jose/Downloads/chela-destapar.mp3";
}


QString RockoSettings::getSongSelectedSound(){
    return "/Users/jose/Downloads/chela-sirviendo.mp3";
}

QString RockoSettings::getViewerPlaceholder(){
    return "/Users/jose/Downloads/pilsen.png";
}

QString RockoSettings::getBackgroundImage(){
    return "/Users/jose/Downloads/bg.jpg";
}

QString RockoSettings::getDatabasePath(){
    return "/Users/jose/build-rockoplus-Desktop_Qt_5_5_1_clang_64bit-Debug/database.db";
}
