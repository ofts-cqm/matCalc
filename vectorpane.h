#ifndef VECTORPANE_H
#define VECTORPANE_H

#include <QWidget>
#include "abstractnumberpane.h"
#include "vector.h"

namespace Ui {
class VectorPane;
}

class VectorPane : public QWidget, public AbstractNumberPane<Vector>
{
    Q_OBJECT

public:
    explicit VectorPane(QWidget *parent = nullptr, Vector vec = {}, bool editable = true);
    ~VectorPane();

    void display(Vector vector);

    void reconstructPage();


private:
    Ui::VectorPane *ui;
    bool editable;
};

#endif // VECTORPANE_H
