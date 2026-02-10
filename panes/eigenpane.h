#ifndef EIGENPANE_H
#define EIGENPANE_H

#include "abstractnumberpane.h"
#include <QObject>
#include <QWidget>
#include <QBoxlayout>
#include <QPushbutton>
#include <QStackedwidget>

class EigenPane : public AbstractNumberPane
{
    Q_OBJECT
public:
    explicit EigenPane(const EigenSpace &space, QWidget *parent = nullptr);

    virtual void reconstructPage() override;

    virtual void display(GenericNumber num) override;
    virtual void paste(GenericNumber num) override;

private:
    QVBoxLayout *content;
    QHBoxLayout *buttonBox;
    QStackedWidget *spaces;
    QPushButton *prev, *next;
    int currentIndex;
    EigenSpace eigen;

private slots:
    void onPrevPressed();
    void onNextPressed();
};

#endif // EIGENPANE_H
