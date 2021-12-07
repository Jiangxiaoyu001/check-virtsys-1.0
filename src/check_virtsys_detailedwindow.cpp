#include <QString>
#include <QByteArray>
#include <qmath.h>
#include "check_virtsys_manager.h"
#include "check_virtsys_detailedwindow.h"
#include "test.h"
#include <QMenu>
#include <QTextBlock>
#include <dlfcn.h>
#include <QScrollBar>

CHECK_VIRTSYS_DETAILEDWINDOW::_treeWid_ * CHECK_VIRTSYS_DETAILEDWINDOW::m_treeWid=nullptr;

CHECK_VIRTSYS_DETAILEDWINDOW::_listStyle_* CHECK_VIRTSYS_DETAILEDWINDOW::m_ls=nullptr;

CHECK_VIRTSYS_DETAILEDWINDOW::CHECK_VIRTSYS_DETAILEDWINDOW(QWidget *parent):
    QWidget(parent),
    m_vBoxLay(new QHBoxLayout(this)),
    plEdit(new QPlainTextEdit(this)),
    m_lswid(new _listWid_(this))
{
//    check_virtsys_detailWinInit();


}

CHECK_VIRTSYS_DETAILEDWINDOW::~CHECK_VIRTSYS_DETAILEDWINDOW()
{

}

void CHECK_VIRTSYS_DETAILEDWINDOW::check_virtsys_detailWinInit()
{
    QWidget * parentWin=this->parentWidget();
    QSize  m_size(parentWin->width(),parentWin->height());
    QPoint m_point(parentWin->pos().x(),parentWin->pos().y());
    m_vBoxLay->setMargin(50);
    m_vBoxLay->setContentsMargins(0,0,m_size.width()-200,0);

    this->setGeometry(QRect(m_point.x(),m_point.y(),m_size.width(),m_size.height()));
    m_vBoxLay->addWidget(m_lswid);
    this->setLayout(m_vBoxLay);

    m_lswid->check_virtsys_detailWinInit();
    m_treeWid=new _treeWid_(this);

    plEdit->setReadOnly(true);
    QScrollBar * pSroBar=new QScrollBar(this);
    pSroBar->setMinimumWidth(100);


    plEdit->setVerticalScrollBar(pSroBar);

     plEdit->setGeometry(m_treeWid->x()+m_treeWid->width(),m_treeWid->y(),
                         (this->width()-(m_lswid->width()+m_treeWid->width())-190),this->height());

//     connect(plEdit,&QPlainTextEdit::customContextMenuRequested,[this]{
//         qDebug()<<"clicked---right"<<endl;
////         QMenu *m_menu=plEdit->createStandardContextMenu();
////         m_menu->exec();
//     });

}


void CHECK_VIRTSYS_DETAILEDWINDOW::_listWid_::check_virtsys_detailWinInit()
{
    QWidget * parentWin=this->parentWidget();
    QSize  m_size(parentWin->width(),parentWin->height());
    QPoint m_point(parentWin->pos().x(),parentWin->pos().y());

    this->setGeometry(QRect(m_point.x(),m_point.y(),10,m_size.height()));


    m_listWinItem=new QListWidgetItem(this,QListWidgetItem::Type);
    m_listWinItem->setText(tr("os_type"));
    m_listWinItem->setSizeHint(QSize(45,35));

    m_listWinItem=new QListWidgetItem(this,QListWidgetItem::Type);
    m_listWinItem->setText(tr("vir_type"));
    m_listWinItem->setSizeHint(QSize(45,35));

    m_listWinItem=new QListWidgetItem(this,QListWidgetItem::Type);
    m_listWinItem->setText(tr("id_domain"));
    m_listWinItem->setSizeHint(QSize(45,35));

    m_listWinItem=new QListWidgetItem(this,QListWidgetItem::Type);
    m_listWinItem->setText(tr("name"));
    m_listWinItem->setSizeHint(QSize(45,35));

    m_listWinItem=new QListWidgetItem(this,QListWidgetItem::Type);
    m_listWinItem->setText(tr("mem"));
    m_listWinItem->setSizeHint(QSize(45,35));

    m_listWinItem=new QListWidgetItem(this,QListWidgetItem::Type);
    m_listWinItem->setText(tr("maxmem"));
    m_listWinItem->setSizeHint(QSize(45,35));

    m_listWinItem=new QListWidgetItem(this,QListWidgetItem::Type);
    m_listWinItem->setText(tr("nrcpu"));
    m_listWinItem->setSizeHint(QSize(45,35));

    m_listWinItem=new QListWidgetItem(this,QListWidgetItem::Type);
    m_listWinItem->setText(tr("cpuRuntime"));
    m_listWinItem->setSizeHint(QSize(45,35));


    m_listWinItem=new QListWidgetItem(this,QListWidgetItem::Type);
    m_listWinItem->setText(tr("state"));
    m_listWinItem->setSizeHint(QSize(45,35));

    this->setMouseTracking(true);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

//    connect(this,&QListWidget::customContextMenuRequested,[](){
//        std::cout<<"---- tets------"<<std::endl;
//    });
//      this->setAttribute(Qt::WA_TransparentForMouseEvents,true);
}


void CHECK_VIRTSYS_DETAILEDWINDOW::_listWid_::check_virtsys_updataDetailWid(int row)
{
//    auto ps=virManager->threadManager;

    CHECK_VIRTSYS_THREAD * thread=(CHECK_VIRTSYS_THREAD *) m_ls->virManager->check_virtsys_factoryIf(THREAD_IF);
    auto mulitmap=thread->check_virtsys_getDomainInfo();
    auto iter=mulitmap.find(m_ls->listWid->item(row)->text().toInt());
    QString text=m_ls->listWid->item(row)->text();
    if(text.toInt()==0&&text.size()>0){
        /* find key */
        auto key=std::find_if(mulitmap.begin(),mulitmap.end(),
                      [&text](std::multimap<unsigned int ,Check_Virtsys_Libvirt_API::
                      _checkVirSysVirDomainInfo_ * >::value_type item){
                        text.remove(QRegExp("\\s")); // remove space
                        text.remove("shutoff") ,text.remove("shutdown");;
                        return text.compare(item.second->name.c_str())==0;
                     });
        if(key!=mulitmap.end()){
            auto &iterP=iter;
            iterP=key;
            goto updata;
        }
    }
    if((iter!=mulitmap.end())){
    updata:{

            /* set xml for tree parse*/
            m_treeWid->check_virtsys_setXml(iter->second->xml.c_str());

            /* updata os type*/
             this->item(0)->setText("os_type:   "+(QString(iter->second->os_type.c_str())));
            /* updata vir type*/
             this->item(1)->setText("vir_type:  "+(QString(iter->second->vir_type.c_str())));

            /* updata domain id*/
            this->item(2)->setText("id_domain:  "+QString::number(iter->second->id,10));
            /* updata domain name */
            this->item(3)->setText("name:   "+QString::fromStdString(iter->second->name));
            /* updata domian mem*/
            this->item(4)->setText("mem:    "+QString::number((iter->second->memory)/1024)+"Mb");
            /* updata domian Maxmem*/
            this->item(5)->setText("maxmem:     "+QString::number((iter->second->maxMem)/1024)+"Mb");
            /* updata domian nrcpu*/
            this->item(6)->setText("nrcpu:      "+QString::number(iter->second->nrVirtCpu));
            /* updata domian cpu ran time */
            this->item(7)->setText("cpuRuntime:     "+QString::number(((iter->second->cpuTime/(qPow(10,9)))/3600))+"h");
            /* updata domain status */
            switch(iter->second->state){
                case VIR_DOMAIN_RUNNING:
                    this->item(8)->setText("vir_state:      running");
                break;
                case VIR_DOMAIN_BLOCKED:
                    this->item(8)->setText("vir_state:      block");
                break;
                case VIR_DOMAIN_PAUSED:
                    this->item(8)->setText("vir_state:      paused");
                break;
                case VIR_DOMAIN_SHUTDOWN:
                    this->item(2)->setText("id_domain:      ---");
                    this->item(8)->setText("vir_state:      shut down");
                break;
                case VIR_DOMAIN_SHUTOFF:
                    this->item(2)->setText("id_domain:      ---");
                    this->item(8)->setText("vir_state:      shut off");
                break;
                case VIR_DOMAIN_CRASHED:
                    this->item(8)->setText("vir_state:      crashed");
                break;
                case VIR_DOMAIN_PMSUSPENDED:
                    this->item(8)->setText("vir_state:      suspended");
                break;
                default:
                    this->item(8)->setText("vir_state:      none");
                break;
            }
        }
    }
}

void CHECK_VIRTSYS_DETAILEDWINDOW::_listWid_::_check_virtsys_updataDetailWid_(int row)
{
    check_virtsys_updataDetailWid(row);
}




void CHECK_VIRTSYS_DETAILEDWINDOW::_listWid_::mouseMoveEvent(QMouseEvent *event)
{
    _listStyle_ * &m_ls=CHECK_VIRTSYS_DETAILEDWINDOW::m_ls;
    QPoint mousePoint(event->pos());
    if(mousePoint.x()>=this->x()+50 &&
            mousePoint.x() <=this->width()-10 &&
            mousePoint.y()<=this->item(0)->sizeHint().height()){
        if(m_ls==nullptr){
            /* new _listStyle_ class */
            m_ls=new _listStyle_(nullptr);
            /* place  point */
             mousePoint=mapToGlobal(QPoint(this->width()-50,0));
            /* Translates to global point*/
//            mousePoint=mapToGlobal(QPoint(mousePoint.x(),mousePoint.y()));
            m_ls->check_virtsys_setMousePoint(mousePoint);
            m_ls->check_virtsys_listWidCreate(this);
            /* we will delete m_ls,when listWid point to NULL */
            if(m_ls->listWid==nullptr){
                 delete m_ls;
                m_ls=nullptr;
            }
            event->ignore();
            return;
        }
    }else{
          if(m_ls){
            m_ls->check_virtsys_listWidDestroy();
            delete m_ls;
            m_ls=nullptr;
          }
          event->ignore();
          return;
    }
    /*parent-widget continue deal*/
    return QListWidget::mouseMoveEvent(event);
}

void CHECK_VIRTSYS_DETAILEDWINDOW::_listWid_::mousePressEvent(QMouseEvent *event)
{
     qDebug()<<"-----mousePressEvent-----"<<endl;
//     event->accept();
    return QListWidget::mousePressEvent(event);
}

void CHECK_VIRTSYS_DETAILEDWINDOW::_listWid_::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"-----mouseReleaseEvent-----"<<endl;
//     event->accept();
    return QListWidget::mouseReleaseEvent(event);
}

void CHECK_VIRTSYS_DETAILEDWINDOW::_listWid_::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug()<<"-----mouseDoubleClickEvent-----"<<endl;
    return QListWidget::mouseDoubleClickEvent(event);
}




/********************************************
 *
 * Describe: Sub class , using VBox set two widget
 *
 *
 *
 *
 * ****************************************************/



CHECK_VIRTSYS_DETAILEDWINDOW::_listWid_::_listWid_(QWidget *parent):
    QListWidget(parent)
{

}

CHECK_VIRTSYS_DETAILEDWINDOW::_listWid_::~_listWid_()
{

}







/*****************************************
*
* Describe: Sub class , set Qlist-style of custom
* in order to give a classical effactive
*
*******************************************/

CHECK_VIRTSYS_DETAILEDWINDOW::_listStyle_::
_listStyle_(QWidget *parent):
    listWid(new QListWidget(parent)),
    virManager(CHECK_VIRTSYS_MANAGER::check_virtsys_managerObj())
{

}

CHECK_VIRTSYS_DETAILEDWINDOW::_listStyle_::~_listStyle_()
{
//    delete this;
}




void CHECK_VIRTSYS_DETAILEDWINDOW::_listStyle_::check_virtsys_loadQss()
{
    QFile m_file("/usr/share/qss/listwid.qss");
    m_file.open(QFile::ReadOnly);
    QString m_styleSheet=QLatin1String(m_file.readAll());
    listWid->setStyleSheet(m_styleSheet);

}



void CHECK_VIRTSYS_DETAILEDWINDOW::_listStyle_::
check_virtsys_setMousePoint(QPoint &m_mousePoint)
{
    this->m_mousePoint=m_mousePoint;
}


QPoint CHECK_VIRTSYS_DETAILEDWINDOW::_listStyle_::check_virtsys_mousePonit()
{
    return m_mousePoint;
}


QSize CHECK_VIRTSYS_DETAILEDWINDOW::_listStyle_::check_virtsys_listWidSize()
{
    QSize m_size(200,listWid->count()*listWid->item(0)->sizeHint().height());
    return m_size;

//    QSize m_size(200,listWid->count()*listWid->item(0)->sizeHint().height());
//    return m_size;
}


void CHECK_VIRTSYS_DETAILEDWINDOW::_listStyle_::
check_virtsys_listWidCreate(_listWid_ * obj)
{
    bool isValue=false;
//    QFont font=this->font();
//    font.setPixelSize(14); // set header font size
     CHECK_VIRTSYS_THREAD * thread=(CHECK_VIRTSYS_THREAD *) m_ls->virManager->check_virtsys_factoryIf(THREAD_IF);
    for(auto &iter:thread->check_virtsys_getDomainInfo()){
        isValue=true;
        m_lisItem=new QListWidgetItem(listWid,QListWidgetItem::Type);
        switch (iter.second->state) {
        case VIR_DOMAIN_SHUTDOWN:
            m_lisItem->setText(tr(iter.second->name.c_str())+"  shut down");
            m_lisItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            m_lisItem->setSizeHint(QSize(50,45));
            m_lisItem->setTextColor(Qt::blue);
            break;
        case VIR_DOMAIN_SHUTOFF:
            m_lisItem->setText(tr(iter.second->name.c_str())+"  shut off");
            m_lisItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            m_lisItem->setSizeHint(QSize(50,45));
            m_lisItem->setTextColor(Qt::blue);
            break;
        default:
            m_lisItem->setText(tr(QByteArray(QString::number(iter.second->id).toLatin1())));
            m_lisItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            m_lisItem->setSizeHint(QSize(50,45));
            m_lisItem->setTextColor(Qt::blue);
        }
//        m_listWinItem->setFont(font); //set font
    }
    if(isValue){
        goto style;
    }else{
        delete listWid;
        listWid=nullptr;
        return;
    }
style:{
        listWid->setGeometry(QRect(check_virtsys_mousePonit(),check_virtsys_listWidSize()));
        listWid->setWindowFlags(Qt::FramelessWindowHint);

        connect(listWid,&QListWidget::currentRowChanged,[obj](int row){
            obj->_check_virtsys_updataDetailWid_(row);
            m_treeWid->check_virtsys_updataTreeView();
            CHECK_VIRTSYS_DETAILEDWINDOW * detailWid=
                    reinterpret_cast<CHECK_VIRTSYS_DETAILEDWINDOW *>(m_treeWid->parentWidget());
            detailWid->plEdit->clear();
            detailWid->plEdit->insertPlainText(m_treeWid->check_virtsys_getXml());
            int count=detailWid->plEdit->blockCount();
            QTextBlock block=detailWid->plEdit->document()->findBlockByNumber(1);
            /*set cursor*/
            detailWid->plEdit->setFocus();
            detailWid->plEdit->setTextCursor(QTextCursor(block));
            QTextCharFormat fmt;
            fmt.setForeground(Qt::yellow);
            detailWid->plEdit->mergeCurrentCharFormat(fmt);
        });

//        connect(listWid,&QListWidget::currentRowChanged,obj,
//                &_listWid_::_check_virtsys_updataDetailWid_);

        listWid->setWindowOpacity(0.5);
        check_virtsys_loadQss();
        listWid->show();
       thread->check_virtsys_free_DomainData();
    }
}

void CHECK_VIRTSYS_DETAILEDWINDOW::_listStyle_::check_virtsys_listWidDestroy()
{
    listWid->disconnect();
    listWid->clear();
    delete listWid;
    listWid=nullptr;
}













/*************************************************
 *
 * Describe: sub class to show virsys-info of XML
 *
 *
 *
 * **********************************************/


CHECK_VIRTSYS_DETAILEDWINDOW::_treeWid_::_treeWid_(QWidget *parent):
    QTreeView(parent),
    model(new QStandardItemModel(this))
{
    check_virtsys_treeViewInit();
}

CHECK_VIRTSYS_DETAILEDWINDOW::_treeWid_::~_treeWid_()
{

}

void CHECK_VIRTSYS_DETAILEDWINDOW::_treeWid_::check_virtsys_treeViewInit()
{
//    QPoint point(CHECK_VIRTSYS_DETAILEDWINDOW::m_ls->())
//    this->setGeometry()

    model->setHorizontalHeaderLabels(QStringList()<<"node"<<"prepory");

    QList<QStandardItem *> itemLsRoot;
    QStandardItem * itemRoot1=nullptr;
    QStandardItem * itemRoot2=nullptr;
    itemRoot1=new QStandardItem("xml");
    itemRoot2=new QStandardItem("暂无");
    itemLsRoot.append(itemRoot1);
    itemLsRoot.append(itemRoot2);
     model->appendRow(itemLsRoot);
//    QList<QStandardItem *> itemLsRoot;
//    QList<QStandardItem *> itemLsFirst;

//    QStandardItem * itemRoot1=nullptr;
//    QStandardItem * itemRoot2=nullptr;

//    QStandardItem * itemFirst1=nullptr;
//    QStandardItem * itemFirst2=nullptr;

//     itemRoot1=new QStandardItem("0");
//     itemRoot2=new QStandardItem("root node");
//     itemLsRoot.append(itemRoot1);
//     itemLsRoot.append(itemRoot2);

//     itemFirst1=new QStandardItem("0");
//     itemFirst2=new QStandardItem("first node");

//     itemFirst1->appendRow(new QStandardItem("----second node---"));
//     itemLsFirst.append(itemFirst1);
//     itemLsFirst.append(itemFirst2);

//     itemRoot1->appendRow(itemLsFirst);
//      model->appendRow(itemLsRoot);
//    model->item(0,0)->appendRow(itemLsFirst);

    QPoint point(this->parentWidget()->x(),this->parentWidget()->y());
    QSize size(this->parentWidget()->width(),this->parentWidget()->height());

    this->setModel(model);
    this->setGeometry(200,0,250,this->parentWidget()->height());
//    this->setMaximumSize(this->parentWidget()->width()-100,this->height());
    this->show();


}

void CHECK_VIRTSYS_DETAILEDWINDOW::_treeWid_::check_virtsys_updataTreeView()
{

    _listStyle_ * m_ls=CHECK_VIRTSYS_DETAILEDWINDOW::m_ls;
//    typedef void (*_test_go_)(const QString );
//    void * pts=dlopen("/root/rpmbuild/SOURCES/check-virtsys-1.0/src/test.so",RTLD_LAZY);
//    char *err=dlerror();
//    if(pts==nullptr){
//        std::cout<<"error:"<<err;
//    }else{
//        _test_go_ _dealXml_=nullptr;
//       _dealXml_= (_test_go_)dlsym(pts,"_dealXml_");
////       qDebug()<<check_virtsys_getXml();
//       _dealXml_("hello");
//    }
    const char * xml=check_virtsys_getXml().toStdString().c_str();
//    qDebug()<<xml;
    model->item(0,0)->setText("test");

}








