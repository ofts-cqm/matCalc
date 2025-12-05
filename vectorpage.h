#ifndef VECTORPAGE_H
#define VECTORPAGE_H

#include "abstractpage.h"
#include <QWidget>
#include <QtWidgets/qspinbox.h>

class VectorPage : public AbstractPage
{
    Q_OBJECT

public:
    explicit VectorPage(QWidget *parent = nullptr);
    ~VectorPage();

private:
    QSpinBox *dimension;
};

#endif // VECTORPAGE_H
