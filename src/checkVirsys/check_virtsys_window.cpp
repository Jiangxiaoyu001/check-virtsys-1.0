#include <QtCore/qmath.h>
#include <checkVirsys/check_virtsys_window.h>
#include <checkVirsys/check_virtsys_aboutdialog.h>
#include <checkVirsys/check_virtsts_genernal.h>
#include <checkVirsys/check_virtsys_virtsysnetworkwindow.h>
#include <checkVirsys/check_virtsys_virtsysdomainwindow.h>
#include <checkVirsys/check_virtsys_detailedwindow.h>

using namespace QtCharts;

Check_Virtsys_Window::Check_Virtsys_Window(QWidget *parent):
    QWidget(parent), //Qt::Horizontal,
    m_timerStatus(false),
    m_listWidget(new QListWidget(this)),
    m_staWidget( new QStackedWidget(this)),
    virManager(CHECK_VIRTSYS_MANAGER::check_virtsys_managerObj()),
    genWidget(new CHECK_VIRTSTS_GENERNAL(this)),
    aboutDialog (new CHECK_VIRTSYS_ABOUTDIALOG(this)),
    detailWidget (new CHECK_VIRTSYS_DETAILEDWINDOW(this)),
    domWidget(new Check_Virtsys_VirtSysDomWindow(this)),
    netWorkWidget(new Check_Virtsys_virtSysNetWorkWindow(this))

{

    //removeWindlwList();
    Check_Virtsys_WindowInit();
    Check_Virtsys_AddListWinItem();
//    Check_Virtsys_loadStyleSheet();
    connect(&timer,&QTimer::timeout,this,&Check_Virtsys_Window::Check_Virtsys_updataWidget);
    //Check_Virtsys_startTimer();
    addWindowList();
//    setBackground();
}

Check_Virtsys_Window::~Check_Virtsys_Window()
{

}

/* operation overload << */
std::list<QWidget *>&
operator<<( std::list<QWidget *>&windowList, QWidget * wid)
{
    windowList.push_back(wid);
    return windowList;
}



void Check_Virtsys_Window::addWindowList()
{
    windowList<<genWidget
              <<aboutDialog
              <<detailWidget
              <<domWidget
              <<netWorkWidget
              <<this;
}

void Check_Virtsys_Window::setBackground()
{
    for(auto &iter:windowList){
        iter->setAutoFillBackground(true);
        QPalette p = iter->palette();
        p.setColor(QPalette::Window,QColor(100,100,105));
        iter->setPalette(p);
    }
}

void Check_Virtsys_Window::removeWindlwList()
{

    for(auto &iter:windowList){
        windowList.pop_back();
        iter++;
    }
}

void Check_Virtsys_Window::Check_Virtsys_CreateLayout()
{
    QGridLayout *layout = new QGridLayout(this);
//    QHBoxLayout *Hlayout= new QHBoxLayout();

//    layout->setHorizontalSpacing(100);
//    layout->setVerticalSpacing(64);
//    layout->setColumnMinimumWidth(0,100);
//    Hlayout->addStretch();
//    Hlayout->addWidget(m_listWidget);
//    Hlayout->addSpacing(10);
//    Hlayout->addWidget(m_staWidget);
//    Hlayout->addSpacing(5);
//    layout->addLayout(Hlayout,0,0);
    layout->addWidget(m_listWidget,0,0); /* layout:1/8 */
    layout->setHorizontalSpacing(1);
    layout->addWidget(m_staWidget,0,1); /* layout: 7/8 */
//    layout->setRowMinimumHeight(0,10);
//    layout->setColumnMinimumWidth(0,200);
//    layout->setColumnMinimumWidth(1,600);
    layout->setRowStretch(0, 1);//设置行列比例系数
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 7);
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);
}
void Check_Virtsys_Window::Check_Virtsys_startTimer()
{
    if(!m_timerStatus){
        m_timerStatus=true;
        timer.start(500);// 500ms
    }
}

void Check_Virtsys_Window::Check_Virtsys_stopTimer()
{
    if(m_timerStatus){
        m_timerStatus=false;
        timer.stop();
    }
}





void Check_Virtsys_Window::Check_Virtsys_WindowInit()
{

    QPalette m_pale(m_listWidget->palette());
    m_pale.setColor(QPalette::Base,QColor(118,238,238));
    m_listWidget->setAutoFillBackground(true);
    m_listWidget->setPalette(m_pale);

    genWidget->check_virt_genernalWidInit();
    domWidget->check_virtsys_domWinInit();
    netWorkWidget->check_virtsys_netWorkWidInit();
    aboutDialog->check_virtsys_aboutDialogInit();
    detailWidget->check_virtsys_detailWinInit();
//    nrcpuUsageChartView->setChart(nrcpuUsageChart);
//    netUsageChartView->setChart(netWorkUsageChart);

    m_staWidget->addWidget(genWidget);
    m_staWidget->addWidget(domWidget);
    m_staWidget->addWidget(netWorkWidget);
    m_staWidget->addWidget(aboutDialog);
    m_staWidget->addWidget(detailWidget);
    m_staWidget->setCurrentWidget(genWidget);
    connect(m_listWidget,&QListWidget::currentItemChanged,this,
            &Check_Virtsys_Window::check_virtsys_SwitchPages);

    Check_Virtsys_CreateLayout();
}


void Check_Virtsys_Window::Check_Virtsys_changedListItem(){

}

void Check_Virtsys_Window::Check_Virtsys_InsertListWinItem(int row)
{
    QListWidgetItem * m_listWinItem=nullptr;
    m_listWinItem=new QListWidgetItem(m_listWidget,QListWidgetItem::Type);
    m_listWidget->insertItem(row,m_listWinItem);

}

void Check_Virtsys_Window::Check_Virtsys_AddListWinItem()
{

    m_listWinItem=new QListWidgetItem(m_listWidget,QListWidgetItem::Type);
    m_listWinItem->setText(tr("虚拟化概述")); //virGenertol
    m_listWinItem->setSizeHint(QSize(45,50));
    m_listWinItem->setSelected(true);


    m_listWinItem=new QListWidgetItem(m_listWidget,QListWidgetItem::Type);
    m_listWinItem->setText(tr("虚拟域信息")); //virDomainInfo
    m_listWinItem->setSizeHint(QSize(45,50));
//    m_listWinItem->setSelected(true);
//    m_listWinItem->setCheckState(Qt::PartiallyChecked);
//    m_listWinItem->setFlags(Qt::ItemIsSelectable);



    m_listWinItem=new QListWidgetItem(m_listWidget,QListWidgetItem::Type);
    m_listWinItem->setText(tr("虚拟网络信息")); //virNetWorkInfo
    m_listWinItem->setSizeHint(QSize(45,50));
    
    m_listWinItem=new QListWidgetItem(m_listWidget,QListWidgetItem::Type);
    m_listWinItem->setText(tr("详细信息")); //detailedInfo
    m_listWinItem->setSizeHint(QSize(45,50));

    m_listWinItem=new QListWidgetItem(m_listWidget,QListWidgetItem::Type);
    m_listWinItem->setText(tr("关于")); //about
    m_listWinItem->setSizeHint(QSize(45,50));

//    m_listWinItem=new QListWidgetItem(m_listWidget,QListWidgetItem::Type);
//    m_listWinItem->setText(tr("虚拟CPU使用率"));
//    m_listWinItem->setSizeHint(QSize(45,50));

//    m_listWinItem=new QListWidgetItem(m_listWidget,QListWidgetItem::Type);
//    m_listWinItem->setText(tr("虚拟网络收发"));
//    m_listWinItem->setSizeHint(QSize(45,50));

//    m_listWinItem=new QListWidgetItem(m_listWidget,QListWidgetItem::Type);
//    m_listWinItem->setText(tr("虚拟机总数量"));
//    m_listWinItem->setSizeHint(QSize(40,50));

}



void Check_Virtsys_Window::Check_Virtsys_RemoveListWinItem()
{

}

void Check_Virtsys_Window::Check_Virtsys_loadStyleSheet()
{
    QFile m_file("/usr/share/qss/QListWidget.qss");
    m_file.open(QFile::ReadOnly);
    QString m_styleSheet=QLatin1String(m_file.readAll());
    m_listWidget->setStyleSheet(m_styleSheet);
}



void Check_Virtsys_Window::Check_Virtsys_updataChart_cpuUsage()
{

}

void Check_Virtsys_Window::Check_Virtsys_updataChart_netWorkUsage()
{

}



//void Check_Virtsys_Window::Check_Virtsys_tabWidgetUpdate_NetWorkInfo_test()
//{
//    quint64 row =0 ,col=0;
//    QTableWidgetItem * m_tabItem=nullptr;

//    int row_num=m_netWorkTabWidget->rowCount();
//    int clo_num=m_netWorkTabWidget->columnCount();
//    for(int i=0;i<row_num;i++){
//        for(int j=0;j<clo_num;j++){
//            m_tabItem= m_netWorkTabWidget->item(i,j);
//            delete m_tabItem;
//            m_tabItem=nullptr;
//        }
//    }
//    m_netWorkTabWidget->setRowCount(1);
////    m_netWorkTabWidget->clearContents();
//    for(auto &iter:virManager->threadManager->check_virtsys_getNetWorkInfo()){

//        quint64 m_rowCount=m_domTabWidget->rowCount();
//        if(row >=m_rowCount){
//            m_netWorkTabWidget->insertRow(m_rowCount);

//        }
//        /* set item and fill with  vir-domain  id*/

//        m_tabItem=new QTableWidgetItem(QString::number(iter.second->id,10));
//        m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//        m_netWorkTabWidget->setItem(row,col++,m_tabItem);


//        /* set item and fill with  vir-NetWork name */

//      m_tabItem=new QTableWidgetItem(QString::fromStdString(iter.second->virNetName.front()));
//      m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//      m_netWorkTabWidget->setItem(row,col++,m_tabItem);

//       std::cout<<"virName:"<<iter.second->virNetName.front()<<std::endl;
//        iter.second->virNetName.pop_front();


//        /* set item and fill with  virNetWork rx_bytes*/

//        m_tabItem=new QTableWidgetItem(QString::number(iter.second->rx_bytes),10);
//        m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//        m_netWorkTabWidget->setItem(row,col++,m_tabItem);

//        /* set item and fill with  virNetWork rx_packets */

//        m_tabItem=new QTableWidgetItem(QString::number(iter.second->rx_packets));
//        m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//        m_netWorkTabWidget->setItem(row,col++,m_tabItem);

//        /* set item and fill with  virNetWork rx_errs */

//        m_tabItem=new QTableWidgetItem(QString::number(iter.second->rx_errs));
//        m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//        m_netWorkTabWidget->setItem(row,col++,m_tabItem);

//        /* set item and fill with  virNetWork rx_drop */


//        m_tabItem=new QTableWidgetItem(QString::number(iter.second->rx_drop));
//        m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//        m_netWorkTabWidget->setItem(row,col++,m_tabItem);


//        /* set item and fill with  virNetWork tx_bytes*/

//        m_tabItem=new QTableWidgetItem(QString::number(iter.second->tx_bytes));
//        m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//        m_netWorkTabWidget->setItem(row,col++,m_tabItem);

//        /* set item and fill with  virNetWork tx_packets */

//        m_tabItem=new QTableWidgetItem(QString::number(iter.second->tx_packets));
//        m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//        m_netWorkTabWidget->setItem(row,col++,m_tabItem);

//        /* set item and fill with  virNetWork tx_errs */

//        m_tabItem=new QTableWidgetItem(QString::number(iter.second->tx_errs));
//        m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//        m_netWorkTabWidget->setItem(row,col++,m_tabItem);

//        /* set item and fill with  virNetWork tx_drop */

//        m_tabItem=new QTableWidgetItem(QString::number(iter.second->tx_drop));
//        m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
//        m_netWorkTabWidget->setItem(row,col++,m_tabItem);

////        m_netWorkTabWidget->insertRow(++row);
//       row++; col=0;
//    }
//    virManager->threadManager-> check_virtsys_free_NetWorkData();
//}



void Check_Virtsys_Window::Check_Virtsys_tabWidDomain_updataItem()
{
    domWidget->check_virtsys_updataDomInfoTabWin();
}




void Check_Virtsys_Window::Check_Virtsys_tabWidNetWork_updataItem()
{
    netWorkWidget->check_virtsys_updataNetworkTabWid();

}



/*  using timer to updata widget  */
void Check_Virtsys_Window::Check_Virtsys_updataWidget()
{
    QWidget * curr_wid=m_staWidget->currentWidget();
    if(curr_wid==domWidget){
          Check_Virtsys_tabWidDomain_updataItem();
    }else if(curr_wid==netWorkWidget){
        Check_Virtsys_tabWidNetWork_updataItem();
    }else if(curr_wid==genWidget){
        if(check_virtsys_vailedTime())
            genWidget->check_virt_genernalWidUpdate();
    }
}

/* judge time whether to vailed gived by five*/
bool Check_Virtsys_Window::check_virtsys_vailedTime()
{
    if(mesc){
        size_t curtime=m_time.msecsSinceStartOfDay();
        bool res=(curtime-mesc >= 5*60*1000 ? true:false);
        if(res)
            mesc=curtime;
        return res;
    }else{
        mesc=m_time.msecsSinceStartOfDay();
        return false;
    }
}





void Check_Virtsys_Window::check_virtsys_SwitchPages()
{
    QListWidget * m_list =qobject_cast<QListWidget *>(sender());
    int curr_row=m_list->currentRow();
    switch(curr_row){
    case 0:
        m_staWidget->setCurrentWidget(genWidget);
   break;
   case 1:
        virManager->check_virtsys_dataManagerCenter(VIRDOMAIN);
        m_staWidget->setCurrentWidget(domWidget);
    break;
    case 2:
        virManager->check_virtsys_dataManagerCenter(VIRNETWORK);
        m_staWidget->setCurrentWidget(netWorkWidget);
    	break;
    case 3:
         virManager->check_virtsys_dataManagerCenter(VIRDOMAIN);
         m_staWidget->setCurrentWidget(detailWidget);
    break;
    case 4:
        aboutDialog->check_virtsys_showAboutDialog();
        m_staWidget->setCurrentWidget(aboutDialog);
    break;
    }
}

















