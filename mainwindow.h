#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "abstractpage.h"
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
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    static MainWindow *instance;
};
#endif // MAINWINDOW_H
