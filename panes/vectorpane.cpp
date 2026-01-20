#include "vectorpane.h"
#include "decimallineedit.h"
#include "ui_vectorpane.h"
#include "../util.h"
#include <QtWidgets/qlabel.h>
#include <QPlainTextEdit>

VectorPane::VectorPane(QWidget *parent, Vector vec, bool editable)
    : ui(new Ui::VectorPane), AbstractNumberPane(parent)
{
    ui->setupUi(this);

    this->editable = editable;
    this->value = vec;
    this->genericValue = GenericNumber(value);
    //if (editable) ui->numLayout->layout()->setSpacing(5);

    VectorPane::reconstructPage();
}

void VectorPane::display(GenericNumber vector){
    this->value = vector.getVector();
    reconstructPage();
}

void VectorPane::paste(GenericNumber vector){
    if (vector.getType() != VECTOR) throw IncompatiblePasteException(*this, vector);
    int oldSize = this->value.dim();
    this->value = vector.getVector();
    this->value.setSize(oldSize);
    reconstructPage();
}

void VectorPane::reconstructPage(){
    clearLayout(ui->numLayout->layout());
    ui->numLayout->layout()->setSpacing(0);
    ui->numLayout->layout()->setContentsMargins(12, 0, 12, 0);
    ui->numLayout->layout()->addItem(getVerticalSpacer());

    for (int i = 0; i < this->value.dim(); i++){
        QWidget *widget;

        if (editable){
            widget = new DecimalLineEdit(
                numberParser, [this, i](double val) { this->value[i] = val; emit onFieldChanged(this->id, i, val); },
                this->value[i]);
        }else{
            QLabel *label = new QLabel(format(this->value[i]), this);
            label->setMinimumHeight(22);
            label->setMinimumWidth(0);
            label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            label->setAlignment(Qt::AlignCenter);
            label->setFont(getLargeFont());
            label->setToolTip(format(this->value[i]));
            widget = label;
        }

        ui->numLayout->layout()->addWidget(widget);
    }
    ui->numLayout->layout()->addItem(getVerticalSpacer());

    if (this->isCurrentPage){
        this->setMinimumHeight(value.dim() * 22 + 20);
        this->setMaximumHeight(value.dim() * 22 + 20);
    }else{
        this->setMinimumHeight(0);
        this->setMaximumHeight(0);
    }
}

const Vector *VectorPane::getPrivateValue()  {return &value; }

VectorPane *VectorPane::setSizer(ResizeBar *bar){
    bar->addTarget([this](int dim){ value.setSize(dim); reconstructPage(); });
    return this;
}

void VectorPane::resizeVector(int size){
    value.setSize(size);
    reconstructPage();
}

const GenericNumber *VectorPane::getValue(){
    genericValue = GenericNumber(value);
    return &genericValue;
}

VectorPane *VectorPane::setID(int id){
    this->id = id;
    return this;
}

VectorPane::~VectorPane()
{
    delete ui;
}
