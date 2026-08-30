#ifndef VECTORPAGE_H
#define VECTORPAGE_H

#include "abstractpage.h"
#include "../panes/vectorpane.h"
#include <QWidget>
#include <QtWidgets/qspinbox.h>

class VectorPage : public AbstractPage
{
    Q_OBJECT

public:
    explicit VectorPage(QWidget *parent = nullptr);
    const static Calculation calculationDefinition[];

    virtual void switchTo(const Calculation &nextCalculation);

    VectorPage *fillIndexPage(QWidget *parent);

private:
    SignPane *alternativSign;
    VectorPane *primaryPane = nullptr;
    ResizeBar *resizeBar;
};

#endif // VECTORPAGE_H
