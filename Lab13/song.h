// song.h
#ifndef SONG_H
#define SONG_H

#include <QString>

class Song {
public:
    Song() = default;
    Song(QString t, QString a, QString d, QString p)
      : title(std::move(t)), artist(std::move(a)),
        duration(std::move(d)), mediaPath(std::move(p)) {}

    QString title;
    QString artist;
    QString duration;
    QString mediaPath;
};

#endif // SONG_H
