#include "controlpane.h"
#include "util.h"

ControlPane::ControlPane(QWidget *parent)
    : QStackedWidget(parent)
{
    this->setMaximumHeight(100);
}

ControlPane *ControlPane::addPage(){
    QWidget *newPage = new QWidget(this);
    currentPageLayout = new QVBoxLayout(newPage);
    currentPageLayout->addSpacerItem(getVerticalSpacer());
    newPage->setLayout(currentPageLayout);

    this->addWidget(newPage);
    this->setCurrentWidget(newPage);

    return this;
}

ControlPane *ControlPane::addResizer(ResizeBar *resizer){
    currentPageLayout->addWidget(resizer);
    currentPageLayout->addSpacerItem(getVerticalSpacer());
    return this;
}
