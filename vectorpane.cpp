#include "vectorpane.h"
#include "decimallineedit.h"
#include "ui_vectorpane.h"
#include "util.h"
#include <QtWidgets/qlabel.h>
#include <QPlainTextEdit>

auto parser = [](QStringView s) -> std::optional<double> {
    bool ok = false;
    double v = s.toDouble(&ok);
    return ok ? std::optional<double>(v) : std::nullopt;
};

VectorPane::VectorPane(QWidget *parent, Vector vec, bool editable)
    : QWidget(parent)
    , ui(new Ui::VectorPane)
{
    this->editable = editable;
    this->value = vec;

    ui->setupUi(this);
    for (int i = 0; i < vec.dim(); i++){
        if (editable){
            DecimalLineEdit *edit = new DecimalLineEdit(
                parser, [this, i](double val) { this->value[i] = val; },vec[i]
            );
            ui->numLayout->layout()->addWidget(edit);
        }else{
            QLabel *label = new QLabel(format(vec[i]), this);
            label->setAlignment(Qt::AlignCenter);
            label->setFont(getLargeFont());
            ui->numLayout->layout()->addWidget(label);
        }
    }
}

VectorPane::~VectorPane()
{
    delete ui;
}
