#ifndef CONTROLPANE_H
#define CONTROLPANE_H

#include "sizerbar.h"
#include <QObject>
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>

class ControlPane : public QStackedWidget
{
    Q_OBJECT

public:
    ControlPane(QWidget *parent);

    ControlPane *addPage();

    ControlPane *addResizer(ResizeBar *resizer);

    void switchTo(int page);

private:
    QVBoxLayout *currentPageLayout;
    std::vector<std::vector<ResizeBar *>> resizers;
};

#endif // CONTROLPANE_H
