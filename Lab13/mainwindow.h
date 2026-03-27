#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPointer>
#include "song.h"
class QTableWidget;
class QListWidget;
class QLineEdit;
class QPushButton;
class SongController;

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    private slots:
        // slots to call controller
        void onAddClicked();
    void onDeleteClicked();
    void onFilterClicked();
    void onToPlaylistClicked();
    // slots to receive updated data
    void refreshAllSongs(const QVector<Song> &songs);
    void refreshPlaylist(const QVector<Song> &playlist);

private:
    QPointer<SongController> controller;

    QTableWidget *tableWidget;
    QListWidget  *playlistWidget;
    QLineEdit    *titleEdit;
    QLineEdit    *artistEdit;
    QLineEdit    *durationEdit;
    QLineEdit    *pathEdit;
    QPushButton  *addBtn;
    QPushButton  *delBtn;
    QPushButton  *updBtn;
    QPushButton  *filterBtn;
    QPushButton  *toPlaylistBtn;
    QPushButton  *playBtn;
    QPushButton  *nextBtn;
};

#endif // MAINWINDOW_H
