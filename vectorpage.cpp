#include "vectorpage.h"
#include "genericpane.h"
#include "numberpane.h"
#include "signpane.h"
#include "vectorpane.h"
#include "util.h"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>

VectorPage::VectorPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *content = new QVBoxLayout(parent);
    content->addItem(getVerticalSpacer());

    // control
    QHBoxLayout *header = new QHBoxLayout();
    content->addLayout(header);
    header->addItem(getHorizontalSpacer());


    QLabel *dimlabel = new QLabel("Dimension: ");
    dimlabel->setFont(getLargeFont());
    header->addWidget(dimlabel);

    dimension = new QSpinBox(parent);
    dimension->setRange(2, 16);
    dimension->setValue(3);
    dimension->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    header->addWidget(dimension);
    header->addItem(getHorizontalSpacer());

    // vector
    QHBoxLayout *vectors = new QHBoxLayout();
    vectors->addItem(getHorizontalSpacer());
    vectors->addWidget(new VectorPane(parent, Vector({1, 2, 3})));
    vectors->addWidget(new NumberPane(parent, 114514));
    vectors->addWidget(new SignPane(PLUS, this));
    vectors->addWidget(new GenericPane(this, VECTOR, false));
    vectors->addItem(getHorizontalSpacer());
    content->addLayout(vectors);

    content->addItem(getVerticalSpacer());
    this->setLayout(content);
}

VectorPage::~VectorPage(){
    delete dimension;
}
