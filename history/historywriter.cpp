#include "historywriter.h"
#include <QFile>
#include <QJsonArray>
#include <QMessageBox>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>
#include "../mainwindow.h"

namespace History{
    bool writeFile = true;

    QJsonArray loadFromFile(){
        QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QStringLiteral("/history.json");
        QFile loadFile(filePath);

        if (!loadFile.open(QIODevice::ReadOnly)) {
            writeFile = false;
            //promptFileAccess();
            return {};
        }

        QByteArray temp = loadFile.readAll();

        QJsonParseError parseError;
        QJsonArray arr = QJsonDocument::fromJson(temp, &parseError).array();

        if (parseError.error != QJsonParseError::NoError) {
            qWarning() << "Parse error at" << parseError.offset << ":" << parseError.errorString();
            MainWindow::setMessage("Your local history is corrupted: " + parseError.errorString());
            return {};
        }

        return arr;
    }

    void writeToFile(const QJsonArray &json){
        if (!writeFile) return;

        QString filePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QStringLiteral("/history.json");

        QFileInfo fileInfo(filePath);
        QDir dir = fileInfo.absoluteDir();

        // Create the directory path if it doesn't exist
        if (!dir.mkpath(dir.absolutePath())) {
            qWarning() << "Failed to create directory path:" << dir.absolutePath();
            return;
        }

        QFile loadFile(filePath);
        if (!loadFile.open(QIODevice::WriteOnly)) {
            qWarning() << "Failed to write history to json file!\n" << "Error:\n" << loadFile.errorString();
            MainWindow::setMessage("Filed to write history to json file!");
            return;
        }

        loadFile.write(QJsonDocument(json).toJson());
    }

    void promptFileAccess(){
        QMessageBox::StandardButton res = QMessageBox::question(
            MainWindow::getInstance(),
            "Save History On Disk?",
            "Do you want to save your histories on disk? If you do so, you will have your histories loaded on the next time you open this calculator",
            QMessageBox::StandardButtons(QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No),
            QMessageBox::StandardButton::Yes
        );
        writeFile = (res == QMessageBox::StandardButton::Yes);
    }
}
