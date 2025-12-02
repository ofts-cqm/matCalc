#include "vectorpane.h"
#include "decimallineedit.h"
#include "ui_vectorpane.h"
#include "util.h"
#include <QtWidgets/qlabel.h>
#include <QPlainTextEdit>

VectorPane::VectorPane(QWidget *parent, Vector vec, bool editable)
    : QWidget(parent)
    , ui(new Ui::VectorPane)
    , AbstractNumberPane(vec)
{
    ui->setupUi(this);

    this->editable = editable;
    this->value = vec;
    if (editable) ui->numLayout->layout()->setSpacing(5);

    reconstructPage();
}

void VectorPane::display(Vector vector){
    this->value = vector;
    this->genericValue = vector;
    reconstructPage();
}

void VectorPane::reconstructPage(){
    clearLayout(ui->numLayout->layout());

    for (int i = 0; i < this->value.dim(); i++){
        QWidget *widget;

        if (editable){
            widget = new DecimalLineEdit(
                numberParser, [this, i](double val) { this->value[i] = val; },
                this->value[i]);
        }else{
            QLabel *label = new QLabel(format(this->value[i]), this);
            label->setAlignment(Qt::AlignCenter);
            label->setFont(getLargeFont());
            widget = label;
        }

        ui->numLayout->layout()->addWidget(widget);
    }

    this->setMinimumHeight(value.dim() * 45 + 15);
}

VectorPane::~VectorPane()
{
    delete ui;
}
