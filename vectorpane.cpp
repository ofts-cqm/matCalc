#include "vectorpane.h"
#include "decimallineedit.h"
#include "ui_vectorpane.h"
#include "util.h"
#include <QtWidgets/qlabel.h>
#include <QPlainTextEdit>

VectorPane::VectorPane(QWidget *parent, Vector vec, bool editable):
    ui(new Ui::VectorPane)
    , AbstractNumberPane(&vec, parent)
{
    ui->setupUi(this);

    this->editable = editable;
    this->value = vec;
    //if (editable) ui->numLayout->layout()->setSpacing(5);

    reconstructPage();
}

void VectorPane::display(GenericNumber vector){
    this->value = vector.getVector();
    reconstructPage();
}

void VectorPane::reconstructPage(){
    clearLayout(ui->numLayout->layout());
    ui->numLayout->layout()->setSpacing(0);
    ui->numLayout->update();

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

    this->setMinimumHeight(value.dim() * 30 + 20);
    this->setMaximumHeight(value.dim() * 40 + 20);
}

VectorPane *VectorPane::setSizer(ResizeBar *bar){
    bar->addTarget([this](int dim){ value.setSize(dim); reconstructPage(); });
    return this;
}

const GenericNumber *VectorPane::getValue(){
    genericValue = GenericNumber(&value);
    return &genericValue;
}

VectorPane::~VectorPane()
{
    delete ui;
}
