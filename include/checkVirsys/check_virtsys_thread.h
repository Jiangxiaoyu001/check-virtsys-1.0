#ifndef CHECK_VIRTSYS_THREAD_H
#define CHECK_VIRTSYS_THREAD_H


#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QThreadPool>
#include "check_virtsys.h"
#include "check_virtsys_virtsysdatainfo.h"



class CHECK_VIRTSYS_THREAD:public QThread
{
public:
    CHECK_VIRTSYS_THREAD();
    ~CHECK_VIRTSYS_THREAD();
private:
    QMutex mute;
    bool m_threadStatus;
    bool isThreadExit;
    virtSysDataType dataType;
    QThread * dataDealThread;
    Check_Virtsys_VirtSysDataInfo * virDataInfo;
    void check_virtsys_threadExit();
    void check_virtsys_dataDealCenter();
    Check_Virtsys_VirtSysDataInfo *check_virtsys_getDataInfoIf();
    std::multimap<unsigned int ,Check_Virtsys_Libvirt_API::_checkVirSysVirDomainInfo_ * > *domain_map;
    std::multimap<unsigned int ,Check_Virtsys_Libvirt_API::_checkVirSysVirNetWorkInfo_ * > *netWork_map;
public:
    std::multimap<unsigned int, Check_Virtsys_Libvirt_API::_checkVirSysVirDomainInfo_ *> check_virtsys_getDomainInfo();
    QThread *&check_virtsys_getThreadObj();
    std::multimap<unsigned int, Check_Virtsys_Libvirt_API::_checkVirSysVirNetWorkInfo_ *> check_virtsys_getNetWorkInfo();

    void check_virtsys_threadStart();
    void check_virtsys_threadStop();
    void check_virtsys_setDataInfoIf(Check_Virtsys_VirtSysDataInfo *);
    void check_virtsys_moveToThread(QObject *&);
    void check_virtsys_dealDataType(virtSysDataType );
    void check_virtsys_free_DomainData();
    void check_virtsys_free_NetWorkData();
};

#endif // CHECK_VIRTSYS_THREAD_H
