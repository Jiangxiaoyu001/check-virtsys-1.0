#ifndef CHECK_VIRTSYS_MANAGER_H
#define CHECK_VIRTSYS_MANAGER_H

#include "check_virtsys.h"
#include "check_virtsys_xml.h"
#include "check_virtsys_thread.h"
#include "check_virtsys_virtsysdatainfo.h"



class CHECK_VIRTSYS_MANAGER:public QObject,public CHECK_VIRTSYS
{
    Q_OBJECT
private:
    int b;
    static CHECK_VIRTSYS_MANAGER * m_manager;
    CHECK_VIRTSYS_MANAGER();
    ~CHECK_VIRTSYS_MANAGER();
     CHECK_VIRTSYS_THREAD * threadManager;
     CHECK_VIRTSYS_XML * cheVirXML;
     Check_Virtsys_VirtSysDataInfo * virDataInfo;
public:

    /*declare a templete function to create some obj in factory module*/
        void * check_virtsys_factoryIf(_INTERFACE_TYPE_ type){
        switch (type){
        case THREAD_IF:{
            if(threadManager==nullptr)
                threadManager=(new CHECK_VIRTSYS_THREAD());
            return threadManager;
        }
        case XML_IF:{
            if(cheVirXML==nullptr)
                cheVirXML=(new CHECK_VIRTSYS_XML());
            return cheVirXML;
        }
        case VIRDATA_IF:{
            if(virDataInfo==nullptr)
                virDataInfo=(new Check_Virtsys_VirtSysDataInfo());
            return virDataInfo;
        }
        default:
            return nullptr;
        }
    }
    /* define */
    class _CG_{
    public:
        ~_CG_(){
            if(m_manager)
                delete m_manager;
            m_manager=nullptr;
        }
    };
    //created singel obj
    static CHECK_VIRTSYS_MANAGER * check_virtsys_managerObj(){
        if(m_manager==nullptr){
             m_manager=new CHECK_VIRTSYS_MANAGER;
             static _CG_ clear;
        }
        return m_manager;
    }
    void check_virtsys_dataManagerCenter(virtSysDataType );
signals:
    void check_virtsys_emitSignal_dealData(virtSysDataType);

public slots:
protected:
         virtual void check_virtsys_SwitchPages();
};

#endif // CHECK_VIRTSYS_MANAGER_H














