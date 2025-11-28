#ifndef VECTORPAGE_H
#define VECTORPAGE_H

#include <QWidget>
#include <QtWidgets/qspinbox.h>

class VectorPage : public QWidget
{
    Q_OBJECT

public:
    explicit VectorPage(QWidget *parent = nullptr);
    ~VectorPage();

private:
    QSpinBox *dimension;
};

#endif // VECTORPAGE_H
