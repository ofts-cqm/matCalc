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

private:
    QSpinBox *dimension;
    VectorPane *primaryPane;  
};

#endif // VECTORPAGE_H
