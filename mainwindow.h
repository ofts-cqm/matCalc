#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "calculatorPage/abstractpage.h"
#include "history/historywindow.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    static void setPage(AbstractPage *);
    static AbstractPage *setPage(History::Page page);
    static void setMessage(QString str);
    static MainWindow *getInstance();
    ~MainWindow();

    HistoryWindow *historyWindow;

private:
    Ui::MainWindow *ui;
    static MainWindow *instance;

    AbstractPage *matPage, *vecPage;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void openHistory();
};
#endif // MAINWINDOW_H
