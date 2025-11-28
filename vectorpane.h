#ifndef VECTORPANE_H
#define VECTORPANE_H

#include <QWidget>
#include <vector>

namespace Ui {
class VectorPane;
}

class VectorPane : public QWidget
{
    Q_OBJECT

public:
    explicit VectorPane(QWidget *parent = nullptr, std::vector<int> vec = {});
    ~VectorPane();

private:
    Ui::VectorPane *ui;
};

#endif // VECTORPANE_H
