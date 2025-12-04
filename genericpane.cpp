#include "genericpane.h"
#include "util.h"

GenericPane::GenericPane(QWidget *parent, NumberType initialDisplay, bool editable)
    : GenericPane::GenericPane(parent, initialDisplay, getNewPageOfThisType(initialDisplay, this, editable), editable){

}

GenericPane::GenericPane(QWidget *parent, NumberType initialDisplay, QWidget *initialPage, bool editable):
    QStackedWidget(parent),
    AbstractNumberPane(GenericNumber())
{
    addWidget((QWidget *)initialPage);
    typeIndex[initialDisplay] = 0;
    this->editable = editable;
    currentType = initialDisplay;
}

void GenericPane::switchTo(NumberType type){
    if (type != currentType){
        currentType = type;
        if (typeIndex.find(currentType) == typeIndex.end()){
            typeIndex[currentType] = count();
            addWidget((QWidget *)getNewPageOfThisType(currentType, this, editable));
        }

        setCurrentIndex(typeIndex[currentType]);
    }
}

void GenericPane::display(GenericNumber number){
    switchTo(number.getType());
    ((AbstractNumberPane *)currentWidget())->display(number);
}

void GenericPane::reconstructPage(){
    ((AbstractNumberPane *)currentWidget())->reconstructPage();
}

const GenericNumber& GenericPane::getValue(){
    return ((AbstractNumberPane *)currentWidget())->getValue();
}

const NumberType GenericPane::getType() const{
    return currentType;
}
