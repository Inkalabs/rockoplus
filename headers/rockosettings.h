#ifndef ROCKOSETTINGS_H
#define ROCKOSETTINGS_H

#include <QString>

class RockoSettings
{
public:
    RockoSettings();
    QString getCoinInsertedSound();
    QString getSongSelectedSound();
    QString getViewerPlaceholder();
    QString getBackgroundImage();
    QString getDatabasePath();
};

#endif // ROCKOSETTINGS_H
