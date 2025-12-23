#ifndef MATRIXPAGE_H
#define MATRIXPAGE_H

#include "abstractpage.h"
#include "matrixpane.h"

class MatrixPage : public AbstractPage
{
    Q_OBJECT
public:
    explicit MatrixPage(QWidget *parent = nullptr);

    const static Calculation calculationdefinition[];

    virtual void switchTo(const Calculation *nextCalculation);

    MatrixPage *fillIndexPage(QWidget *parent);

private:
    static int primeHeight();
    static int primeWidth();
    static int seoncdWidth();
    static MatrixPane *primaryPane, *secondaryPane;
    ResizeBar *normalHeight, *normalWidth, *mulHeight, *mulWidth, *mulMiddle;
};

#endif // MATRIXPAGE_H
