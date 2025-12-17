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

GenericNumber *evaFunc(const Calculation *calc, const GenericNumber *a, const GenericNumber *b){
    switch (calc->sign){
    case PLUS:
        vectorBuff = a->getVector() + b->getVector();
        break;
    case MINUS:
        vectorBuff = a->getVector() - b->getVector();
        break;
    case MUL:
        vectorBuff = a->getVector() * b->getDouble();
        break;
    case DOT:
        numBuff = a->getVector() * b->getVector();
        break;
    case CROSS:
        vectorBuff = a->getVector().cross(b->getVector());
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
    // control
    resizeBar = new ResizeBar("Dimension", [this](){return primaryPane == nullptr ? 3 : primaryPane->getPrivateValue()->dim();}, control);
    control->addPage()->addResizer(resizeBar);

    // vector
    content->addItem(getHorizontalSpacer());
    content->addWidget(registerOperand(new GenericPane(this, (primaryPane = new VectorPane())->setSizer(resizeBar), true), 1));
    content->addWidget(sign);
    content->addWidget(registerOperand(new GenericPane(this, (new VectorPane(nullptr))->setSizer(resizeBar), true), 2));
    content->addWidget(equal);
    content->addWidget(registerOperand(new GenericPane(this, (new VectorPane(nullptr, Vector(3), false))->setSizer(resizeBar), false), 3));
    content->addItem(getHorizontalSpacer());

    AbstractPage::switchTo(&calculationDefinition[0]);
}

void VectorPage::switchTo(const Calculation *nextCalculation){
    if (currentCalculation->sign == CROSS) resizeBar->setVisible(true);

    if (nextCalculation->sign == CROSS){
        primaryPane->resizeVector(3);
        resizeBar->reload();
        resizeBar->setVisible(false);
    }

    AbstractPage::switchTo(nextCalculation);
}

const Calculation VectorPage::calculationDefinition[] = {
    { VECTOR, VECTOR, VECTOR, PLUS, "+" },
    { VECTOR, VECTOR, VECTOR, MINUS, "-" },
    { VECTOR, NUMBER, VECTOR, MUL, "Scaling" },
    { VECTOR, VECTOR, NUMBER, DOT, "Dot" },
    { VECTOR, VECTOR, VECTOR, CROSS, "Cross" },
    //{ VECTOR, VECTOR, VECTOR, PROJ, "Projection" },
    //{ VECTOR, VECTOR, VECTOR, PERP, "Perp Proj" },
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


