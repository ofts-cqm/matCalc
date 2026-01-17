#ifndef DECIMALLINEEDIT_H
#define DECIMALLINEEDIT_H

#include <QLineEdit>
#include <optional>
#include <functional>

class DecimalLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    using Parser = std::function<std::optional<double>(QStringView)>;
    using Setter = std::function<void(double)>;

    DecimalLineEdit(const Parser parser,
                    const Setter setter,
                    double initial,
                    QWidget* parent = nullptr);

    void setValue(double val);

protected:
    void focusInEvent(QFocusEvent* event) override;

private slots:
    void onTextEdited(const QString& text);
    void onEditingFinished();
    void onEnterPressed();

private:
    const Parser parserFunc;
    const Setter setterFunc;

    bool formal = false;
    void setError(bool enabled);
};


#endif // DECIMALLINEEDIT_H
