#include <QDebug>
#include <QObject>
#include "check_virtsys_thread.h"

CHECK_VIRTSYS_THREAD::CHECK_VIRTSYS_THREAD():
    m_threadStatus(false),
    isThreadExit(false),
    dataType(VIRDOMAIN),
    dataDealThread(new QThread()),
    virDataInfo(nullptr),
    domain_map(nullptr),
    netWork_map(nullptr)
{
    /* move obj to thread */
    this->moveToThread(dataDealThread);
    /* connect signal of thread started */
    connect(dataDealThread,&QThread::started,[=](){check_virtsys_dataDealCenter();});

    /* connect signal of thread finished */
    connect(dataDealThread,&QThread::finished,dataDealThread,&QThread::deleteLater);
}

CHECK_VIRTSYS_THREAD::~CHECK_VIRTSYS_THREAD()
{
    if(dataDealThread->isRunning()){
       check_virtsys_threadExit();
    }
}

void CHECK_VIRTSYS_THREAD::check_virtsys_threadStart()
{
    QMutexLocker muteLock(&mute);
    if(!m_threadStatus){
        m_threadStatus=true;
        isThreadExit=false;
        dataDealThread->start();
    }else{

    }
}

void CHECK_VIRTSYS_THREAD::check_virtsys_threadStop()
{
    QMutexLocker muteLock(&mute);
    if(m_threadStatus){
        m_threadStatus=false;
        isThreadExit=true;
    }
}

void CHECK_VIRTSYS_THREAD::check_virtsys_threadExit()
{

//    QMutexLocker muteLock(&mute);
    mute.lock();
    if(m_threadStatus){
        m_threadStatus=false;
        isThreadExit=true;
        mute.unlock();
                /*  make sure thread safe exit  */
        dataDealThread->quit();
        dataDealThread->wait(70); // wait 50ms外套
        dataDealThread=nullptr;
    }
}



void CHECK_VIRTSYS_THREAD::check_virtsys_moveToThread(QObject *& obj)
{
    obj->moveToThread(dataDealThread);
}

void CHECK_VIRTSYS_THREAD::check_virtsys_dealDataType(virtSysDataType dataType)
{
    QMutexLocker muteLock(&mute);
    this->dataType=dataType;
}







void CHECK_VIRTSYS_THREAD::check_virtsys_dataDealCenter()
{
    /*TODO:*/
    //qDebug()<<"thread:"<<QThread::currentThread()<<endl;
    while(1){
        {
            QMutexLocker muteLock(&mute);
            if(isThreadExit)
                break;
            virDataInfo->check_virtsys_virDataInfo(dataType);
        }
        msleep(500); //0.9 ms
//          usleep(50*1000);//0.5 s
    }
   // qDebug()<<"exit thread successed"<<endl;
}



void CHECK_VIRTSYS_THREAD::check_virtsys_setDataInfoIf(Check_Virtsys_VirtSysDataInfo *virDataInfo)
{
    this->virDataInfo=virDataInfo;
}

Check_Virtsys_VirtSysDataInfo *CHECK_VIRTSYS_THREAD::check_virtsys_getDataInfoIf()
{
    return virDataInfo;
}

std::multimap<unsigned int, Check_Virtsys_Libvirt_API::_checkVirSysVirDomainInfo_ *>
CHECK_VIRTSYS_THREAD::check_virtsys_getDomainInfo()
{
    QMutexLocker muteLock(&mute);
    domain_map=&virDataInfo->virsysDomInfo_Map;
    return  virDataInfo->virsysDomInfo_Map;
}


std::multimap<unsigned int, Check_Virtsys_Libvirt_API::_checkVirSysVirNetWorkInfo_ *>
CHECK_VIRTSYS_THREAD::check_virtsys_getNetWorkInfo()
{
    QMutexLocker muteLock(&mute);
    netWork_map =&virDataInfo->virsysNetWorkInfo_Map;
    return virDataInfo->virsysNetWorkInfo_Map;
}


QThread *&CHECK_VIRTSYS_THREAD::check_virtsys_getThreadObj()
{
    return dataDealThread;
}

void CHECK_VIRTSYS_THREAD::check_virtsys_free_DomainData()
{
    QMutexLocker muteLock(&mute);
    if(domain_map){
          for(auto iter=domain_map->begin();iter!=domain_map->end();){
              delete iter->second;
              iter->second=nullptr;
              domain_map->erase(iter++);
          }
          domain_map=nullptr;
    }

}
void CHECK_VIRTSYS_THREAD::check_virtsys_free_NetWorkData()
{
    QMutexLocker muteLock(&mute);
    if(netWork_map){
        for(auto iter=netWork_map->begin();iter!=netWork_map->end();){
            delete iter->second;
            iter->second=nullptr;
            netWork_map->erase(iter++);
        }
        netWork_map=nullptr;
    }
}











