#include "decimallineedit.h"

#include <QFocusEvent>
#include <QPalette>
#include "util.h"

DecimalLineEdit::DecimalLineEdit(
    const Parser parser,
    const Setter setter,
    double initial,
    QWidget* parent)
    : QLineEdit(format(initial), parent),
    parserFunc(std::move(parser)),
    setterFunc(std::move(setter))
{
    connect(this, &QLineEdit::textEdited,
            this, &DecimalLineEdit::onTextEdited);
    this->setFont(getLargeFont());
}

void DecimalLineEdit::focusInEvent(QFocusEvent* event)
{
    QLineEdit::focusInEvent(event);
    selectAll();
}

void DecimalLineEdit::onTextEdited(const QString& text)
{
    if (!parserFunc)
        return;

    std::optional<double> result = parserFunc(QStringView{text});

    if (result.has_value()) {
        setError(false);
        setterFunc(result.value());
    } else {
        setError(true);
    }
}

void DecimalLineEdit::setError(bool enabled)
{
    QPalette p = palette();
    if (enabled)
        p.setColor(QPalette::Base, QColor(255, 200, 200)); // redish
    else
        p.setColor(QPalette::Base, Qt::white);

    setPalette(p);
}
