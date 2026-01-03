#include "matrixpane.h"
#include "decimallineedit.h"
#include "util.h"
#include <QLabel>

MatrixPane::MatrixPane(QWidget *parent, Matrix mat, bool editable)
    : AbstractNumberPane(parent)
    , ui(new Ui::VectorPane)
{
    ui->setupUi(this);

    this->editable = editable;
    this->value = mat;
    this->genericValue = GenericNumber(&value);

    MatrixPane::reconstructPage();
}

void MatrixPane::display(GenericNumber matrix){
    this->value = matrix.getMatrix();
    reconstructPage();
}

void MatrixPane::paste(GenericNumber num){
    int oldWidth = value.getWidth();
    int oldHeight = value.getHeight();
    this->value = num.getMatrix();
    this->value.resize(oldHeight, oldWidth);
    reconstructPage();
}

void MatrixPane::reconstructPage(){
    clearLayout(ui->numLayout->layout());
    ui->numLayout->layout()->setSpacing(0);
    ui->numLayout->layout()->setContentsMargins(12, 0, 12, 0);
    ui->numLayout->layout()->addItem(getVerticalSpacer());

    for (int i = 0; i < getHeight(); i++){
        QWidget *widget = new QWidget(ui->numLayout);
        QHBoxLayout *layout = new QHBoxLayout(widget);
        layout->setContentsMargins(0, 0, 0, 0);
        widget->setLayout(layout);

        for (int j = 0; j < getWidth(); j++){
            QWidget *content;

            if (editable){
                content = new DecimalLineEdit(
                    numberParser, [this, i, j](double val) {this->value[i, j] = val;},
                    this->value[i, j]);
                content->setMaximumWidth(40);
            }else{
                QLabel *label = new QLabel(format(this->value[i, j]), this);
                label->setMinimumHeight(22);
                label->setMinimumWidth(0);
                label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
                label->setAlignment(Qt::AlignCenter);
                label->setFont(getLargeFont());
                content = label;
            }

            layout->addWidget(content);
        }
        ui->numLayout->layout()->addWidget(widget);
    }

    ui->numLayout->layout()->addItem(getVerticalSpacer());
    this->setMinimumHeight(value.getHeight() * 22 + 20);
    this->setGeometry(0, 0, value.getWidth() * 40 + 24, value.getHeight() * 22 + 20);
    this->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);
}

const GenericNumber *MatrixPane::getValue(){
    genericValue = GenericNumber(&value);
    return &genericValue;
}

MatrixPane *MatrixPane::setHeightSizer(ResizeBar *bar){
    bar->addTarget([this](int dim){ value.resize(dim); reconstructPage(); });
    heightSizers.push_back(bar);
    return this;
}

MatrixPane *MatrixPane::setWidthSizer(ResizeBar *bar){
    bar->addTarget([this](int dim){ value.resize(-1, dim); reconstructPage(); });
    widthSizers.push_back(bar);
    return this;
}

MatrixPane *MatrixPane::setSquareSizer(ResizeBar *bar){
    bar->addTarget([this](int dim){ value.resize(dim, dim); reconstructPage(); });
    squareSizers.push_back(bar);
    return this;
}

int MatrixPane::getHeight() const{ return value.getHeight();}

int MatrixPane::getWidth() const {return value.getWidth(); }

void MatrixPane::resizeMatrix(int height, int width){
    value.resize(height, width);
    reconstructPage();
}

void MatrixPane::resizeMatrix(int size){
    value.resize(size, size);
    reconstructPage();
}
