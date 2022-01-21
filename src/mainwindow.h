#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMouseEvent>
#include <QPaintEvent>
#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace BASEWINDOW {
    //class check_virtsys_basewindow;
}
QT_END_NAMESPACE

class MainWindow:public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //BASEWINDOW::check_virtsys_basewindow * _baseWidPrt_;
protected:
    void paintEvent(QPaintEvent* event) override;
    /* override mouse event to re-run window move*/
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    /*platform :windows*/
    //bool nativeEvent(const QByteArray &eventType, void *message, long *result)override;
private:
    class baseWindow;
    bool m_Pressed;
    bool m_edgeCalc;
    QPoint lastPos;
    QPoint currPos;
    QPoint windowPos;
    QWidget * frontWin;
    QStackedWidget * bStaWid;
    baseWindow * baseWinPimpl;
    baseWindow * _baseWinPimpl_();


    void MainWindowInit();
    void MainWindowCtr();
    void createLayout();
    void addWindows(QWidget *wid);
    void removeWindows(QWidget *wid);
    void setFrontWindow(QWidget *wid);
    QWidget * getFrontWindow();
    void _setBaseStaWid_(QStackedWidget * staWid);
};
#endif // MAINWINDOW_H
