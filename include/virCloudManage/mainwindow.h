#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QMainWindow>
#include <QStackedWidget>
#include <QApplication>
#include "widgets/framelesswidget.h"
QT_BEGIN_NAMESPACE
namespace BASEWINDOW {
    //class check_virtsys_basewindow;
}
QT_END_NAMESPACE


class MainWindow:public FramelessWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow * Interface;
    static MainWindow * getInface();
private:
    void paintEvent(QPaintEvent* event) override;
private:
    class baseWindow;
    bool m_edgeCalc;

    baseWindow * baseWinPimpl;
    baseWindow * _baseWinPimpl_();
    void MainWindowInit();
    void MainWindowCtr();
    void createLayout();
    void setWindowIco();
    QStackedWidget * baseStaWid();
    void addWindows(QWidget *wid);
    void removeWindows(QWidget *wid);
    void setFrontWindow(QWidget *wid);
    QWidget * getFrontWindow();
    void _setBaseStaWid_(QStackedWidget * staWid);
};


#endif // MAINWINDOW_H
