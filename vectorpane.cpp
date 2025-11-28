#include "vectorpane.h"
#include "ui_vectorpane.h"
#include <vector>

VectorPane::VectorPane(QWidget *parent, std::vector<int> vec)
    : QWidget(parent)
    , ui(new Ui::VectorPane)
{
    ui->setupUi(this);
    for (int i : vec){
        QLabel *label = new QLabel(this);
        label->setText(QString::fromStdString(std::to_string(i)));
        ui->numLayout->addWidget(label);
    }
    ui->numLayout->addSpacerItem(new QSpacerItem(0, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

VectorPane::~VectorPane()
{
    delete ui;
}
