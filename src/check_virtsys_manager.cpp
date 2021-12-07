#include "check_virtsys_manager.h"



CHECK_VIRTSYS_MANAGER * CHECK_VIRTSYS_MANAGER::m_manager=nullptr;


CHECK_VIRTSYS_MANAGER::CHECK_VIRTSYS_MANAGER():
    threadManager(new CHECK_VIRTSYS_THREAD()),
    cheVirXML(new CHECK_VIRTSYS_XML),
    virDataInfo(new Check_Virtsys_VirtSysDataInfo)

{
//    QObject *obj;
//    obj=qobject_cast<QObject *>(virDataInfo);
//    threadManager->check_virtsys_moveToThread(obj);
//    obj=qobject_cast<QObject *>(cheVirXML);
//    threadManager->check_virtsys_moveToThread(obj);


    QThread * thread=threadManager->check_virtsys_getThreadObj();
    virDataInfo->moveToThread(thread);
    cheVirXML->moveToThread(thread);

    threadManager->check_virtsys_setDataInfoIf(virDataInfo);

    connect(virDataInfo,&Check_Virtsys_VirtSysDataInfo::check_virtsys_emitSignal_parseXML,
            cheVirXML,&CHECK_VIRTSYS_XML::check_virt_parseXml_NetWorkInfo,Qt::DirectConnection);

    connect(cheVirXML,&CHECK_VIRTSYS_XML::check_virt_emitSignal_saveNetWorkData,
            virDataInfo,&Check_Virtsys_VirtSysDataInfo::check_virtsys_saveVirNetWorkData,Qt::DirectConnection);

    threadManager->check_virtsys_threadStart();

}

CHECK_VIRTSYS_MANAGER::~CHECK_VIRTSYS_MANAGER()
{
    delete threadManager;
    delete cheVirXML;
    delete virDataInfo;
}




void CHECK_VIRTSYS_MANAGER::check_virtsys_dataManagerCenter(virtSysDataType type)
{
    switch (type) {
    case VIRNODE:
        break;
    case VIRCONCECT:
        break;
    case VIRDOMAIN:
        threadManager->check_virtsys_dealDataType(VIRDOMAIN);
//        virDataInfo->check_virtsys_VirtDataControlCenter(virDomain);
        break;
    case VIRNETWORK:
         threadManager->check_virtsys_dealDataType(VIRNETWORK);
//         virDataInfo->check_virtsys_VirtDataControlCenter(virNetWork);
        break;
     case VIRSTORAGEVOL:
        break;
     default:
        break;
    }
}





void CHECK_VIRTSYS_MANAGER::check_virtsys_SwitchPages()
{

}

///* virtual function   must return a type father or child */
//CHECK_VIRTSYS_MANAGER *CHECK_VIRTSYS_MANAGER::check_virtsys_factoryIf(_INTERFACE_TYPE_ type)
//{
//    switch (type){
//    case THREAD_IF:
//        if(virThreadToManager==nullptr)
//            virThreadToManager=reinterpret_cast<CHECK_VIRTSYS_MANAGER *>(new CHECK_VIRTSYS_THREAD());
//        return virThreadToManager;
//    case XML_IF:
//        if(cheVirXML==nullptr)
//            virXmlToManager=reinterpret_cast<CHECK_VIRTSYS_MANAGER *>(new CHECK_VIRTSYS_XML());
//        return virXmlToManager;
//    case VIRDATA_IF:
//        if(virDataToManager==nullptr)
//            virDataToManager=reinterpret_cast<CHECK_VIRTSYS_MANAGER *>(new Check_Virtsys_VirtSysDataInfo());
//        return virDataToManager;
//    default:
//        break;
//    }
//    return this;
//}




