#ifndef VECTORPAGE_H
#define VECTORPAGE_H

#include "abstractpage.h"
#include "vectorpane.h"
#include <QWidget>
#include <QtWidgets/qspinbox.h>

class VectorPage : public AbstractPage
{
    Q_OBJECT

public:
    explicit VectorPage(QWidget *parent = nullptr);
    ~VectorPage();

    const static Calculation calculationDefinition[];

    virtual void switchTo(const Calculation *nextCalculation);

    VectorPage *fillIndexPage(QWidget *parent);

private:
    QSpinBox *dimension;
    VectorPane *primaryPane;
    ResizeBar *resizeBar;
};

#endif // VECTORPAGE_H
