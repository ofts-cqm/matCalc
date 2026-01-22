#ifndef CALCULATORLINEEDIT_H
#define CALCULATORLINEEDIT_H

#include <QObject>
#include <QPlainTextedit>

class CalculatorLineEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    CalculatorLineEdit(QWidget *parent = nullptr);

    void appendInput(const QString &str);

    void clearInput();

    void evaluate();

protected:
    virtual void focusInEvent(QFocusEvent* event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    bool hasError = false;
};

#endif // CALCULATORLINEEDIT_H
