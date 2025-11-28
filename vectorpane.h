#ifndef VECTORPANE_H
#define VECTORPANE_H

#include <QWidget>
#include "vector.h"

namespace Ui {
class VectorPane;
}

class VectorPane : public QWidget
{
    Q_OBJECT

public:
    explicit VectorPane(QWidget *parent = nullptr, Vector vec = {}, bool editable = true);
    ~VectorPane();

private:
    Ui::VectorPane *ui;
    Vector value;
    bool editable;
};

#endif // VECTORPANE_H
