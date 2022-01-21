
#include <iostream>
#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include "check_virtsys_window.h"


enum sortMethod{};

class MainWindow::baseWindow{
public:
    baseWindow();
    ~baseWindow();
private:

    QStackedWidget * bStaWid;
    /* declare friend class*/
    friend class MainWindow;
    QWidget * _baseWin_();
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




MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),
    m_Pressed(false),
    m_edgeCalc(false),
    lastPos(0,0),
    currPos(0,0),
    windowPos(0,0),
    frontWin(nullptr),
    bStaWid(nullptr),
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
//    QPainter painter(this);
//    painter.begin(this);
//    //painter.setCompositionMode( QPainter::CompositionMode_Clear );
//    painter.setBrush(QBrush(QColor(100,100,105)));
//    painter.fillRect(0,64,1920,1080,Qt::SolidPattern);
//    painter.end();
    QWidget::paintEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    /*if current window is Max , allowend not to move*/
   if(this->isMaximized())
       return;
   if(event->buttons()&Qt::LeftButton &&m_Pressed){
       /*temp_p(current  pos) - lastpoint(lsat  pos) = */
       QPoint temp=event->globalPos()-lastPos;
       temp=temp+windowPos; /*( pos) + (original pos) = current pos*/
       QRect _rec=QApplication::desktop()->availableGeometry();
       if(m_edgeCalc){
           /*enable edge calc*/
           return;
       }else{
           this->move(temp);
       }
   }
  // qDebug()<<"event->pos:"<<event->pos()<<"=====>>> event->globalPos:"<<event->globalPos();
   QWidget::mouseMoveEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // this->setFocus();&&Qt::WindowMaximized && this->windowState()==0
        if(event->button()==Qt::LeftButton){
            lastPos=event->globalPos();
            windowPos=this->pos();
            event->ignore();
            m_Pressed=true;
        }
        QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
           m_Pressed=false;
           QApplication::restoreOverrideCursor();//restore mouse style
       }
    QWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    return mouseDoubleClickEvent(event);
}

void MainWindow::MainWindowInit()
{
    QRect rect(0,0,1920,1080);
    QRect sta_rect(0,64,1920,1016);
    setGeometry(rect);
    bStaWid=new QStackedWidget(this);
    bStaWid->setGeometry(sta_rect);
    /* remove window frame */
    setWindowFlags(Qt::FramelessWindowHint);
    /*
    setWindowFlags(Qt::FramelessWindowHint |
                    Qt::WindowSystemMenuHint
                    |Qt::FramelessWindowHint
                    |Qt::WindowMinMaxButtonsHint);

    */
    QPushButton * maxBtn=new QPushButton(this);
    QPushButton * minBtn=new QPushButton(this);
    QPushButton * closeBtn=new QPushButton(this);



    this->setWindowTitle("check virtsys");
   // this->setFixedSize(900,900);
    //setAttribute(Qt::WA_TransparentForMouseEvents,false);
    //    this->resize(900,600);

    QPalette m_pal;
    m_pal.setColor(QPalette::Background,QColor(100,100,105));
    this->setPalette(m_pal);
    this->setAutoFillBackground(true);
//    setCentralWidget(bStaWid);


    //QGridLayout *gridlayout=new QGridLayout();
    QHBoxLayout * hlayout=new QHBoxLayout();
    //hlayout->addStretch();/*add strecth */
    hlayout->addSpacing(50);
    hlayout->addWidget(minBtn,0);
    hlayout->addSpacing(50);
    hlayout->addWidget(minBtn,0);
    hlayout->addSpacing(50);
    hlayout->addWidget(closeBtn,0);
    hlayout->addSpacing(20);
//    setLayout(hlayout);
    //gridlayout->addLayout(hlayout,0,0,1,1);
    //gridlayout->addWidget(bStaWid,1,0,0,0);
//    gridBox->addWidget(maxBtn,0,0,0,0);



}

void MainWindow::MainWindowCtr()
{
    Check_Virtsys_Window * virtWin;
    virtWin=new Check_Virtsys_Window(this->bStaWid);
    _setBaseStaWid_(bStaWid);
    addWindows(virtWin);
    /* default front window */
    setFrontWindow(virtWin);
}

void MainWindow::createLayout()
{
    QGridLayout *griLay=new QGridLayout();
    this->setLayout(griLay);
}

void MainWindow::_setBaseStaWid_(QStackedWidget * staWid)
{
    _baseWinPimpl_()->_setBaseStaWid_(staWid);
}

void MainWindow::addWindows(QWidget *wid)
{
    //qDebug()<<"=====>> test";
    _baseWinPimpl_()->addWindow(wid);

}

void MainWindow::removeWindows(QWidget *wid)
{
    _baseWinPimpl_()->removeWindow(wid);
}

void MainWindow::setFrontWindow(QWidget *wid)
{
    if(wid){
        this->frontWin=wid;
        bStaWid->setCurrentWidget(frontWin);
    }else{
        bStaWid->setCurrentIndex(0);
    }
}

QWidget *MainWindow::getFrontWindow()
{
    return frontWin;
}



/*
 * base Interface implementation
*/
MainWindow::baseWindow::baseWindow():
    bStaWid(nullptr)
{

}

MainWindow::baseWindow::~baseWindow()
{

}

QWidget *MainWindow::baseWindow::_baseWin_()
{
    return nullptr;
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

QWidget *MainWindow::baseWindow::getFrontWindow()
{
    return nullptr;
}
