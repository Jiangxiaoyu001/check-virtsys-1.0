
#include <QtCore/qmath.h>
#include <QHeaderView>
#include "check_virtsys_manager.h"
#include "check_virtsts_genernalwindow.h"

CHECK_VIRTSTS_GENERNALWINDOW::CHECK_VIRTSTS_GENERNALWINDOW(QWidget *parent):
    m_genernalWin(new QTableWidget(parent)),
    virManager(CHECK_VIRTSYS_MANAGER::check_virtsys_managerObj())
{

}

CHECK_VIRTSTS_GENERNALWINDOW::~CHECK_VIRTSTS_GENERNALWINDOW()
{

}

void CHECK_VIRTSTS_GENERNALWINDOW::chech_virtsys_updataGenernalWin()
{

}

void CHECK_VIRTSTS_GENERNALWINDOW::check_virtsys_genernalWinInit()
{

    QWidget * parentWin=m_genernalWin->parentWidget();
    QSize  m_size(parentWin->width(),parentWin->height());
    QPoint m_point(parentWin->pos().x(),parentWin->pos().y());
    m_genernalWin->setGeometry(m_point.x(),m_point.y(),m_size.width(),m_size.height());

    QTableWidgetItem * m_tabItem=nullptr;
    QStringList m_tabHeaderList;
     m_tabHeaderList<<"name"<<"totoCount"<<"runningCount"<<"shutCount"<<"totoMem";
    m_genernalWin->setColumnCount(m_tabHeaderList.count());

     m_genernalWin->setRowCount(1);
    for(int i=0;i<m_genernalWin->columnCount();i++){
        m_tabItem=new QTableWidgetItem(m_tabHeaderList.at(i));
        QFont font=m_tabItem->font();
        font.setPixelSize(14); // set header font size
        m_tabItem->setTextColor(Qt::blue); //set header text color
        m_tabItem->setFont(font); //set font
        m_genernalWin->setHorizontalHeaderItem(i,m_tabItem);
        m_tabItem=new QTableWidgetItem("---");
        m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        m_genernalWin->setItem(0,i,m_tabItem);
    }
        m_genernalWin->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //    m_domTabWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //m_domTabWidget->setEnabled(false);
        m_genernalWin->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_genernalWin->setSelectionBehavior(QAbstractItemView::SelectRows);

}












