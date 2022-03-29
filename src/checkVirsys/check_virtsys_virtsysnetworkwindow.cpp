#include <QHeaderView>
#include <QPushButton>
#include <checkVirsys/check_virtsys_virtsysnetworkwindow.h>

Check_Virtsys_virtSysNetWorkWindow::Check_Virtsys_virtSysNetWorkWindow(QWidget * parent):
    QTableWidget(parent),
    virManager(CHECK_VIRTSYS_MANAGER::check_virtsys_managerObj()),
    thread((CHECK_VIRTSYS_THREAD *) virManager->check_virtsys_factoryIf(THREAD_IF))
{
//    check_virtsys_netWorkWidInit();
}

Check_Virtsys_virtSysNetWorkWindow::~Check_Virtsys_virtSysNetWorkWindow()
{

}


/*  widget style with virNetWorkInfo-table    */

void Check_Virtsys_virtSysNetWorkWindow::check_virtsys_netWorkWidInit()
{
    QWidget * parentWin=this->parentWidget();
    QSize  m_size(parentWin->width(),parentWin->height());
    QPoint m_point(parentWin->pos().x(),parentWin->pos().y());
    this->setGeometry(m_point.x(),m_point.y(),m_size.width(),m_size.height());

    this->resize(this->width(),this->height());

//    this->setGeometry(m_point.x(),m_point.y(),
//                                m_size.width(),m_size.height());
    QTableWidgetItem * m_tabItem=nullptr;
    QStringList m_tabHeaderList;
//     m_tabHeaderList <<"id"<<"virnetName"<<"rx_bytes"<<"rx_packets"<<"rx_errs"
//                   <<"rx_drop"<<"tx_bytes"<<"tx_packets"<<"tx_errs"<<"tx_drop";

     m_tabHeaderList <<"域ID"<<"虚拟网卡"<<"接收字节"<<"接收包"<<"接收错误"
                   <<"接收丢失"<<"发送字节"<<"发送包"<<"发送错误"<<"发送丢失";
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


    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void Check_Virtsys_virtSysNetWorkWindow::check_virtsys_updataNetworkTabWid()
{
    quint64 row=0, col=0 , m_rowCount=0, currRowCount=0;

    QTableWidgetItem * m_tabItem=nullptr;

    for(auto &iter:thread->check_virtsys_getNetWorkInfo()){
        currRowCount++;
        m_rowCount=this->rowCount();
        if(row >=m_rowCount){
            if(m_rowCount==0)
                 this->setRowCount(1);
            else
                this->insertRow(m_rowCount);
            /* set item and fill with  vir-domain  id*/
           // qDebug()<<"row_num:"<<this->rowCount();
            m_tabItem=new QTableWidgetItem(QString::number(iter.second->id,10));
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);

            /* set item and fill with  vir-NetWork name */

            m_tabItem=new QTableWidgetItem(QString::fromStdString(iter.second->virNetName.front()));
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);

            //std::cout<<"virName:"<<iter.second->virNetName.front()<<std::endl;
            iter.second->virNetName.pop_front();
            /* set item and fill with  virNetWork rx_bytes*/

            m_tabItem=new QTableWidgetItem(QString::number(iter.second->rx_bytes),10);
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);

            /* set item and fill with  virNetWork rx_packets */

            m_tabItem=new QTableWidgetItem(QString::number(iter.second->rx_packets));
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);

            /* set item and fill with  virNetWork rx_errs */

            m_tabItem=new QTableWidgetItem(QString::number(iter.second->rx_errs));
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);

            /* set item and fill with  virNetWork rx_drop */


            m_tabItem=new QTableWidgetItem(QString::number(iter.second->rx_drop));
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);


            /* set item and fill with  virNetWork tx_bytes*/

            m_tabItem=new QTableWidgetItem(QString::number(iter.second->tx_bytes));
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);

            /* set item and fill with  virNetWork tx_packets */

            m_tabItem=new QTableWidgetItem(QString::number(iter.second->tx_packets));
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);

            /* set item and fill with  virNetWork tx_errs */

            m_tabItem=new QTableWidgetItem(QString::number(iter.second->tx_errs));
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row,col++,m_tabItem);

            /* set item and fill with  virNetWork tx_drop */

            m_tabItem=new QTableWidgetItem(QString::number(iter.second->tx_drop));
            m_tabItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            this->setItem(row++,col++,m_tabItem);

            col=0;
        }else{
            /* updata item and fill with  vir-domain  id*/
          this->item(row,col++)->setText(QString::number(iter.second->id,10));

          /* updata item and fill with  vir-NetWork name */
          this->item(row,col++)->setText(QString::fromStdString(iter.second->virNetName.front()));

         //std::cout<<"virName:"<<iter.second->virNetName.front()<<std::endl;
          iter.second->virNetName.pop_front();


          /* updata item and fill with  virNetWork rx_bytes*/
           this->item(row,col++)->setText(QString::number(iter.second->rx_bytes,10));

          /* updata item and fill with  virNetWork rx_packets */
         this->item(row,col++)->setText(QString::number(iter.second->rx_packets));


          /* updata item and fill with  virNetWork rx_errs */
          this->item(row,col++)->setText(QString::number(iter.second->rx_errs));



          /* updata item and fill with  virNetWork rx_drop */

          this->item(row,col++)->setText(QString::number(iter.second->rx_drop));


          /* updata item and fill with  virNetWork tx_bytes*/

          this->item(row,col++)->setText(QString::number(iter.second->tx_bytes));

          /* updata item and fill with  virNetWork tx_packets */

          this->item(row,col++)->setText(QString::number(iter.second->tx_packets));


          /* updata item and fill with  virNetWork tx_errs */
          this->item(row,col++)->setText(QString::number(iter.second->tx_errs));

          /* updata item and fill with  virNetWork tx_drop */
          this->item(row,col++)->setText(QString::number(iter.second->tx_drop));

         row++; col=0;
        }
    }
    thread->check_virtsys_free_NetWorkData();
    m_rowCount= this->rowCount();
    for(; row < m_rowCount ; row++)
        this->removeRow(row);
}















