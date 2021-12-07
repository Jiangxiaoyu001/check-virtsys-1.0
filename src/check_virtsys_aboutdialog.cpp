#include "check_virtsys_aboutdialog.h"
#include "check_virtsys_manager.h"


CHECK_VIRTSYS_ABOUTDIALOG::CHECK_VIRTSYS_ABOUTDIALOG(QWidget *parent):
    QWidget(parent),
    virManager(CHECK_VIRTSYS_MANAGER::check_virtsys_managerObj())
{
    //    check_virtsys_aboutDialogInit();
//    qDebug()<<this->parent();
}

CHECK_VIRTSYS_ABOUTDIALOG::~CHECK_VIRTSYS_ABOUTDIALOG()
{

}




void CHECK_VIRTSYS_ABOUTDIALOG::check_virtsys_aboutDialogInit()
{

    QFont m_font("Microsoft YaHei",13);
    QPalette m_pale(this->palette());
    m_pale.setColor(QPalette::Background,Qt::white);
    QWidget * parentWin=this->parentWidget();
    QSize  m_size(parentWin->width(),parentWin->height());
    QPoint m_point(parentWin->pos().x(),parentWin->pos().y());

    this->resize(m_size.width(),m_size.height());

    this->setAutoFillBackground(true);
    this->setPalette(m_pale);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Widget);
    this->hide();

    m_label=new QLabel(this);
//    m_label->setFixedWidth(150);
    m_label->setFont(m_font);
    m_label->setText("软件: check virtsys"); //tool
    m_label->move(m_size.width()/2-100,m_size.height()/2-100);

    m_label=new QLabel(this);
    m_label->setText("版本: 1.0.9");//version
    m_label->setFont(m_font);
    m_label->move(m_size.width()/2-100,m_size.height()/2-70);


    m_label=new QLabel(this);
    m_label->setText("日期: 2021-10-18 18:53");//data
    m_label->setFont(m_font);
    m_label->move(m_size.width()/2-100,m_size.height()/2-40);

    m_label=new QLabel(this);
    m_label->setText("公司: ZKFD"); //company
    m_label->setFont(m_font);
    m_label->move(m_size.width()/2-100,m_size.height()/2-10);

    m_label=new QLabel(this);
    m_label->setText("作者: Jiangxiaoyu"); //author
    m_label->setFont(m_font);
    m_label->move(m_size.width()/2-100,m_size.height()/2+20);


}


void CHECK_VIRTSYS_ABOUTDIALOG::check_virtsys_showAboutDialog()
{

    if(this->isHidden()){
        this->show();
     }
}
















