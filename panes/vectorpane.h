#ifndef VECTORPANE_H
#define VECTORPANE_H

#include <QWidget>
#include "abstractnumberpane.h"
#include "../calculatorPage/sizerbar.h"
#include "../numbers/vector.h"

namespace Ui {
class VectorPane;
}

class VectorPane : public AbstractNumberPane
{
    Q_OBJECT

public:
    explicit VectorPane(QWidget *parent = nullptr, Vector vec = Vector(3), bool editable = true);
    ~VectorPane();

    virtual void display(GenericNumber vector) override;

    virtual void paste(GenericNumber num) override;

    virtual void reconstructPage() override;

    virtual const GenericNumber *getValue() override;

    const Vector *getPrivateValue();

    VectorPane *setSizer(ResizeBar *bar);

    void resizeVector(int size);

    VectorPane *setID(int id);

private:
    Ui::VectorPane *ui;
    bool editable;
    Vector value;
    int id = -1;

Q_SIGNALS:
    void onFieldChanged(int id, int pos, double val);
};

#endif // VECTORPANE_H
