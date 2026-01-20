#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtWidgets/qboxlayout.h>

class HistoryWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit HistoryWindow(QWidget *parent = nullptr);

    void refreshHistory();

    static HistoryWindow *instance;

private:
    QVBoxLayout *contentLayout;
    QWidget *content;
};

#endif // HISTORYWINDOW_H
