#include <iostream>
#include <checkVirsys/mainwindow.h>
//#include "ui_mainwindow.h"
#include <checkVirsys/check_virtsys_window.h>


enum sortMethod{};

class MainWindow::baseWindow:public QWidget{
public:
    baseWindow(QWidget * parent=nullptr);
    ~baseWindow();
private:
    QStackedWidget * bStaWid;
    /* declare friend class*/
    friend class MainWindow;
    QWidget * _baseWin_();
    void baseWindowInit();
    void _setBaseStaWid_(QStackedWidget * staWid);
    QStackedWidget *_baseStaWid_();
    //void basewin_init(QWidget *wid);
    void addWindow(QWidget *wid);
    void removeWindow(QWidget * wid);
    void sortWindow(sortMethod sort);
    void setFrontWindow(QWidget *wid);
    /* scan  and load widget configure*/
    QWidget * getFrontWindow();
    //void insert_window(UINT16 pre_site,UINT16 nxt_site,QWidget wid);
    unsigned short get_allCount_windows();
    unsigned short get_showedCount_windows();
    unsigned short get_hidedCount_windows();
};


 MainWindow * MainWindow::Interface=nullptr;
 MainWindow * MainWindow::getInface(){
     if(!Interface){
        Interface = new  MainWindow;
     }
     return Interface;
 }

MainWindow::MainWindow(QWidget *parent):FramelessWidget(parent),
    m_edgeCalc(false),
    baseWinPimpl(nullptr)
{
    MainWindowInit();
    MainWindowCtr();
}

MainWindow::~MainWindow()
{
}

MainWindow::baseWindow *MainWindow::_baseWinPimpl_()
{
    if(!baseWinPimpl)
        baseWinPimpl=new baseWindow();
    return baseWinPimpl;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    return FramelessWidget::paintEvent(event);
}



void MainWindow::MainWindowInit()
{
    setWindowIco();
    QRect rect(0,0,1920,1080);
    //QRect rect(0,0,1000,800);
    setGeometry(rect);
    this->setWindowTitle("check virtsys");
    setMinimumSize(400,400);
    QDesktopWidget *deskdop = QApplication::desktop();
    static_cast<QWidget *>(this)->move((deskdop->width() - this->width())/2,
                                        (deskdop->height() - this->height())/2);

     setCentralWidget(_baseWinPimpl_()->_baseWin_());

}

void MainWindow::MainWindowCtr()
{
    Check_Virtsys_Window * virtWin;
    virtWin=new Check_Virtsys_Window(_baseWinPimpl_()->_baseStaWid_());
    addWindows(virtWin);
    /* default front window */
    setFrontWindow(virtWin);

}

void MainWindow::createLayout()
{
    QGridLayout *griLay=new QGridLayout();
    this->setLayout(griLay);
}

void MainWindow::setWindowIco()
{
//    static_cast<QWidget *>(this)->
     setWindowIcon(QIcon(":/resources/virsys.ico"));
}



void MainWindow::addWindows(QWidget *wid)
{
    _baseWinPimpl_()->addWindow(wid);

}

void MainWindow::removeWindows(QWidget *wid)
{
    _baseWinPimpl_()->removeWindow(wid);
}

void MainWindow::setFrontWindow(QWidget *wid)
{
     _baseWinPimpl_()->setFrontWindow(wid);
}

QWidget *MainWindow::getFrontWindow()
{
    return nullptr;
}



/*
 * base Interface implementation
*/
MainWindow::baseWindow::baseWindow(QWidget *parent):
    QWidget(parent),
    bStaWid(nullptr)
{
    baseWindowInit();
}

MainWindow::baseWindow::~baseWindow()
{

}

QWidget *MainWindow::baseWindow::_baseWin_()
{
    return this;
}

void MainWindow::baseWindow::baseWindowInit()
{
    setWindowFlags(Qt::FramelessWindowHint);
    bStaWid=new QStackedWidget(this);
    QVBoxLayout * vBlayout = new QVBoxLayout();
    vBlayout->addWidget(bStaWid);
    setLayout(vBlayout);
    setAutoFillBackground(true);
    QPalette p = palette();
    p.setColor(QPalette::Window,QColor(100,100,105));
    setPalette(p);
}

void MainWindow::baseWindow::_setBaseStaWid_(QStackedWidget * staWid)
{
    bStaWid=staWid;
}

QStackedWidget *MainWindow::baseWindow::_baseStaWid_()
{
    return bStaWid;
}



void MainWindow::baseWindow::addWindow(QWidget *wid)
{
    _baseStaWid_()->addWidget(wid);
}

void MainWindow::baseWindow::removeWindow(QWidget *wid)
{
    _baseStaWid_()->removeWidget(wid);
}

void MainWindow::baseWindow::sortWindow(sortMethod sort)
{
    //UNUSE(sort)
}

void MainWindow::baseWindow::setFrontWindow(QWidget *wid)
{
    if(wid){
        bStaWid->setCurrentWidget(wid);
    }else{
        bStaWid->setCurrentIndex(0);
    }
}

QWidget *MainWindow::baseWindow::getFrontWindow()
{
    return nullptr;
}


