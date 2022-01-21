#include "check_virtsys_window.h"
#include "check_virtsys_basewindow.h"

using namespace BASEWINDOW;






class check_virtsys_basewindow::baseWindow:public QWidget{
public:
    baseWindow(QWidget * parent=nullptr);
    ~baseWindow();
    QWidget * _baseWin_();
    QStackedWidget *_baseStaWid_();
    void basewin_init(QWidget *wid);
    void add_window(QWidget *wid);
    void delete_window(QWidget * wid);
    void sort_window(sortMethod sort);

    /* scan  and load widget configure*/



    /*   */
    void set_front_window(QWidget *wid);
    QWidget * get_front_window();
    void insert_window(UINT16 pre_site,UINT16 nxt_site,QWidget wid);
    unsigned short get_allCount_windows();
    unsigned short get_showedCount_windows();
    unsigned short get_hidedCount_windows();
protected:
    /* override mouse event to re-run window move*/
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    /*platform :windows*/
    //bool nativeEvent(const QByteArray &eventType, void *message, long *result)override;
private:
    QWidget * frontWid;
      /* define basewin point*/
    QWidget *m_baseWid;
    QStackedWidget *m_staWid;
    /*mouse last point*/
    QPoint lastPos;
    QPoint windowPos;
    bool m_Pressed;
    bool m_edgeCalc;
    /*calculation the desktop edge to move */
    void edgeCalcMove();
};



check_virtsys_basewindow::check_virtsys_basewindow():
    baseWinPimpl(new baseWindow())
{
    this->check_objcls_isExist();
    checkvirtsys_baseWinInit();
}

check_virtsys_basewindow::~check_virtsys_basewindow()
{

}

QStackedWidget *check_virtsys_basewindow::_baseStaWid_()
{
    return baseWinPimpl->_baseStaWid_();
}

void check_virtsys_basewindow::checkvirtsys_baseWinInit()
{
    baseWinPimpl->basewin_init(baseWinPimpl->_baseWin_());
}




void check_virtsys_basewindow::checkvirtsys_add_window(QWidget *wid)
{
    baseWinPimpl->add_window(wid);
}

void check_virtsys_basewindow::checkvirtsys_delete_window(QWidget *wid)
{
    baseWinPimpl->delete_window(wid);
}

void check_virtsys_basewindow::checkvirtsys_setFront_window(QWidget *wid)
{

}

check_virtsys_basewindow::baseWindow *check_virtsys_basewindow::_baseWinPimpl_()
{
    return baseWinPimpl;
}

void check_virtsys_basewindow::check_objcls_isExist()
{
    if(!baseWinPimpl)
         baseWinPimpl=new baseWindow() ;
    return ;
}







/* base windows to provide base management sub-windows*/


check_virtsys_basewindow::baseWindow::baseWindow(QWidget *parent):
    QWidget(parent),
    m_baseWid(this),
    m_staWid(new QStackedWidget(_baseWin_())),
    lastPos(0,0),
    windowPos(0,0),
    m_Pressed(false),
    m_edgeCalc(false)
{

}

check_virtsys_basewindow::baseWindow::~baseWindow()
{

}

void check_virtsys_basewindow::baseWindow::basewin_init(QWidget *wid)
{
    QRect rect(0,0,1920,1080);
    QRect sta_rect(0,64,1920,1016);
    wid->setGeometry(rect);
    m_staWid->setGeometry(sta_rect);
    /* remove window frame */

    wid->setWindowFlags(Qt::FramelessWindowHint);
//    wid->setWindowFlags( Qt::WindowSystemMenuHint
//                        |Qt::FramelessWindowHint
//                        |Qt::WindowMinMaxButtonsHint);


    QPushButton * maxBtn=new QPushButton(this);
    QPushButton * minBtn=new QPushButton(this);
    QPushButton * closeBtn=new QPushButton(this);

    QGridLayout *griLay=new QGridLayout(this);
    griLay->setGeometry(rect);
    griLay->addWidget(maxBtn,0,0,0,0);
    QPalette m_pal;
    //this->setCentralWidget(this);
    this->setWindowTitle("check virtsys");
   // this->setFixedSize(900,900);
//setAttribute(Qt::WA_TransparentForMouseEvents,false);
//    this->resize(900,600);
    m_pal.setColor(QPalette::Background,QColor(100,100,105));

    this->setAutoFillBackground(m_staWid);
    this->setPalette(m_pal);
}

void check_virtsys_basewindow::baseWindow::add_window(QWidget *wid)
{
    /* set parent-widget*/
    wid->setParent(_baseStaWid_());
   _baseStaWid_()->addWidget(wid);

   _baseStaWid_()->setCurrentWidget(get_front_window());
   qDebug()<<"this is test";
   this->show();
}

void check_virtsys_basewindow::baseWindow::delete_window(QWidget *wid)
{

}

void check_virtsys_basewindow::baseWindow::set_front_window(QWidget *wid)
{
    frontWid=wid;
}

QWidget * check_virtsys_basewindow::baseWindow::get_front_window()
{
    return frontWid;
}


/*mouse event*/

void check_virtsys_basewindow::baseWindow::mouseMoveEvent(QMouseEvent *event)
{

    /*if current window is Max , allowend not to move*/
    if(this->isMaximized())
        return;
    if(event->buttons()&Qt::LeftButton &&m_Pressed){
        /*temp_p(current  pos) - lastpoint(lsat  pos) = */
        QPoint temp=event->globalPos()-lastPos;
        temp=temp+windowPos; /*( pos) + (original pos) = current pos*/
        //qDebug()<<"this->pos():"<<this->pos()<<"---->> windowPos:"<<windowPos;
        QRect _rec=QApplication::desktop()->availableGeometry();
        if(m_edgeCalc){
            /*enable edge calc*/
            return;
        }else{
            this->move(temp);
        }
    }
    qDebug()<<"event->pos:"<<event->pos()<<"=====>>> event->globalPos:"<<event->globalPos();
    QWidget::mouseMoveEvent(event);
}

void check_virtsys_basewindow::baseWindow::mousePressEvent(QMouseEvent *event)
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

void check_virtsys_basewindow::baseWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        m_Pressed=false;
        QApplication::restoreOverrideCursor();//restore mouse style
    }
     QWidget::mouseReleaseEvent(event);
}

void check_virtsys_basewindow::baseWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    //QWidget::mouseDoubleClickEvent(event);
}

void check_virtsys_basewindow::baseWindow::edgeCalcMove()
{

}

QStackedWidget *check_virtsys_basewindow::baseWindow::_baseStaWid_()
{
 return m_staWid;
}

QWidget *check_virtsys_basewindow::baseWindow::_baseWin_()
{
    return m_baseWid;
}



