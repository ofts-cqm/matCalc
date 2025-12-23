#include "genericpane.h"
#include "abstractpage.h"
#include "util.h"

GenericPane::GenericPane(QWidget *parent, NumberType initialDisplay, bool editable)
    : GenericPane::GenericPane(parent, getNewPageOfThisType(initialDisplay, parent, editable), editable){

}

GenericPane::GenericPane(QWidget *parent, AbstractNumberPane *initialPage, bool editable):
    QWidget(parent),
    typeIndex()
{
    this->setMinimumWidth(120);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addItem(getVerticalSpacer());
    setLayout(mainLayout);

    QHBoxLayout *contentWrapper = new QHBoxLayout();
    mainLayout->addItem(contentWrapper);

    contentWrapper->addItem(getHorizontalSpacer());
    contentWrapper->addWidget(content = new QStackedWidget(this));
    contentWrapper->addItem(getHorizontalSpacer());
    mainLayout->addItem(getVerticalSpacer());

    buttons = new QHBoxLayout();
    mainLayout->addItem(buttons);

    copy = new QPushButton("Copy", this);
    copy->setMaximumWidth(60);
    buttons->addWidget(copy);
    connect(copy, &QPushButton::pressed, this, &GenericPane::onCopy);

    paste = new QPushButton("Paste", this);
    paste->setMaximumWidth(60);
    buttons->addWidget(paste);
    connect(paste, &QPushButton::pressed, this, &GenericPane::onPaste);

    for (int i = 0; i < NUMBER_TYPE_COUNT; i++){
        typeIndex[i] = -1;
    }

    content->addWidget((QWidget *)initialPage);
    typeIndex[initialPage->getType()] = 0;
    this->editable = editable;
    currentType = initialPage->getType();
}

GenericPane *GenericPane::append(AbstractNumberPane *pane){
    typeIndex[pane->getType()] = content->count();
    content->addWidget(pane);
    return this;
}

void GenericPane::switchTo(NumberType type){
    if (type != currentType){
        if (currentType == UNKNOWN || currentType == EMPTY){
            this->setVisible(true);
        }

        currentType = type;

        if (currentType == UNKNOWN || currentType == EMPTY){
            this->setVisible(false);
        }

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

static GenericNumber clipBoard;

void GenericPane::onCopy(){
    clipBoard = this->getValue()->deepclone();
}

void GenericPane::onPaste(){
    if (clipBoard.getType() == this->getType()){
        static_cast<AbstractNumberPane *>(content->currentWidget())->paste(clipBoard);
        AbstractPage::getCurrent()->evaluate();
    }
}

const QString GenericPane::functionStyle = ".QStackedWidget {border-image: url(:/assets/FuncBracket.png) 0 96 0 96 stretch; border-width: 5px;}";
const QString GenericPane::modulusStyle = ".QStackedWidget {border-image: url(:/assets/ModuloBorder.png) 0 6 0 6 stretch; border-width: 8px;}";

