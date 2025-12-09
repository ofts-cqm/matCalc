#include "vectorpage.h"
#include "genericpane.h"
#include "util.h"
#include "vectorpane.h"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>

GenericNumber *evaFunc(Calculation calc, const GenericNumber *a, const GenericNumber *b){
    return new GenericNumber(new Vector(a->getVector()));
}

VectorPage::VectorPage(QWidget *parent)
    : AbstractPage(
          evaFunc,
          {NumberType::VECTOR, NumberType::NUMBER, NumberType::VECTOR, Sign::NULL_SPACE},
          parent)
{
    // control
    ResizeBar *resizeBar = new ResizeBar("Dimension", [](){return 1;}, control);
    control->addPage()->addResizer(resizeBar);

    // vector
    content->addItem(getHorizontalSpacer());
    content->addWidget(registerOperand(new GenericPane(this, (new VectorPane())->setSizer(resizeBar), true), 1));
    content->addWidget(registerOperand(new GenericPane(this, NUMBER, true), 2));
    content->addWidget(sign);
    content->addWidget(registerOperand(new GenericPane(this, (new VectorPane(nullptr, Vector(3), false))->setSizer(resizeBar), false), 3));
    content->addItem(getHorizontalSpacer());

    switchTo({NumberType::VECTOR, NumberType::NUMBER, NumberType::VECTOR, Sign::NULL_SPACE});
}

VectorPage::~VectorPage(){
    delete dimension;
}
