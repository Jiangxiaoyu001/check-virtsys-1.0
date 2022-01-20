#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace BASEWINDOW {
    class check_virtsys_basewindow;
}
QT_END_NAMESPACE

class MainWindow
{
    //Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    BASEWINDOW::check_virtsys_basewindow * _baseWidPrt_;
private:
    void MainWindowInit();

};
#endif // MAINWINDOW_H
