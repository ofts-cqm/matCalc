#include "genericpane.h"
#include "util.h"

GenericPane::GenericPane(QWidget *parent, NumberType initialDisplay, bool editable)
    : GenericPane::GenericPane(parent, initialDisplay, getNewPageOfThisType(initialDisplay, parent, editable), editable){

}

GenericPane::GenericPane(QWidget *parent, NumberType initialDisplay, QWidget *initialPage, bool editable):
    QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    QHBoxLayout *contentWrapper = new QHBoxLayout();
    mainLayout->addItem(contentWrapper);

    contentWrapper->addItem(getHorizontalSpacer());
    contentWrapper->addWidget(content = new QStackedWidget(this));
    contentWrapper->addItem(getHorizontalSpacer());

    QHBoxLayout *buttons = new QHBoxLayout();
    mainLayout->addItem(buttons);

    copy = new QPushButton("Copy", this);
    buttons->addWidget(copy);

    paste = new QPushButton("Paste", this);
    buttons->addWidget(paste);


    content->addWidget((QWidget *)initialPage);
    typeIndex[initialDisplay] = 0;
    this->editable = editable;
    currentType = initialDisplay;
}

void GenericPane::switchTo(NumberType type){
    if (type != currentType){
        currentType = type;
        if (typeIndex.find(currentType) == typeIndex.end()){
            typeIndex[currentType] = content->count();
            content->addWidget((QWidget *)getNewPageOfThisType(currentType, this, editable));
        }

        content->setCurrentIndex(typeIndex[currentType]);
    }
}

void GenericPane::display(GenericNumber number){
    switchTo(number.getType());
    ((AbstractNumberPane *)content->currentWidget())->display(number);
}

void GenericPane::reconstructPage(){
    ((AbstractNumberPane *)content->currentWidget())->reconstructPage();
}

const GenericNumber& GenericPane::getValue(){
    return ((AbstractNumberPane *)content->currentWidget())->getValue();
}

const NumberType GenericPane::getType() const{
    return currentType;
}
