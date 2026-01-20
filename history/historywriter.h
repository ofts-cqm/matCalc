#ifndef HISTORYWRITER_H
#define HISTORYWRITER_H

#include<QJsonObject>

namespace History {
    QJsonArray loadFromFile();

    void writeToFile(const QJsonArray &json);

    extern bool writeFile;

    void promptFileAccess();
}
#endif // HISTORYWRITER_H
