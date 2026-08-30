#ifndef MATRIXPAGE_H
#define MATRIXPAGE_H

#include "abstractpage.h"
#include "../panes/matrixpane.h"
#include "../panes/spansetpane.h"

class MatrixPage : public AbstractPage
{
    Q_OBJECT
public:
    explicit MatrixPage(QWidget *parent = nullptr);

    const static Calculation calculationdefinition[];

    virtual void switchTo(const Calculation &nextCalculation);

    MatrixPage *fillIndexPage(QWidget *parent);

private:
    MatrixPane *primaryPane = nullptr, *secondaryPane = nullptr;
    SpanSetPane *resPane = nullptr;
    ResizeBar *normalHeight, *normalWidth, *mulHeight, *mulWidth, *mulMiddle, *normalSize;
};

#endif // MATRIXPAGE_H
