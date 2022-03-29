#include <QtCore/qmath.h>
#include <QHeaderView>
#include <checkVirsys/check_virtsys_manager.h>
#include <checkVirsys/check_virtsys_virtsysdomainwindow.h>

Check_Virtsys_VirtSysDomWindow::Check_Virtsys_VirtSysDomWindow(QWidget *parent):
    QTableWidget(parent),
   virManager(CHECK_VIRTSYS_MANAGER::check_virtsys_managerObj()),
   thread((CHECK_VIRTSYS_THREAD *)virManager->check_virtsys_factoryIf(THREAD_IF))
{

//    check_virtsys_domWinInit();
}

Check_Virtsys_VirtSysDomWindow::~Check_Virtsys_VirtSysDomWindow()
{

}

void Check_Virtsys_VirtSysDomWindow::check_virtsys_domWinInit()
{


    QWidget * parentWin=this->parentWidget();
    QSize  m_size(parentWin->width(),parentWin->height());
    qDebug()<<"m_size:"<<m_size;
    QPoint m_point(parentWin->pos().x(),parentWin->pos().y());
//    this->setGeometry(m_point.x(),m_point.y(),m_size.width(),m_size.height());
//    this->setGeometry(10,0,this->width(),this->height());
//    this->resize(this->width(),this->height());
    QTableWidgetItem * m_tabItem=nullptr;
    QStringList m_tabHeaderList;
     m_tabHeaderList<<"域ID"<<"名称"<<"可用内存"<<"最大内存"<<"cpu数量"<<"cpu运行时间"<<"状态";
    // m_tabHeaderList<<"id"<<"name"<<"Mem"<<"Maxmem"<<"nrcpu"<<"cpuRunTime"<<"State";
    this->setColumnCount(m_tabHeaderList.count());

     this->setRowCount(1);
    for(int i=0;i<this->columnCount();i++){
        m_tabItem=new QTableWidgetItem(m_tabHeaderList.at(i));
        QFont font=m_tabItem->font();
        font.setPixelSize(14); // set header font size
        m_tabItem->setTextColor(Qt::blue); //set header text color
        m_tabItem->setFont(font); //set font
        this->setHorizontalHeaderItem(i,m_tabItem);
        m_tabItem=new QTableWidgetItem("---");
        m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        this->setItem(0,i,m_tabItem);
    }
        this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //this->setEnabled(false);
        this->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->setSelectionBehavior(QAbstractItemView::SelectRows);
}




void Check_Virtsys_VirtSysDomWindow::check_virtsys_updataDomInfoTabWin()
{
    QTableWidgetItem * m_tabItem=nullptr;
    quint64 row=0 , col=0 ,m_rowCount=0;


//    std::map<int ,char *> map_test;
//    for(auto &iter:map_test){
//        qDebug()<<"this is no"<<endl;
//    }
    auto map=thread->check_virtsys_getDomainInfo();
    for(auto &iter:map){

        quint64 m_rowCount=this->rowCount();
        if(row >=m_rowCount){
            if(m_rowCount==0)
                  this->setRowCount(1);
            else
                this->insertRow(m_rowCount);

            /* set domain id*/
            m_tabItem=new QTableWidgetItem(QString::number(iter.second->id,10)+"("+
                                           QString::fromStdString(iter.second->os_type)+")");
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);

            /* set domain name */
            m_tabItem=new QTableWidgetItem(QString::fromStdString(iter.second->name));
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);

            /* set domian mem*/
            m_tabItem=new QTableWidgetItem(QString::number((iter.second->memory)/1024)+"Mb");
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);


            /* set domian Maxmem */
            m_tabItem=new QTableWidgetItem(QString::number((iter.second->maxMem)/1024)+"Mb");
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);

            /* set domian nrcpu*/
            m_tabItem=new QTableWidgetItem(QString::number(iter.second->nrVirtCpu));
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);


            /* set domian cpu ran time */
            m_tabItem=new QTableWidgetItem(QString::number(((iter.second->cpuTime/(qPow(10,9)))/3600))+"h");
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);

            /* set domain status */
            switch(iter.second->state){
                case VIR_DOMAIN_RUNNING:
                    m_tabItem=new QTableWidgetItem("running");
                    m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
                    this->setItem(row,col++,m_tabItem);
                break;
                case VIR_DOMAIN_BLOCKED:
                    m_tabItem=new QTableWidgetItem("block");
                    m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
                    this->setItem(row,col++,m_tabItem);
                break;
                case VIR_DOMAIN_PAUSED:
                    m_tabItem=new QTableWidgetItem("paused");
                    m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
                    this->setItem(row,col++,m_tabItem);
                break;
                case VIR_DOMAIN_SHUTDOWN:
                    this->item(row,0)->setText("---");
                    m_tabItem=new QTableWidgetItem("shut down");
                    m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
                    this->setItem(row,col++,m_tabItem);
                break;
                case VIR_DOMAIN_SHUTOFF:
                    this->item(row,0)->setText("---");
                    m_tabItem=new QTableWidgetItem("shut off");
                    m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
                    this->setItem(row,col++,m_tabItem);
                break;
                case VIR_DOMAIN_CRASHED:
                    m_tabItem=new QTableWidgetItem("crashed");
                    m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
                    this->setItem(row,col++,m_tabItem);
                break;
                case VIR_DOMAIN_PMSUSPENDED:
                    m_tabItem=new QTableWidgetItem("suspended");
                    m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
                    this->setItem(row,col++,m_tabItem);
                break;
                default:
                    m_tabItem=new QTableWidgetItem("none");
                    m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
                    this->setItem(row,col++,m_tabItem);
                break;
            }
            row++ , col=0;
        }else{

            /* updata domain id*/
            this->item(row,col++)->setText(QString::number(iter.second->id,10)+"("+
                                                     QString::fromStdString(iter.second->os_type)+")");

            /* updata domain name */
            this->item(row,col++)->setText(QString::fromStdString(iter.second->name));

            /* updata domian mem*/
            this->item(row,col++)->setText(QString::number((iter.second->memory)/1024)+"Mb");

            /* updata domian Maxmem*/
            this->item(row,col++)->setText(QString::number((iter.second->maxMem)/1024)+"Mb");


            /* updata domian nrcpu*/
            this->item(row,col++)->setText(QString::number(iter.second->nrVirtCpu));


            /* updata domian cpu ran time */
            this->item(row,col++)->setText(QString::number(((iter.second->cpuTime/(qPow(10,9)))/3600))+"h");


            /* updata domain status */
            switch(iter.second->state){
                case VIR_DOMAIN_RUNNING:
                    this->item(row,col++)->setText("running");
                break;
                case VIR_DOMAIN_BLOCKED:
                    this->item(row,col++)->setText("block");
                break;
                case VIR_DOMAIN_PAUSED:
                    this->item(row,col++)->setText("paused");
                break;
                case VIR_DOMAIN_SHUTDOWN:
                    this->item(row,0)->setText("---");
                    this->item(row,col++)->setText("shut down");
                break;
                case VIR_DOMAIN_SHUTOFF:
                    this->item(row,0)->setText("---");
                    this->item(row,col++)->setText("shut off");
                break;
                case VIR_DOMAIN_CRASHED:
                    this->item(row,col++)->setText("crashed");
                break;
                case VIR_DOMAIN_PMSUSPENDED:
                    this->item(row,col++)->setText("suspended");
                break;
                default:
                    this->item(row,col++)->setText("none");
                break;
            }
            row++,col=0;
         }
    }
    thread->check_virtsys_free_DomainData();
    m_rowCount= this->rowCount();
    for(; row < m_rowCount ; row++)
         this->removeRow(row);

}












