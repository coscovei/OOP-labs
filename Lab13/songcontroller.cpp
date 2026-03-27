#include "songcontroller.h"

SongController::SongController(QObject *parent)
    : QObject(parent)
{}

void SongController::addSong(const QString &title,
                             const QString &artist,
                             const QString &duration,
                             const QString &path)
{
    m_allSongs.append(Song{title, artist, duration, path});
    emit allSongsChanged(m_allSongs);
}

void SongController::deleteSong(int index)
{
    if (index < 0 || index >= m_allSongs.size()) return;
    // remove from playlist if present
    const auto &toRemove = m_allSongs.at(index).title;
    for (int i = m_playlist.size()-1; i >= 0; --i) {
        if (m_playlist.at(i).title == toRemove)
            m_playlist.remove(i);
    }
    // remove from all songs
    m_allSongs.remove(index);
    emit allSongsChanged(m_allSongs);
    emit playlistChanged(m_playlist);
}

void SongController::addToPlaylist(int index)
{
    if (index < 0 || index >= m_allSongs.size()) return;
    m_playlist.append(m_allSongs.at(index));
    emit playlistChanged(m_playlist);
}
