#include "matrixpage.h"
#include "calculationselectionlabel.h"
#include "util.h"
#include "vectorpane.h"

static GenericNumber retHolder;
static Matrix matrixBuff;
static Vector vectorBuff;
static double numBuff;

static GenericNumber *evaFunc(const Calculation *calc, const GenericNumber *a, const GenericNumber *b){
    switch (calc->sign){
    case PLUS:
        matrixBuff = a->getMatrix() + b->getMatrix();
        break;
    case MINUS:
        matrixBuff = a->getMatrix() - b->getMatrix();
        break;
    case MUL:
        if (calc->operandA == NUMBER){
            matrixBuff = b->getMatrix() * a->getDouble();
        } else if(calc->operandB == VECTOR){
            vectorBuff = a->getMatrix() * b->getVector();
        } else {
            matrixBuff = a->getMatrix() * b->getMatrix();
        }
        break;
    case TRANS:
        matrixBuff = a->getMatrix().transpose();
        break;
    case RREF:
    case INVT:
    case NULL_SPACE:
    case COL_SPACE:
    case RANK:
    case DET:
    default:
        break;
    }

    if (calc->result == VECTOR) retHolder = &vectorBuff;
    else if (calc->result == MATRIX) retHolder = &matrixBuff;
    else retHolder = &numBuff;

    return &retHolder;
}

const Calculation MatrixPage::calculationdefinition[] = {
    { MATRIX, MATRIX, MATRIX, PLUS, "+" },
    { MATRIX, MATRIX, MATRIX, MINUS, "-" },
    { NUMBER, MATRIX, MATRIX, MUL, "Scaling" },
    { MATRIX, MATRIX, MATRIX, MUL, "Mat Prod " },
    { MATRIX, VECTOR, VECTOR, MUL, "Mat-Vec" },
    { MATRIX, EMPTY, MATRIX, TRANS, "Transpose" }
};

int MatrixPage::primeHeight(){
    return primaryPane == nullptr ? 3 : primaryPane->getHeight();
}

int MatrixPage::primeWidth(){
    return primaryPane == nullptr ? 3 : primaryPane->getWidth();
}

int MatrixPage::seoncdWidth(){
    return secondaryPane == nullptr ? 3 : secondaryPane->getWidth();
}

MatrixPane *MatrixPage::primaryPane = nullptr;
MatrixPane *MatrixPage::secondaryPane = nullptr;

MatrixPage::MatrixPage(QWidget *parent)
    : AbstractPage(evaFunc, &calculationdefinition[0], parent){

    // addition and substraction
    normalHeight = new ResizeBar("Height", primeHeight, control);
    normalWidth = new ResizeBar("Width", primeWidth, control);
    control->addPage()->addResizer(normalHeight)->addResizer(normalWidth);

    // matrix multiplication;
    mulHeight = new ResizeBar("n", primeHeight, control);
    mulMiddle = new ResizeBar("m", primeWidth, control);
    mulWidth = new ResizeBar("k", seoncdWidth, control);
    control->addPage()->addResizer(mulHeight)->addResizer(mulMiddle)->addResizer(mulWidth);

    // square
    normalSize = new ResizeBar("Dimension", primeHeight, control);
    control->addPage()->addResizer(normalSize);
    control->switchTo(0);

    content->addItem(getHorizontalSpacer());
    content->addWidget(registerOperand(new GenericPane(this,
        (primaryPane = new MatrixPane())->
            setHeightSizer(normalHeight)->setWidthSizer(normalWidth)->
            setHeightSizer(mulHeight)->setWidthSizer(mulMiddle)->
            setHeightSizer(normalSize)->setWidthSizer(normalSize), true), 1));
    content->addWidget(sign);
    content->addWidget(registerOperand((new GenericPane(this,
        (secondaryPane = new MatrixPane(nullptr))->
            setHeightSizer(normalHeight)->setWidthSizer(normalWidth)->
            setHeightSizer(mulMiddle)->setWidthSizer(mulWidth), true))->append(
        (new VectorPane())->setSizer(normalWidth)), 2));
    content->addWidget(equal);
    content->addWidget(registerOperand(new GenericPane(this,
        new MatrixPane(nullptr, Matrix(3, 3), false), false), 3));
    content->addItem(getHorizontalSpacer());

    AbstractPage::switchTo(&calculationdefinition[0]);
}

void MatrixPage::switchTo(const Calculation *nextCalculation){
    switch(nextCalculation->sign){
    case PLUS:
    case MINUS:
    case TRANS:
    case RREF:
    case RANK:
    case NULL_SPACE:
    case COL_SPACE:
        control->switchTo(0);
        break;
    case MUL:
        if(nextCalculation->operandA == MATRIX && nextCalculation->operandB == MATRIX){
            control->switchTo(1);
        } else {
            control->switchTo(0);
        }
        break;
    case INVT:
    case DET:
        control->switchTo(2);
    default:
        break;
    }

    AbstractPage::switchTo(nextCalculation);
}

MatrixPage *MatrixPage::fillIndexPage(QWidget *parent){
    QVBoxLayout *indexPage = new QVBoxLayout(parent);

    for (const Calculation &calc : calculationdefinition){
        indexPage->addWidget(new CalculationSelectionLabel(calc.name, &calc, this, parent));
    }

    indexPage->addItem(getVerticalSpacer());
    return this;
}
