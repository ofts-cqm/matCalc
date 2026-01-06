#ifndef SPANSETPANE_H
#define SPANSETPANE_H

#include "abstractnumberpane.h"
#include "sizerbar.h"
#include "spanset.h"
#include <QWidget>

namespace Ui {
class SpanSetPane;
}

class SpanSetPane : public AbstractNumberPane
{
    Q_OBJECT

public:
    explicit SpanSetPane(SpanSet value, bool editable, QWidget *parent = nullptr);
    ~SpanSetPane();

    virtual void display(GenericNumber num);

    virtual void paste(GenericNumber num);

    virtual void reconstructPage();

    virtual const GenericNumber *getValue();

    virtual QSize sizeHint() const;

    virtual QSize minimumSizeHint() const;

    SpanSetPane *vecSizer(ResizeBar *bar);

    SpanSetPane *setSizer(ResizeBar *bar);

private slots:
    void onVecFieldChanged(int id, int pos, double val);

private:
    Ui::SpanSetPane *ui;
    bool editable;
    SpanSet value;
};

#endif // SPANSETPANE_H
