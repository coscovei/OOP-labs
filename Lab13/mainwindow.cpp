#include "mainwindow.h"
#include "songcontroller.h"
#include <QTableWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      controller(new SongController(this))
{
    // Build UI exactly as in week 12
    tableWidget = new QTableWidget(0, 3, this);
    tableWidget->setHorizontalHeaderLabels({"Title","Artist","Duration"});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    titleEdit    = new QLineEdit(this);
    artistEdit   = new QLineEdit(this);
    durationEdit = new QLineEdit(this);
    pathEdit     = new QLineEdit(this);

    addBtn        = new QPushButton("&Add", this);
    delBtn        = new QPushButton("&Delete", this);
    updBtn        = new QPushButton("&Update", this);
    filterBtn     = new QPushButton("&Filter", this);
    toPlaylistBtn = new QPushButton(">", this);
    playBtn       = new QPushButton("&Play", this);
    nextBtn       = new QPushButton("&Next", this);

    playlistWidget = new QListWidget(this);

    auto *form = new QFormLayout;
    form->addRow("Title:",    titleEdit);
    form->addRow("Artist:",   artistEdit);
    form->addRow("Duration:", durationEdit);
    form->addRow("Path:",     pathEdit);

    auto *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(addBtn);
    btnLayout->addWidget(delBtn);
    btnLayout->addWidget(updBtn);
    btnLayout->addWidget(filterBtn);

    auto *left = new QVBoxLayout;
    left->addWidget(new QLabel("All songs", this));
    left->addWidget(tableWidget);
    left->addLayout(form);
    left->addLayout(btnLayout);

    auto *middle = new QVBoxLayout;
    middle->addStretch();
    middle->addWidget(toPlaylistBtn);
    middle->addStretch();

    auto *right = new QVBoxLayout;
    right->addWidget(new QLabel("Playlist", this));
    right->addWidget(playlistWidget);
    right->addWidget(playBtn);
    right->addWidget(nextBtn);

    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(left, 4);
    mainLayout->addLayout(middle, 1);
    mainLayout->addLayout(right, 3);
    setLayout(mainLayout);

    setWindowTitle("Playlist Qt");
    resize(800, 500);

    //Wire up UI to controller slots
    connect(addBtn,        &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(delBtn,        &QPushButton::clicked, this, &MainWindow::onDeleteClicked);
    connect(filterBtn,     &QPushButton::clicked, this, &MainWindow::onFilterClicked);
    connect(toPlaylistBtn, &QPushButton::clicked, this, &MainWindow::onToPlaylistClicked);

    // Wire up controller to UI refresh slots
    connect(controller, &SongController::allSongsChanged,
            this, &MainWindow::refreshAllSongs);
    connect(controller, &SongController::playlistChanged,
            this, &MainWindow::refreshPlaylist);
}

void MainWindow::onAddClicked()
{
    controller->addSong(
        titleEdit->text(),
        artistEdit->text(),
        durationEdit->text(),
        pathEdit->text()
    );
}

void MainWindow::onDeleteClicked()
{
    controller->deleteSong(tableWidget->currentRow());
}

void MainWindow::onFilterClicked()
{
    QString key = artistEdit->text().toLower();
    for (int r = 0; r < tableWidget->rowCount(); ++r) {
        bool hide = !tableWidget->item(r,1)->text().toLower().contains(key);
        tableWidget->setRowHidden(r, hide);
    }
}

void MainWindow::onToPlaylistClicked()
{
    controller->addToPlaylist(tableWidget->currentRow());
}

void MainWindow::refreshAllSongs(const QVector<Song> &songs)
{
    tableWidget->setRowCount(songs.size());
    for (int i = 0; i < songs.size(); ++i) {
        const auto &s = songs.at(i);
        tableWidget->setItem(i, 0, new QTableWidgetItem(s.title));
        tableWidget->setItem(i, 1, new QTableWidgetItem(s.artist));
        tableWidget->setItem(i, 2, new QTableWidgetItem(s.duration));
        // store path in UserRole on the first column
        tableWidget->item(i,0)->setData(Qt::UserRole, s.mediaPath);
    }
}

void MainWindow::refreshPlaylist(const QVector<Song> &pl)
{
    playlistWidget->clear();
    for (const auto &s : pl)
        playlistWidget->addItem(s.title);
}
