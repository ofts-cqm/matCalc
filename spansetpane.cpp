#include "spansetpane.h"
#include "labelpane.h"
#include "ui_spansetpane.h"
#include "util.h"
#include "vectorpane.h"

SpanSetPane::SpanSetPane(SpanSet value, bool editable, QWidget *parent)
    : AbstractNumberPane(parent)
    , ui(new Ui::SpanSetPane)
    , editable(editable)
    , value(value)
{
    this->genericValue = &value;
    ui->setupUi(this);
    span = true;
    ui->span->setFont(getLargeFont());
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
    if (this->value.getWidth() == 0) return QSize(135, 40);
    return this->isCurrentPage ? QSize(value.getWidth() > 2 ? 252 : value.getWidth() * 92 + 68, value.getHeight() * 22 + 92) : QSize(0, 0);
}

QSize SpanSetPane::minimumSizeHint() const{
    return QSize(0, 0);
}

void SpanSetPane::reconstructPage(){
    clearLayout(ui->numLayout->layout());
    if (span) ui->span->show();
    else ui->span->hide();

    if (value.getWidth() == 0){
        ui->numLayout->layout()->addWidget(new LabelPane("Empty"));
        this->setMinimumHeight(40);
        this->setMinimumWidth(span ? 150 : 40);
        return;
    }

    for (int i = 0; i < value.getWidth(); i++){
        VectorPane *pane = (new VectorPane(ui->numLayout, value[i], editable))->setID(i);
        pane->setAsCurrent(true);
        pane->reconstructPage();
        connect(pane, &VectorPane::onFieldChanged, this, &SpanSetPane::onVecFieldChanged);
        ui->numLayout->layout()->addWidget(pane);
    }

    if (this->isCurrentPage){
        this->setMinimumHeight(value.getHeight() * 22 + 92);
        this->setMinimumWidth(value.getWidth() > 2 ? 252 : value.getWidth() * 92 + 68);
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

SpanSetPane *SpanSetPane::hasSpan(bool span){
    this->span = span;
    if (span) ui->span->show();
    else ui->span->hide();
    return this;
}

void SpanSetPane::onVecFieldChanged(int id, int pos, double val){
    value[pos, id] = val;
}

SpanSetPane::~SpanSetPane()
{
    delete ui;
}
