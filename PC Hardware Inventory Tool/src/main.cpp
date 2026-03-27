// File: src/main.cpp

#include <QApplication>
#include <QDir>
#include <iostream>

// Include the test‐routines (defines runRepoControllerTests())
#include "tests/RepoControllerTests.cpp"

// Now include the usual application headers
#include "repos/CSVHardwareRepository.h"
#include "repos/JSONHardwareRepository.h"
#include "controllers/HardwareController.h"
#include "ui/MainWindow.h"

int main(int argc, char *argv[]) {
    // 1) Run the repository/controller smoke‐tests.
    //    If any assert fails, the program aborts here.
    runRepoControllerTests();

    // 2) All tests passed → proceed to launch the GUI
    QApplication app(argc, argv);

    // Ensure a "data/" directory exists next to the executable
    QString dataDir = QCoreApplication::applicationDirPath() + QDir::separator() + "data";
    QDir dir;
    if (!dir.exists(dataDir)) {
        dir.mkpath(dataDir);
    }

    // Build the full paths to hardware.csv and hardware.json
    QString csvPath  = dataDir + QDir::separator() + "hardware.csv";
    QString jsonPath = dataDir + QDir::separator() + "hardware.json";

    // ──────────────────────────────────────────────────────────────────────────
    // CHOOSE YOUR BACKEND: CSV or JSON
    //
    // By default, we use CSV. To switch to JSON, comment out the CSV line
    // below and uncomment the JSON line.
    // ──────────────────────────────────────────────────────────────────────────

    // --- CSV Backend ---
    //auto repo = std::make_unique<CSVHardwareRepository>(csvPath);

    // --- JSON Backend ---
    auto repo = std::make_unique<JSONHardwareRepository>(jsonPath);

    // ─────────────────────────────────────────────────────────────────────────

    HardwareController controller(std::move(repo));
    MainWindow window(controller);
    window.show();

    return app.exec();
}
