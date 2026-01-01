#ifndef LABELPANE_H
#define LABELPANE_H

#include "abstractnumberpane.h"
#include <QLabel>

class LabelPane : public AbstractNumberPane
{
    Q_OBJECT
public:
    LabelPane(QString label, QWidget *parent = nullptr);

    virtual void reconstructPage() override;

    virtual void display(GenericNumber num) override;

    virtual void paste(GenericNumber num) override;
private:
    QLabel *label;
};

#endif // LABELPANE_H
