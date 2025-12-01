#include "genericpane.h"
#include "util.h"
#include "numberpane.h"
#include "vectorpane.h"

GenericPane::GenericPane(QWidget *parent, NumberType initialDisplay, bool editable, QWidget *initialPage):
    QStackedWidget(parent),
    AbstractNumberPane<GenericNumber>(GenericNumber())
{
    if (initialPage == nullptr) initialPage = getNewPageOfThisType(initialDisplay, this, editable);
    if (initialPage != nullptr) {
        addWidget(initialPage);
        typeIndex[initialDisplay] = 0;
    }

    this->editable = editable;
    currentType = initialDisplay;
}

void GenericPane::display(GenericNumber number){
    if (number.getType() != currentType){
        currentType = number.getType();
        if (typeIndex.find(currentType) == typeIndex.end()){
            typeIndex[currentType] = count();
            addWidget(getNewPageOfThisType(currentType, this, editable));
        }

        setCurrentIndex(typeIndex[currentType]);
    }

    switch (currentType){
    case NUMBER:
        ((NumberPane *)currentWidget())->display(number.getDouble());
        break;
    case VECTOR:
        ((VectorPane *)currentWidget())->display(number.getVector());
        break;
    case UNKNOWN:
        break;
    }
}

void GenericPane::reconstructPage(){
    ((AbstractNumberPane *)currentWidget())->reconstructPage();
}
