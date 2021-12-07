#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "check_virtsys_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStackedWidget *m_staWidget;
    Check_Virtsys_Window * window;
private:
    void MainWindowInit();
    void mousePressEvent(QMouseEvent *event){
        qDebug()<<"----mainWidget mousePressEvent--------"<<endl;
        event->ignore();
//        return QWidget::mouseMoveEvent(event);
    }
};
#endif // MAINWINDOW_H
