#include "util.h"

QString format(double val){
    char buffer[64];
    std::snprintf(buffer, sizeof(buffer), "%.6f", val);  // fixed, 6 decimals

    std::string s(buffer);

    // Remove trailing zeros
    s.erase(s.find_last_not_of('0') + 1);

    // Remove trailing dot
    if (!s.empty() && s.back() == '.') {
        s.pop_back();
    }

    return QString::fromStdString(s);
}

QFont getLargeFont(){
    QFont font = QFont();
    font.setPointSize(20);
    return font;
}
