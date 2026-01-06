#include "spansetpane.h"
#include "ui_spansetpane.h"
#include "util.h"
#include "vectorpane.h"

SpanSetPane::SpanSetPane(SpanSet value, bool editable, QWidget *parent)
    : AbstractNumberPane(parent)
    , ui(new Ui::SpanSetPane)
    , editable(editable)
    , value(value)
{
    ui->setupUi(this);
    SpanSetPane::reconstructPage();
}

void SpanSetPane::display(GenericNumber num){
    if (num.getType() == SPAN_SET)
        this->value = num.getSpanSet();
    else if(num.getType() == MATRIX)
        this->value = num.getMatrix();
    else throw IncompatiblePasteException(*this, num);
    reconstructPage();
}

void SpanSetPane::paste(GenericNumber num){
    display(num);
}

QSize SpanSetPane::sizeHint() const{
    return this->isCurrentPage ? QSize(value.getWidth() > 3 ? 300 : value.getWidth() * 80 + 40, value.getHeight() * 22 + 92) : QSize(0, 0);
}

QSize SpanSetPane::minimumSizeHint() const{
    return QSize(0, 0);
}

void SpanSetPane::reconstructPage(){
    clearLayout(ui->numLayout->layout());

    for (int i = 0; i < value.getWidth(); i++){
        VectorPane *pane = (new VectorPane(ui->numLayout, value[i], editable))->setID(i);
        pane->setAsCurrent(true);
        pane->reconstructPage();
        connect(pane, &VectorPane::onFieldChanged, this, &SpanSetPane::onVecFieldChanged);
        ui->numLayout->layout()->addWidget(pane);
    }

    if (this->isCurrentPage){
        this->setMinimumHeight(value.getHeight() * 22 + 92);
        this->setMinimumWidth(value.getWidth() > 3 ? 300 : value.getWidth() * 80 + 40);
        this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    }else{
        this->setMinimumWidth(0);
        this->setMinimumHeight(0);
        this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    }
}

const GenericNumber *SpanSetPane::getValue(){
    genericValue = GenericNumber(&value);
    return &genericValue;
}

SpanSetPane *SpanSetPane::vecSizer(ResizeBar *bar){
    bar->addTarget([this](int dim){ value.resize(dim, -1); reconstructPage(); });
    return this;
}

SpanSetPane *SpanSetPane::setSizer(ResizeBar *bar){
    bar->addTarget([this](int dim){ value.resize(-1, dim); reconstructPage(); });
    return this;
}

void SpanSetPane::onVecFieldChanged(int id, int pos, double val){
    value[id, pos] = val;
}

SpanSetPane::~SpanSetPane()
{
    delete ui;
}
