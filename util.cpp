#include "util.h"
#include "numberpane.h"
#include "vectorpane.h"

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

void clearLayout(QLayout* layout, bool deleteWidgets) {
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout, deleteWidgets);
        }
        delete item;
    }
}

std::optional<double> numberParser(QStringView s){
    bool ok = false;
    double v = s.toDouble(&ok);
    return ok ? std::optional<double>(v) : std::nullopt;
};

EmptyPane::EmptyPane(QWidget *parent): QWidget(parent){}

QWidget *getNewPageOfThisType(NumberType type, QWidget *parent, bool editable){
    switch (type){
    case NUMBER:
        return new NumberPane(parent, 0, editable);
    case VECTOR:
        return new VectorPane(parent, {}, editable);
    case UNKNOWN:
    case EMPTY:
        return new EmptyPane(parent);
    }
}
