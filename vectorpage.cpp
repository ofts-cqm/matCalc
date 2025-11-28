#include "vectorpage.h"
#include "vectorpane.h"
#include "util.h"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>

VectorPage::VectorPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *content = new QVBoxLayout(parent);

    // control
    QHBoxLayout *header = new QHBoxLayout();
    header->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
    content->addLayout(header);

    QLabel *dimlabel = new QLabel("Dimension: ");
    dimlabel->setFont(getLargeFont());
    header->addWidget(dimlabel);

    dimension = new QSpinBox(parent);
    dimension->setRange(2, 16);
    dimension->setValue(3);
    //dimension->setGeometry(0, 0, 40, 20);
    dimension->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    header->addWidget(dimension);
    header->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));

    // vector
    QHBoxLayout *vectors = new QHBoxLayout();
    vectors->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
    vectors->addWidget(new VectorPane(parent, Vector({1, 2, 3})));
    vectors->addWidget(new VectorPane(parent, Vector({4, 5, 6})));
    vectors->addWidget(new VectorPane(parent, Vector({7, 8, 9}), false));
    vectors->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed));
    content->addLayout(vectors);

    this->setLayout(content);
}

VectorPage::~VectorPage(){
    delete dimension;
}
