#include "genericpane.h"
#include "util.h"

GenericPane::GenericPane(QWidget *parent, NumberType initialDisplay, bool editable)
    : GenericPane::GenericPane(parent, getNewPageOfThisType(initialDisplay, parent, editable), editable){

}

GenericPane::GenericPane(QWidget *parent, AbstractNumberPane *initialPage, bool editable):
    QWidget(parent),
    typeIndex()
{
    this->setMinimumWidth(120);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addItem(getVerticalSpacer());
    setLayout(mainLayout);

    QHBoxLayout *contentWrapper = new QHBoxLayout();
    mainLayout->addItem(contentWrapper);

    contentWrapper->addItem(getHorizontalSpacer());
    contentWrapper->addWidget(content = new QStackedWidget(this));
    contentWrapper->addItem(getHorizontalSpacer());
    mainLayout->addItem(getVerticalSpacer());

    QHBoxLayout *buttons = new QHBoxLayout();
    mainLayout->addItem(buttons);

    copy = new QPushButton("Copy", this);
    copy->setMaximumWidth(60);
    buttons->addWidget(copy);

    paste = new QPushButton("Paste", this);
    paste->setMaximumWidth(60);
    buttons->addWidget(paste);

    for (int i = 0; i < NUMBER_TYPE_COUNT; i++){
        typeIndex[i] = -1;
    }


    content->addWidget((QWidget *)initialPage);
    typeIndex[initialPage->getType()] = 0;
    this->editable = editable;
    currentType = initialPage->getType();
}

void GenericPane::switchTo(NumberType type){
    if (type != currentType){
        currentType = type;
        if (typeIndex[currentType] == -1){
            typeIndex[currentType] = content->count();
            content->addWidget((QWidget *)getNewPageOfThisType(currentType, this, editable));
        }

        content->setCurrentIndex(typeIndex[currentType]);
    }
}

void GenericPane::applyBorder(SignDefinition type){
    if (currentType == EMPTY || currentType == UNKNOWN) return;

    QString border = "";
    if (type.isAbs){
        border = modulusStyle;
    } else if (type.isFunction){
        border = functionStyle;
    }

    this->setStyleSheet(border);
}

void GenericPane::display(GenericNumber number){
    switchTo(number.getType());
    static_cast<AbstractNumberPane *>(content->currentWidget())->display(number);
}

void GenericPane::reconstructPage(){
    static_cast<AbstractNumberPane *>(content->currentWidget())->reconstructPage();
}

const GenericNumber *GenericPane::getValue(){
    auto val = static_cast<AbstractNumberPane *>(content->currentWidget())->getValue();
    return val;
}

const NumberType GenericPane::getType() const{
    return currentType;
}

const QString GenericPane::functionStyle = ".QStackedWidget {border-image: url(:/assets/FuncBracket.png) 0 64 0 64 stretch; border-width: 5px;}";
const QString GenericPane::modulusStyle = ".QStackedWidget {border-image: url(:/assets/ModuloBorder.png) 0 4 0 4 stretch; border-width: 5px;}";

