#include "controlpane.h"
#include "../util.h"

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
    this->resizers.push_back(std::vector<ResizeBar *>());
    this->setCurrentWidget(newPage);
    return this;
}

ControlPane *ControlPane::addResizer(ResizeBar *resizer){
    currentPageLayout->addWidget(resizer);
    currentPageLayout->addSpacerItem(getVerticalSpacer());
    this->resizers.back().push_back(resizer);
    return this;
}

void ControlPane::refreshSizer(){
    for (ResizeBar *sizer : resizers[this->currentIndex()]){
        sizer->reload();
    }
}

void ControlPane::switchTo(int page){
    if (this->currentIndex() == page) return;
    this->setCurrentIndex(page);
    refreshSizer();
}
