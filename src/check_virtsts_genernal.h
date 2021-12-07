#ifndef CHECK_VIRTSTS_GENERNAL_H
#define CHECK_VIRTSTS_GENERNAL_H

#include <dlfcn.h>
#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include "check_virtsys_manager.h"

#define LIBSOCID_PATH "/opt/SSCard/sharedlib/libcheck.so"

class CHECK_VIRTSTS_GENERNAL:public QWidget
{
public:
    CHECK_VIRTSTS_GENERNAL(QWidget * parent=nullptr):QWidget(parent),
    m_tabVirType(new QLabel(this)),
    m_tabSocId(new QLabel(this)),
    m_tabSocState(new QLabel(this)),
    virManager(CHECK_VIRTSYS_MANAGER::check_virtsys_managerObj()),
    thread((CHECK_VIRTSYS_THREAD *)virManager->check_virtsys_factoryIf(THREAD_IF)),
    m_virTypeStr("  "),
    m_osTypeStr("  "){
        //check_virt_genernalWidInit();
    }
    void check_virt_genernalWidInit(){
        int w=70,h=40;
        QPalette m_pale(this->palette());
        m_pale.setColor(QPalette::Background,Qt::white);
        QWidget * parentWin=this->parentWidget();
        this->setAutoFillBackground(true);
        this->setPalette(m_pale);

        QSize  size(parentWin->width(),parentWin->height());
        QPoint point(parentWin->pos().x(),parentWin->pos().y());
        this->setGeometry(point.x(),point.y(),size.width(),size.height());

        QPoint m_point(this->width()/2-w,this->height()/2-h*3);
        QSize m_size(500,70);
        QRect m_rect(m_point,m_size);
        m_tabVirType->setGeometry(m_rect);
        check_virt_genernalWidUpdate();
        m_tabSocState->setGeometry(m_point.x(),m_point.y()+h,m_size.width(),m_size.height());
        m_tabSocId->setGeometry(m_point.x(),m_point.y()+2*h,m_size.width(),m_size.height());
        this->show();
    }
    void check_virt_genernalWidUpdate(){
        QString vir_type("");
        QString os_type("");
	m_osTypelist.clear();
	m_virTypelist.clear();
        auto map=thread->check_virtsys_getDomainInfo();
        /* judge whether list contain the same vir_type/os_type
         do not if is true  append the vir_type/os_type if  is true*/
        for(auto &_iter_:map){
            vir_type=_iter_.second->vir_type.c_str();
            os_type=_iter_.second->os_type.c_str();
            if(m_virTypelist.isEmpty())
                m_virTypelist.append(vir_type);
            if(m_osTypelist.isEmpty()){
                m_osTypelist.append(os_type);
	    }
           // else{
                for(auto &iter:m_virTypelist){
                    if(!iter.contains(vir_type)){
                        m_virTypelist.append(vir_type);
		    }
                }
                for(auto &iter:m_osTypelist){
                    if(!iter.contains(os_type))
                        m_osTypelist.append(os_type);
                }
            }
        //}
	m_virTypeStr.clear();
	m_osTypeStr.clear();
        for(auto &iter:m_virTypelist){
            m_virTypeStr.append(iter);
            /*remove front */
            m_virTypelist.pop_front();
        }
        for(auto &iter:m_osTypelist){
            m_osTypeStr.append(iter);
            /*remove front */
            m_osTypelist.pop_front();
        }
        client_get_socid();
        QFont m_font("Microsoft YaHei",13);
        m_tabVirType->setText(tr("虚拟化名称: %1").arg(m_virTypeStr));
        m_tabSocState->setText(tr("虚拟化方式: %1").arg(m_osTypeStr));
        m_tabSocId->setText(tr("SocId: %1").arg(m_socId));
        m_tabVirType->setFont(m_font);
        m_tabSocState->setFont(m_font);
        m_tabSocId->setFont(m_font);
        this->show();
    }
private:
    QLabel * m_tabVirType;
    QLabel * m_tabSocId;
    QLabel * m_tabSocState;
    CHECK_VIRTSYS_MANAGER * virManager;
    CHECK_VIRTSYS_THREAD * thread;
    QStringList m_virTypelist;
    QStringList m_osTypelist;
    QString m_virTypeStr;
    QString m_osTypeStr;
    QString m_socId;
    /*get soc id */
    void client_get_socid(){
        void *handle=NULL;
        char * error;
        handle = dlopen(LIBSOCID_PATH, RTLD_NOW);
        m_socId.clear();
        if(handle)
        {
            typedef int (*SOC_OPT_READ)(char * ,unsigned int );
            SOC_OPT_READ rbow_sscard_opt_read =(SOC_OPT_READ)dlsym(handle,"rbow_sscard_opt_read");
            if((error = dlerror()))
            {
//                m_socId.append(tr("not smzy system ,soc don't existed "));
                m_socId.append(tr("非专用机，SOC不存在 "));
                goto final;
            }else{
                int len=16 ;// 默认16字节
                char buff[20]={0};
                int ret=rbow_sscard_opt_read(buff,len);
                if(ret==16|| ret==32|| ret==48)
                {
                    m_socId.append(buff);
                    goto final;
                }else{
//                    m_socId.append(tr("get soc_id failed"));
                    m_socId.append(tr("获取SOC失败"));
                    goto final;
                }
            }
        }else{
//            m_socId.append(tr("not smzy system ,soc don't existed "));
            m_socId.append(tr("非专用机，SOC不存在 "));
            return;
        }
    final:{
         dlclose(handle);
    }
    }
};

#endif // CHECK_VIRTSTS_GENERNAL_H
