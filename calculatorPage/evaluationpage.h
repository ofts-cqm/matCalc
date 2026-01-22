#ifndef EVALUATIONPAGE_H
#define EVALUATIONPAGE_H

#include <QWidget>
#include <QMainWindow>
#include "calculatorlineedit.h"

namespace Ui {
class EvaluationPage;
}

class EvaluationPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit EvaluationPage(QWidget *parent = nullptr);
    ~EvaluationPage();

    static EvaluationPage *instance;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onButtonPressed();

private:
    Ui::EvaluationPage *ui;
    CalculatorLineEdit *input;
};

#endif // EVALUATIONPAGE_H
