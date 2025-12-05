#include "vectorpage.h"
#include "genericpane.h"
#include "util.h"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>

GenericNumber *evaFunc(Calculation calc, GenericNumber *a, GenericNumber *b){
    return new GenericNumber(Vector(3));
}

VectorPage::VectorPage(QWidget *parent) : AbstractPage([](Calculation calc, GenericNumber *a, GenericNumber *b){return evaFunc(calc, a, b);}, {NumberType::VECTOR, NumberType::NUMBER, NumberType::VECTOR, Sign::NULL_SPACE}, parent) {
    control->addItem(getHorizontalSpacer());
    QLabel *dimlabel = new QLabel("Dimension: ");
    dimlabel->setFont(getLargeFont());
    control->addWidget(dimlabel);

    dimension = new QSpinBox(parent);
    dimension->setRange(2, 16);
    dimension->setValue(3);
    dimension->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    control->addWidget(dimension);
    control->addItem(getHorizontalSpacer());

    // vector
    content->addItem(getHorizontalSpacer());
    content->addWidget(registerOperand(new GenericPane(this, VECTOR, true), 1));
    content->addWidget(registerOperand(new GenericPane(this, NUMBER, true), 2));
    content->addWidget(sign);
    content->addWidget(registerOperand(new GenericPane(this, VECTOR, false), 3));
    content->addItem(getHorizontalSpacer());

    switchTo({NumberType::VECTOR, NumberType::NUMBER, NumberType::VECTOR, Sign::NULL_SPACE});
}

VectorPage::~VectorPage(){
    delete dimension;
}
