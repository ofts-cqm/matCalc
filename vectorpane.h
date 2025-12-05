#ifndef VECTORPANE_H
#define VECTORPANE_H

#include <QWidget>
#include "abstractnumberpane.h"
#include "vector.h"

namespace Ui {
class VectorPane;
}

class VectorPane : public AbstractNumberPane
{
    Q_OBJECT

public:
    explicit VectorPane(QWidget *parent = nullptr, Vector vec = Vector(3), bool editable = true);
    ~VectorPane();

    void display(Vector vector);

    void reconstructPage();

private:
    Ui::VectorPane *ui;
    bool editable;
    Vector value;
};

#endif // VECTORPANE_H
