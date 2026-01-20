#include "util.h"
#include "calc/calculator.h"
#include "panes/matrixpane.h"
#include "panes/numberpane.h"
#include "panes/spansetpane.h"
#include "panes/vectorpane.h"
#include "panes/labelpane.h"
#include "mainwindow.h"
#include <QWidget>

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

    if (s == "-0") return "0";

    return QString::fromStdString(s);
}

std::string nameForNumberType(NumberType type){
    switch (type){
    case NUMBER:
        return "Number";
    case VECTOR:
        return "Vector";
    case MATRIX:
        return "Matrix";
    case SPAN_SET:
        return "Set";
    case LABEL:
        return "Info Label";
    case UNKNOWN:
    case EMPTY:
        return "Empty";
    }
}

QFont getLargeFont(){
    QFont font = QFont();
    font.setPointSize(16);
    return font;
}

QFont getXLFont(){
    QFont font = QFont();
    font.setPointSize(24);
    return font;
}

void clearLayout(QLayout* layout, bool deleteWidgets) {
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout, deleteWidgets);
            delete childLayout;
        }

        QWidget *w = item->widget();
        if (deleteWidgets && w){
            w->deleteLater();
        }
        delete item;
    }
}

void throwRangeException(int accessed, int maximum) {
    std::string str = "Invalid access of index " + std::to_string(accessed) + ", length is " + std::to_string(maximum);
    throw std::out_of_range(str);
}

std::optional<double> numberParser(QStringView s){
    bool ok = false;
    double v = s.toDouble(&ok);
    //return ok ? std::optional<double>(v) : std::nullopt;
    if (ok) return v;
    std::optional<double> res = Calculator::evaluate(s.toString().toStdString());
    MainWindow::setMessage(QString(Calculator::getShortErrorMessage().c_str()));
    return res;
};

QSpacerItem *getHorizontalSpacer(){
    return new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed);
}

QSpacerItem *getVerticalSpacer(){
    return new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
}

EmptyPane::EmptyPane(QWidget *parent): AbstractNumberPane(parent){}

AbstractNumberPane *getNewPageOfThisType(NumberType type, QWidget *parent, bool editable){
    switch (type){
    case NUMBER:
        return new NumberPane(parent, 0, editable);
    case VECTOR:
        return new VectorPane(parent, Vector(3), editable);
    case MATRIX:
        return new MatrixPane(parent, Matrix(3, 3), editable);
    case LABEL:
        return new LabelPane(QString::fromStdString(""), parent);
    case SPAN_SET:
        return new SpanSetPane(SpanSet(), editable, parent);
    case UNKNOWN:
    case EMPTY:
        return new EmptyPane(parent);
        break;
    }
}

bool isZero(double d){
    return d < 1e-9 && d > -1e-9;
}
