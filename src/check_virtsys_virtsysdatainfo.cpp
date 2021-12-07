
#include <string.h>
#include <QDomDocument>
#include <QtCore/qmath.h>
#include "check_virtsys_virtsysdatainfo.h"

/*
Check_Virtsys_VirtSysDataInfo *
Check_Virtsys_VirtSysDataInfo::virsysDataInfo=nullptr;
Check_Virtsys_VirtSysDataInfo *
Check_Virtsys_VirtSysDataInfo::check_virtsys_virsysDataInfoClass_Obj()
{
    if(virsysDataInfo==nullptr)
        virsysDataInfo=new Check_Virtsys_VirtSysDataInfo();
    return virsysDataInfo;
}
*/
//using namespace Check_Virtsys_Libvirt_API;

Check_Virtsys_VirtSysDataInfo::Check_Virtsys_VirtSysDataInfo()
{

}

Check_Virtsys_VirtSysDataInfo::~Check_Virtsys_VirtSysDataInfo()
{
    check_virtsys_free_virDomain();
    check_virtsys_free_virNetWork();
}

void Check_Virtsys_VirtSysDataInfo::check_virtsys_Debug_Msg()
{
    for(virsysDomInfo_Map_Iter=virsysDomInfo_Map.begin();
        virsysDomInfo_Map_Iter!=virsysDomInfo_Map.end();virsysDomInfo_Map_Iter++){
        std::cout<<"id_domain: "<<virsysDomInfo_Map_Iter->first<<std::endl
                 <<"name: "<<virsysDomInfo_Map_Iter->second->name<<std::endl
                 <<"state: "<<virsysDomInfo_Map_Iter->second->state<<std::endl
                 <<"maxmem: "<<virsysDomInfo_Map_Iter->second->maxMem/1024<<"MB"<<std::endl
                 <<"memory: "<<virsysDomInfo_Map_Iter->second->memory/1024<<"MB"<<std::endl
                 <<"nrvirCpu: "<<virsysDomInfo_Map_Iter->second->nrVirtCpu<<std::endl
                 <<"cputime: " <<(virsysDomInfo_Map_Iter->second->cpuTime/(qPow(10,9)))/(3600*24)<<"天"<<std::endl;
    }
}

/* namespace struct construct init*/
Check_Virtsys_Libvirt_API::CHECK_VIRTSYS_VIRDOMAIN_INFO::
CHECK_VIRTSYS_VIRDOMAIN_INFO()
{

}

Check_Virtsys_Libvirt_API::CHECK_VIRTSYS_VIRDOMAIN_INFO::
CHECK_VIRTSYS_VIRDOMAIN_INFO(const virDomainInfo info_dom,
                             Check_Virtsys_VirtSysDataInfo * obj):
    id(obj->virData->id),
    count(obj->virData->virCount),
    xml(obj->virData->desc),
    os_type(obj->virData->os_type),
    vir_type(obj->virData->virt_type),
    name(obj->virData->name),
    state(info_dom.state),
    maxMem(info_dom.maxMem),
    memory(info_dom.memory),
    nrVirtCpu(info_dom.nrVirtCpu),
    cpuTime(info_dom.cpuTime)

{

    obj->virsysDomInfo_Map.insert(std::make_pair(id,  this));


}



Check_Virtsys_Libvirt_API::CHECK_VIRTSYS_VIRDOMAIN_INFO::
~CHECK_VIRTSYS_VIRDOMAIN_INFO()
{
   // qDebug()<<"destory domain";
}


/* namespace struct VIRNETWORK construct init*/

Check_Virtsys_Libvirt_API::
CHECK_VIRTSYS_VIRNETWORK_INFO::CHECK_VIRTSYS_VIRNETWORK_INFO()
{

}

Check_Virtsys_Libvirt_API::CHECK_VIRTSYS_VIRNETWORK_INFO::
CHECK_VIRTSYS_VIRNETWORK_INFO(unsigned int id_dom,
                              std::string name,
                               _virDomainInterfaceStats &state
                              , Check_Virtsys_VirtSysDataInfo * virsysObj):

     id(id_dom),
     rx_bytes(state.rx_bytes),
     rx_packets(state.rx_packets),
     rx_errs(state.rx_errs),
     rx_drop(state.rx_drop),
     tx_bytes(state.tx_bytes),
     tx_packets(state.tx_packets),
     tx_errs(state.tx_errs),
     tx_drop(state.tx_drop)

{
    virNetName.push_back(name);
//    qDebug()<<"construct network";
    virsysObj->virsysNetWorkInfo_Map.insert(std::make_pair(id,this));
}


Check_Virtsys_Libvirt_API::
CHECK_VIRTSYS_VIRNETWORK_INFO::~CHECK_VIRTSYS_VIRNETWORK_INFO()
{
//    qDebug()<<"destory network";
}





void Check_Virtsys_VirtSysDataInfo::check_virtsys_getVistsysTotol()
{

}



// Init libvirt api
void Check_Virtsys_VirtSysDataInfo::check_virtsys_Libvirt_API_Init()
{

}





/* get vir domain info api*/
void Check_Virtsys_VirtSysDataInfo::check_virtsys_virDomainInfo()
{
    try {
        virErrorPtr error=nullptr;
        virConnectPtr conn =nullptr; /* the hypervisor connection */
        virDomainPtr *dom=nullptr;   /* the domain being checked */
        virDomainInfo info;        /* the information being fetched */
        int ret;
        int num_domains=0;

        QDomDocument docment("");
        QDomElement root;
        /*  all domain state */
       // const int list_flags = VIR_CONNECT_LIST_DOMAINS_INACTIVE;
        /* NULL means connect to local Xen hypervisor */
        conn = virConnectOpenReadOnly(nullptr);
        if (conn == nullptr) {
           // fprintf(stderr, "Failed to connect to hypervisor\n");
            goto error;
        }
       /* find all domain info*/
        num_domains = virConnectListAllDomains(conn, &dom, 0);
        for(int id_dom=0;id_dom<num_domains;id_dom++){
            ret = virDomainGetInfo(dom[id_dom], &info);
            if (ret < 0) {
                error=virGetLastError();
                qDebug()<<"error :"<<error->message;
                virFreeError(error);
                goto error;
            }
            this->virData->virCount=num_domains;
            this->virData->id=virDomainGetID(dom[id_dom]);
            this->virData->os_type.clear();
            this->virData->name.clear();
            this->virData->virt_type.clear();
            this->virData->desc.clear();
            char * os_type=nullptr;
            const char * name=nullptr;
            char *_name_=nullptr;
            char * desc=nullptr;
//            const char * virt_type=nullptr;
            os_type=virDomainGetOSType(dom[id_dom]);
            this->virData->os_type=os_type;
//            this->virData->os_type=virDomainGetOSType(dom[id_dom]);
            name=virDomainGetName(dom[id_dom]);
            this->virData->name=name;
//            this->virData->name=virDomainGetName(dom[id_dom]);
            desc=virDomainGetXMLDesc(dom[id_dom],0);
            this->virData->desc=desc;
//            this->virData->desc=virDomainGetXMLDesc(dom[id_dom],0);
            docment.setContent(QString(this->virData->desc.c_str()));
            root=docment.documentElement();//read xml root node
//            virt_type=root.attribute("type").toStdString().c_str();
            this->virData->virt_type=root.attribute("type").toStdString();
        /*new struct for save info, must be free in call this destory function*/
        new Check_Virtsys_Libvirt_API::_checkVirSysVirDomainInfo_(info,this);
            /* free memory*/
            free(os_type);
//            free((char *)name);
            free(desc);
//            free((char *)virt_type);
        }
     error:{

            if (dom != nullptr){
                for (int i = 0; i < num_domains; i++)
                    virDomainFree(dom[i]);
                free(dom);

            }
            if (conn != nullptr){
                int ret= virConnectClose(conn);
                if(ret<0){
                    error=virGetLastError();
                    qDebug()<<"error :"<<error->message;
                    virFreeError(error);
                }
            }
        }
    }catch(std::bad_exception &e){
        std::cout<<"execption:"<<e.what()<<std::endl;
    }catch(std::range_error &e){
        std::cout<<"execption:"<<e.what()<<std::endl;
    }catch (...) {
         std::cout<<"execption: other error"<<std::endl;
    }
}

void Check_Virtsys_VirtSysDataInfo::check_virtsys_virNetWorkInfo()
{

    /* there for virNetWork API
       const char * name=virNetworkGetName(network[j]);
       int net_num=virConnectListAllNetworks(conn,&network,1<<i);
       char * domain_desc=virNetworkGetXMLDesc(network[j],0);
       virDomainInterfaceStats(dom[id_dom],"default",&stats,sizeof(stats));
   */

    try {
        int num_domains=0;
        QString virNetName("");
        QString domain_desc("");
        virConnectPtr conn =nullptr;
        virErrorPtr error=nullptr;
        virDomainPtr *dom=nullptr;
        struct _virDomainInterfaceStats stats , *statsPtr;
        statsPtr=&stats;
        /*  init struct  _virDomainInterfaceStats  to make sure  struct member had a correct value  */
        memset(&stats,0,sizeof(stats));
        conn = virConnectOpenReadOnly(nullptr);
        if (conn == nullptr) {
            goto error;
        }
        num_domains=virConnectListAllDomains(conn, &dom, 0);

        for(int id_dom=0;id_dom<num_domains;id_dom++){
            char * xml=nullptr;
            domain_desc.clear();
            xml=virDomainGetXMLDesc(dom[id_dom],0);
            domain_desc=QString(xml);
            this->emit check_virtsys_emitSignal_parseXML(domain_desc,dom[id_dom],statsPtr);
             free(xml);
            /* remove append xml   */
            //m_domXMLDesc.append(domain_desc);
        }
    error:
       if (dom != nullptr)
       {
           for (int i = 0; i < num_domains; i++)
               virDomainFree(dom[i]);
           free(dom);
       }
       if (conn != nullptr)
       {
           int ret= virConnectClose(conn);
           if(ret<0){
               error=virGetLastError();
               qDebug()<<"error :"<<error->message;
               virFreeError(error);
           }
       }
    }catch(std::bad_exception &e){
        std::cout<<"execption:"<<e.what()<<std::endl;

    }catch(std::range_error &e){
        std::cout<<"execption:"<<e.what()<<std::endl;
    }catch (...) {
        std::cout<<"execption: other error"<<std::endl;
    }
}


/* slot function   */
void Check_Virtsys_VirtSysDataInfo::
check_virtsys_saveVirNetWorkData(unsigned int id, std::string virNetName,
                                 _virDomainInterfaceStats &stats,
                                 Check_Virtsys_VirtSysDataInfo * obj)
{
      new Check_Virtsys_Libvirt_API::
            CHECK_VIRTSYS_VIRNETWORK_INFO(id,virNetName,stats,obj);
}




void Check_Virtsys_VirtSysDataInfo::check_virtsys_free_virDomain()
{
    for(auto iter=virsysDomInfo_Map.begin();iter!=virsysDomInfo_Map.end();){
        delete iter->second;
        iter->second=nullptr;
        virsysDomInfo_Map.erase(iter++);
    }
}

void Check_Virtsys_VirtSysDataInfo::check_virtsys_free_virNetWork()
{
    for(auto iter=virsysNetWorkInfo_Map.begin();iter!=virsysNetWorkInfo_Map.end();){
        delete iter->second;
        iter->second=nullptr;
        virsysNetWorkInfo_Map.erase(iter++);
    }
}

void Check_Virtsys_VirtSysDataInfo::check_virtsys_free_virData()
{
     check_virtsys_free_virNetWork();
     check_virtsys_free_virDomain();
}


void Check_Virtsys_VirtSysDataInfo::check_virtsys_virDataInfo(virtSysDataType & data_type)
{

//    check_virtsys_free_virData();

    switch (data_type) {
        case VIRCONCECT:
        break;
        case VIRNODE:
        break;
        case VIRNETWORK:
            check_virtsys_free_virNetWork();
            check_virtsys_virNetWorkInfo();
        break;
        case VIRDOMAIN:
            check_virtsys_free_virDomain();
            check_virtsys_virDomainInfo();
        break;
        case VIRSTORAGEVOL:
        break;
    default:
        break;
    }
}












//template<class T>
//void Check_Virtsys_VirtSysDatanfo::check_virtsys_VirtDataControlCenter(T type )
//{
////    virtSysDataType dataType;
////    typeid (type).name();
////    if(typeid (type)==typeid (Check_Virtsys_VirtSysDomWindow *))
////         dataType=VIRCONCECT;
////    if(typeid (type)==typeid (int)){

////    }else if(typeid (type)==typeid (std::string)){

////    }
////    check_virtsys_virDataInfo(dataType);

//}


//void Check_Virtsys_VirtSysDatanfo::check_virtsys_VirtDataControlCenter(Check_Virtsys_VirtSysDomWindow *virtSysWin)
//{
//    Q_UNUSED(virtSysWin)
//    Check_Virtsys_VirtSysDomWindow *test;
//    check_virtsys_VirtDataControlCenter(virtSysWin);
//      //virtSysWin->Check_Virtsys_freeMemory();
////    Check_Virtsys_VirtSysDatanfo *(virtSysWinSub)=reinterpret_cast<Check_Virtsys_VirtSysDatanfo *>(virtSysWin);
////    virtSysWinSub=new Check_Virtsys_VirtSysDatanfo();
//}





