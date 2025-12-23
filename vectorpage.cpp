#include "vectorpage.h"
#include "calculationselectionlabel.h"
#include "genericpane.h"
#include "util.h"
#include "vectorpane.h"
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>

static GenericNumber retHolder;
static Vector vectorBuff;
static double numBuff;

static GenericNumber *evaFunc(const Calculation *calc, const GenericNumber *a, const GenericNumber *b){
    switch (calc->sign){
    case PLUS:
        vectorBuff = a->getVector() + b->getVector();
        break;
    case MINUS:
        vectorBuff = a->getVector() - b->getVector();
        break;
    case MUL:
        vectorBuff = b->getVector() * a->getDouble();
        break;
    case DOT:
        numBuff = a->getVector() * b->getVector();
        break;
    case CROSS:
        vectorBuff = a->getVector().cross(b->getVector());
        break;
    case PROJ:
        vectorBuff = Vector::proj(a->getVector(), b->getVector());
        break;
    case PERP:
        vectorBuff = Vector::perp(a->getVector(), b->getVector());
        break;
    case LENGTH:
        numBuff = a->getVector().dim();
        break;
    default:
        qDebug("Unexpected Sign for VectorPage: %d", calc->sign);
        break;
    }

    //vectorBuff = a->getVector() + b->getVector();
    if (calc->result == VECTOR) retHolder = &vectorBuff;
    else retHolder = &numBuff;

    return &retHolder;
}

VectorPage::VectorPage(QWidget *parent)
    : AbstractPage(evaFunc, &calculationDefinition[0], parent)
{
    this->alternativSign = new SignPane(currentCalculation->sign, this);
    this->alternativSign->setVisible(false);

    // control
    resizeBar = new ResizeBar("Dimension", [this](){return primaryPane == nullptr ? 3 : primaryPane->getPrivateValue()->dim();}, control);
    control->addPage()->addResizer(resizeBar);

    // vector
    content->addItem(getHorizontalSpacer());
    content->addWidget(alternativSign);
    content->addWidget(registerOperand(new GenericPane(this, (primaryPane = new VectorPane())->setSizer(resizeBar), true), 1));
    content->addWidget(sign);
    content->addWidget(registerOperand(new GenericPane(this, (new VectorPane(nullptr))->setSizer(resizeBar), true), 2));
    content->addWidget(equal);
    content->addWidget(registerOperand(new GenericPane(this, (new VectorPane(nullptr, Vector(3), false))->setSizer(resizeBar), false), 3));
    content->addItem(getHorizontalSpacer());

    AbstractPage::switchTo(&calculationDefinition[0]);
}

void VectorPage::switchTo(const Calculation *nextCalculation){
    if (currentCalculation == nextCalculation) return;

    switch (currentCalculation->sign){
    case CROSS:
        resizeBar->setVisible(true);
        break;
    case PERP:
    case PROJ:
        this->alternativSign->setVisible(false);
        this->sign->setVisible(true);
        break;
    default:
        break;
    }

    switch (nextCalculation->sign){
    case CROSS:
        primaryPane->resizeVector(3);
        resizeBar->reload();
        resizeBar->setVisible(false);
        break;
    case PERP:
    case PROJ:
        this->alternativSign->setVisible(true);
        this->alternativSign->display(nextCalculation->sign);
        this->sign->setVisible(false);
        break;
    default:
        break;
    }

    AbstractPage::switchTo(nextCalculation);
}

const Calculation VectorPage::calculationDefinition[] = {
    { VECTOR, VECTOR, VECTOR, PLUS, "+" },
    { VECTOR, VECTOR, VECTOR, MINUS, "-" },
    { NUMBER, VECTOR, VECTOR, MUL, "Scaling" },
    { VECTOR, VECTOR, NUMBER, DOT, "Dot" },
    { VECTOR, VECTOR, VECTOR, CROSS, "Cross" },
    { VECTOR, VECTOR, VECTOR, PROJ, "Projection" },
    { VECTOR, VECTOR, VECTOR, PERP, "Perp Proj" },
    { VECTOR, EMPTY, NUMBER, LENGTH, "Length" }
};

VectorPage *VectorPage::fillIndexPage(QWidget *parent){
    QVBoxLayout *indexPage = new QVBoxLayout(parent);

    for (const Calculation &calc : calculationDefinition){
        indexPage->addWidget(new CalculationSelectionLabel(calc.name, &calc, this, parent));
    }

    indexPage->addItem(getVerticalSpacer());
    return this;
}

VectorPage::~VectorPage(){
    delete dimension;
}


