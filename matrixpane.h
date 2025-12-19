#ifndef MATRIXPANE_H
#define MATRIXPANE_H

#include <QObject>
#include <QWidget>
#include "abstractnumberpane.h"
#include "matrix.h"
#include "sizerbar.h"
#include "ui_vectorpane.h"

class MatrixPane : public AbstractNumberPane
{
    Q_OBJECT

public:
    explicit MatrixPane(QWidget *parent = nullptr, Matrix mat = Matrix(3, 3), bool editable = true);

    virtual void display(GenericNumber matrix);

    virtual void paste(GenericNumber num);

    virtual void reconstructPage();

    virtual const GenericNumber *getValue();

    MatrixPane *setHeightSizer(ResizeBar *bar);

    MatrixPane *setWidthSizer(ResizeBar *bar);

    MatrixPane *setSquareSizer(ResizeBar *bar);

    int getHeight() const;

    int getWidth() const;

    void resizeMatrix(int height = -1, int width = -1);

    void resizeMatrix(int size);

private:
    Ui::VectorPane *ui;
    bool editable;
    Matrix value;
};

#endif // MATRIXPANE_H
