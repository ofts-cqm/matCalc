#include "matrixpage.h"
#include "calculationselectionlabel.h"
#include "spanset.h"
#include "spansetpane.h"
#include "util.h"
#include "vectorpane.h"
#include "reducedmatrix.h"

static GenericNumber retHolder;
static Matrix matrixBuff;
static Vector vectorBuff;
static double numBuff;
static std::string labBuff;
static SpanSet setBuff;

static GenericNumber *evaFunc(const Calculation *calc, const GenericNumber *a, const GenericNumber *b){
    labBuff = "";

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
        matrixBuff = b->getMatrix().reduceAsMatrix();
        break;
    case DET:
        numBuff = b->getMatrix().det();
        break;
    case INVT: {
        ReducedMatrix mat = ReducedMatrix::reduce(a->getMatrix(), Matrix::unit(a->getMatrix().getHeight()));
        if (mat.rank() == a->getMatrix().getHeight()) matrixBuff = mat.augmentedMatrix();
        else labBuff = "Matrix Not Invertable";
        break;
    }
    case RANK:
        numBuff = b->getMatrix().reduce().rank();
        break;
    case NULL_SPACE:
        setBuff = b->getMatrix().nullSpace();
        //setBuff = SpanSet(b->getMatrix());
        break;
    case COL_SPACE:
        setBuff = b->getMatrix().colSpace();
        break;
    case BASE:
        setBuff = b->getSpanSet().reduce();
        break;
    default:
        break;
    }

    if (calc->result == VECTOR) retHolder = &vectorBuff;
    else if (calc->result == MATRIX) retHolder = &matrixBuff;
    else if (calc->result == SPAN_SET) retHolder = &setBuff;
    else retHolder = &numBuff;

    if (labBuff != "") retHolder = &labBuff;

    return &retHolder;
}

const Calculation MatrixPage::calculationdefinition[] = {
    { MATRIX, MATRIX, MATRIX, PLUS, "+" },
    { MATRIX, MATRIX, MATRIX, MINUS, "-" },
    { NUMBER, MATRIX, MATRIX, MUL, "Scaling" },
    { MATRIX, MATRIX, MATRIX, MUL, "Mat Prod " },
    { MATRIX, VECTOR, VECTOR, MUL, "Mat-Vec" },
    { MATRIX, EMPTY, MATRIX, INVT, "Invert"},
    { MATRIX, EMPTY, MATRIX, TRANS, "Transpose" },
    { EMPTY, MATRIX, NUMBER, RANK, "Rank" },
    { EMPTY, MATRIX, NUMBER, DET, "Det" },
    { EMPTY, MATRIX, MATRIX, RREF, "Reduce" },
    { EMPTY, MATRIX, SPAN_SET, COL_SPACE, "Range" },
    { EMPTY, MATRIX, SPAN_SET, NULL_SPACE, "Kernal" },
    { EMPTY, SPAN_SET, SPAN_SET, BASE, "Find Base" }
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
SpanSetPane *MatrixPage::resPane = nullptr;

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
    content->addWidget(registerOperand((new GenericPane(this,
        (primaryPane = new MatrixPane())->
            setHeightSizer(normalHeight)->setWidthSizer(normalWidth)->
            setHeightSizer(mulHeight)->setWidthSizer(mulMiddle)->
            setHeightSizer(normalSize)->setWidthSizer(normalSize), true)), 1));
    content->addWidget(sign);
    content->addWidget(registerOperand((new GenericPane(this,
        (secondaryPane = new MatrixPane(nullptr))->
            setHeightSizer(normalHeight)->setWidthSizer(normalWidth)->
            setHeightSizer(mulMiddle)->setWidthSizer(mulWidth)->
            setHeightSizer(normalSize)->setWidthSizer(normalSize), true))->append(
        (new VectorPane())->setSizer(normalWidth))->append(
        (new SpanSetPane(SpanSet(3, 3), true))->setSizer(normalWidth)->vecSizer(normalHeight)->hasSpan(false)), 2));
    content->addWidget(equal);
    content->addWidget(registerOperand((new GenericPane(this,
        new MatrixPane(nullptr, Matrix(3, 3), false), false))->append(
        resPane = new SpanSetPane(SpanSet(), false)), 3));
    content->addItem(getHorizontalSpacer());

    AbstractPage::switchTo(&calculationdefinition[0]);
}

void MatrixPage::switchTo(const Calculation *nextCalculation){
    resPane->hasSpan(true);
    switch(nextCalculation->sign){
    case BASE:
        resPane->hasSpan(false);
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
        break;
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
