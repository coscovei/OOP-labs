#ifndef SONGCONTROLLER_H
#define SONGCONTROLLER_H

#include <QObject>
#include <QVector>
#include "song.h"

class SongController : public QObject {
    Q_OBJECT
public:
    explicit SongController(QObject *parent = nullptr);

    public slots:
        void addSong(const QString &title,
                     const QString &artist,
                     const QString &duration,
                     const QString &path);
    void deleteSong(int index);
    void addToPlaylist(int index);

    signals:
        void allSongsChanged(const QVector<Song> &songs);
    void playlistChanged(const QVector<Song> &playlist);

private:
    QVector<Song> m_allSongs;
    QVector<Song> m_playlist;
};

#endif // SONGCONTROLLER_H
