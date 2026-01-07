#include "sizerbar.h"
#include "abstractpage.h"
#include "../util.h"
#include <QHBoxLayout>
#include <QLabel>

ResizeBar::ResizeBar(QString name, DimSrc source, QWidget *parent)
    : QWidget(parent)
{
    this->source = source;

    QHBoxLayout *content = new QHBoxLayout(this);
    this->setLayout(content);

    QLabel *label = new QLabel(name);
    label->setFont(getLargeFont());
    content->addWidget(label);

    slider = new QSlider(Qt::Orientation::Horizontal, this);
    slider->setTickInterval(1);
    slider->setTickPosition(QSlider::TickPosition::TicksBothSides);
    slider->setMinimum(2);
    slider->setMaximum(10);
    slider->setSingleStep(1);
    slider->setValue(source());
    slider->setTracking(false);
    slider->setMinimumWidth(200);
    content->addWidget(slider);
    this->setMaximumHeight(50);
    connect(slider, &QSlider::sliderReleased, this, &ResizeBar::onSliderReleased);
}

ResizeBar *ResizeBar::addTarget(DimTar target){
    targets.push_back(target);
    return this;
}

void ResizeBar::reload(){
    internalReload = true;
    slider->setValue(source());
    onSliderReleased();
}

void ResizeBar::onSliderReleased(){
    int newVal = slider->sliderPosition();

    for (DimTar &target : targets){
        target(newVal);
    }

    if (internalReload){
        internalReload = false;
        return;
    }

    AbstractPage::getCurrent()->evaluate();
}
