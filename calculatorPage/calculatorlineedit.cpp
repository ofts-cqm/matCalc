#include "calculatorlineedit.h"
#include "../util.h"
#include "../calc/calculator.h"
#include "../history/calculationhistory.h"

CalculatorLineEdit::CalculatorLineEdit(QWidget *parent)
    : QPlainTextEdit(parent) {
    this->setFont(getLargeFont());
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CalculatorLineEdit::focusInEvent(QFocusEvent *event){
    QPlainTextEdit::focusInEvent(event);
    selectAll();
    if (hasError){
        document()->clear();
        hasError = false;
    }
}

void CalculatorLineEdit::keyPressEvent(QKeyEvent *event){
    if (event->key() != Qt::Key_Enter && event->key() != Qt::Key_Return){
        QPlainTextEdit::keyPressEvent(event);
        return;
    }

    evaluate();
}

void CalculatorLineEdit::appendInput(const QString &str){
    this->textCursor().insertText(str);
}

void CalculatorLineEdit::clearInput(){
    this->document()->clear();
    if (hasError) hasError = false;
}

void CalculatorLineEdit::evaluate(){
    std::optional<double> result = Calculator::evaluate(toPlainText().toStdString(), true);
    if (result.has_value()) {
        History::addHistory(History::Page::CALCULATOR, EQU, toPlainText().toStdString(), GenericNumber::unknown, result.value());
        setPlainText(format(result.value()));
        selectAll();
    }
    else{
        setPlainText(QString::fromStdString(Calculator::getLongErrorMessage()));
        hasError = true;
        this->textCursor().clearSelection();
        this->parentWidget()->setFocus();
    }
}
