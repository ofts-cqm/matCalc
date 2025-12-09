#include "controlpane.h"
#include "util.h"

ControlPane::ControlPane(QWidget *parent)
    : QStackedWidget(parent){
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

ControlPane *ControlPane::addPage(){
    QWidget *newPage = new QWidget(this);
    currentPageLayout = new QVBoxLayout(newPage);
    currentPageLayout->addSpacerItem(getVerticalSpacer());
    newPage->setLayout(currentPageLayout);
    newPage->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    this->addWidget(newPage);
    this->setCurrentWidget(newPage);
    return this;
}

ControlPane *ControlPane::addResizer(ResizeBar *resizer){
    currentPageLayout->addWidget(resizer);
    currentPageLayout->addSpacerItem(getVerticalSpacer());
    return this;
}
