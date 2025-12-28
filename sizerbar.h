#ifndef SIZERBAR_H
#define SIZERBAR_H

#include <QObject>
#include <QWidget>
#include <QSlider>
#include <functional>

class ResizeBar: public QWidget
{
    Q_OBJECT

public:
    using DimSrc = std::function<int(void)>;
    using DimTar = std::function<void(int)>;

    ResizeBar(QString name, DimSrc source, QWidget *parent);

    ResizeBar *addTarget(DimTar target);

    void reload();

    void close();

private slots:
    void onSliderReleased();

private:
    DimSrc source;
    QSlider *slider;
    std::vector<DimTar> targets;
    bool internalReload;
};

#endif // SIZERBAR_H
