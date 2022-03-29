#ifndef Check_Virtsys_VirtSysDatanfo_H
#define Check_Virtsys_VirtSysDatanfo_H

#include <QDebug>
#include <map>
#include <iostream>
#include <string.h>
#include <QThread>
#include <QObject>
#include <typeinfo>
#include <iostream>
//#include <Python>
#include <QMainWindow>
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>


class Check_Virtsys_VirtSysDataInfo;  // forward define class

QT_BEGIN_NAMESPACE
namespace  Check_Virtsys_Libvirt_API{

    typedef struct CHECK_VIRTSYS_CONNECT_INFO{ /* virt connect */
        CHECK_VIRTSYS_CONNECT_INFO();
        ~CHECK_VIRTSYS_CONNECT_INFO();
    }_checkVirSysConnectInfo_;
    typedef struct CHECK_VIRTSYS_VIRDOMAIN_INFO{ /* virt domain*/

        unsigned int id;           /* the virsys id for domain  */
        size_t count;
        std::string xml;           /* the virtsys desc xml*/
        std::string os_type;       /* the virsys type  PV/HVM */
        std::string vir_type;      /* the vri type KVM....*/
        std::string name;          /* the virsys name  */
        unsigned int state;        /* the running state, one of virDomainState */
        unsigned long maxMem;       /* the maximum memory in KBytes allowed */
        unsigned long memory;       /* the memory in KBytes used by the domain */
        unsigned short nrVirtCpu;   /* the number of virtual CPUs for the domain */
        unsigned long long cpuTime; /* the CPU time used in nanoseconds */
     public:
        CHECK_VIRTSYS_VIRDOMAIN_INFO();
        CHECK_VIRTSYS_VIRDOMAIN_INFO(unsigned int,virDomainInfo ,virDomainPtr *);
        CHECK_VIRTSYS_VIRDOMAIN_INFO(const virDomainInfo info_dom,
                                      Check_Virtsys_VirtSysDataInfo *);
        ~CHECK_VIRTSYS_VIRDOMAIN_INFO();
    }_checkVirSysVirDomainInfo_;
    typedef struct CHECK_VIRTSYS_VIRNODE_INFO{ /* virt Node*/
        CHECK_VIRTSYS_VIRNODE_INFO();
        ~CHECK_VIRTSYS_VIRNODE_INFO();
    }_checkVirSysVirNodeInfo_;
    typedef struct CHECK_VIRTSYS_VIRNETWORK_INFO{ /* virt networt */
        unsigned int id;
//        std::StringL virNetName;
        std::list<std::string> virNetName;
        long long rx_bytes;
        long long rx_packets;
        long long rx_errs;
        long long rx_drop;
        long long tx_bytes;
        long long tx_packets;
        long long tx_errs;
        long long tx_drop;
        CHECK_VIRTSYS_VIRNETWORK_INFO();
        CHECK_VIRTSYS_VIRNETWORK_INFO( unsigned int , std::string ,_virDomainInterfaceStats &,
                                        Check_Virtsys_VirtSysDataInfo *);
        ~CHECK_VIRTSYS_VIRNETWORK_INFO();
    }_checkVirSysVirNetWorkInfo_;
    typedef struct CHECK_VIRTSYS_VIRSTORAGEVOL_INFO{ /* virt STORAGEVOL */
        CHECK_VIRTSYS_VIRSTORAGEVOL_INFO();
        ~CHECK_VIRTSYS_VIRSTORAGEVOL_INFO();
    }_checkVirSysVirStorageVolInfo_;
}
QT_END_NAMESPACE




typedef enum _VirtSysDataType_{
    VIRCONCECT,
    VIRNODE,
    VIRNETWORK,
    VIRDOMAIN,
    VIRSTORAGEVOL
}virtSysDataType;

/* forword declear */
class Check_Virtsys_VirtSysDomWindow;
class Check_Virtsys_virtSysNetWorkWindow;
class Check_Virtsys_VirtSysDataInfo:public QObject
{
    Q_OBJECT
 public:
    /* created map for save virDomain info , can be called to other class*/
//    static Check_Virtsys_VirtSysDataInfo * check_virtsys_virsysDataInfoClass_Obj();
    std::multimap<unsigned int ,Check_Virtsys_Libvirt_API::_checkVirSysVirDomainInfo_ * > virsysDomInfo_Map;

    /* consided  one virsys had more virNetWork ,
     * in order to save all virNetWorkData for one of the virsys,
     *  so using multimap  instead of using map that map-key can be repeated  */
    std::multimap<unsigned int ,Check_Virtsys_Libvirt_API::_checkVirSysVirNetWorkInfo_ * > virsysNetWorkInfo_Map;

    /*    */
    template<class T> void check_virtsys_VirtDataControlCenter(T type){
            virtSysDataType dataType;
            typeid (type).name();
            if(typeid (type)==typeid (Check_Virtsys_VirtSysDomWindow *))
                 dataType=VIRDOMAIN;
            if(typeid (type)==typeid (Check_Virtsys_virtSysNetWorkWindow *)){
               dataType=VIRNETWORK;
            }else if(typeid (type)==typeid (std::string)){

            }
            check_virtsys_virDataInfo(dataType);
    }
    struct _VIRSYSDATA_{
        unsigned int id;
        std::string name;
        size_t virCount;
        std::string desc;
        std::string virt_type;
        std::string os_type;
    }virData_={
        .id=0,
        .name=(""),
        .virCount=0,
        .desc=(""),
        .virt_type=(""),
        .os_type=("")
    };
    typedef struct _VIRSYSDATA_ _virData_;
    _virData_ *virData=&virData_;
    void check_virtsys_Debug_Msg();
    void check_virtsys_virDataInfo(virtSysDataType & );
    Check_Virtsys_VirtSysDataInfo();
    ~Check_Virtsys_VirtSysDataInfo();
private:
//    static Check_Virtsys_VirtSysDataInfo * virsysDataInfo;
     std::map<unsigned int ,Check_Virtsys_Libvirt_API::_checkVirSysVirDomainInfo_ * >::
        iterator virsysDomInfo_Map_Iter;
     virtSysDataType check_virtsys_getVirtsysDataType();
     void check_virtsys_getVistsysTotol();
     unsigned int check_virtsys_getVirtsysRun();
     unsigned int check_virtsys_getVirtsysStop();
     void check_virtsys_Libvirt_API_Init();
     void check_virtsys_virDomainInfo();
     void check_virtsys_virNetWorkInfo();
     void check_virtsys_free_virDomain();
     void check_virtsys_free_virNetWork();
     void check_virtsys_free_virData();
signals:
     /*  may be i will consider ?,  can be send a type wit custom   */
     void check_virtsys_emitSignal_parseXML(QString &,virDomainPtr & ,struct _virDomainInterfaceStats * &);
public slots:
     void check_virtsys_saveVirNetWorkData(unsigned int , std::string ,_virDomainInterfaceStats &,
                                           Check_Virtsys_VirtSysDataInfo *);
};

#endif // Check_Virtsys_VirtSysDatanfo_H


