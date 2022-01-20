
#include <iostream>
#include "mainwindow.h"
//#include "ui_mainwindow.h"

#include "check_virtsys_window.h"
#include "check_virtsys_basewindow.h"

MainWindow::MainWindow(QWidget *parent):
    _baseWidPrt_(new BASEWINDOW::check_virtsys_basewindow())

{
    MainWindowInit();
}

MainWindow::~MainWindow()
{

}

void MainWindow::MainWindowInit()
{
    Check_Virtsys_Window * virtWin=new Check_Virtsys_Window(_baseWidPrt_->_baseStaWid_());
    _baseWidPrt_->checkvirtsys_setFront_window(virtWin);
    _baseWidPrt_->checkvirtsys_add_window(virtWin);
}



