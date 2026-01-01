#include "labelpane.h"
#include <QVBoxLayout>

LabelPane::LabelPane(QString label, QWidget *parent) : AbstractNumberPane(parent){
    QLayout *layout = new QVBoxLayout(this);
    layout->addWidget(this->label = new QLabel(label, this));
}

void LabelPane::reconstructPage(){
    label->update();
}

void LabelPane::display(GenericNumber num) {
    label->setText(QString::fromStdString(num.getLabel()));
}

void LabelPane::paste(GenericNumber num) {
    display(num);
}
