#ifndef CHECK_VIRTSYS_XML_H
#define CHECK_VIRTSYS_XML_H

#include <QObject>
#include <iostream>
#include <QStringList>

#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>



/* forward declare */
class Check_Virtsys_VirtSysDataInfo;

class CHECK_VIRTSYS_XML :public QObject
{
    Q_OBJECT
public:
    CHECK_VIRTSYS_XML();
    /* parse xml contents*/;
    void check_virt_parseXml(const char * &xml);
//private:
//    friend class Check_Virtsys_virtSysNetWorkWindow;
signals:
    void check_virt_emitSignal_saveNetWorkData(unsigned int , std::string ,_virDomainInterfaceStats &,
                                               Check_Virtsys_VirtSysDataInfo *);
public slots:
      void check_virt_parseXml_NetWorkInfo(const QString  , virDomainPtr ,
                                           _virDomainInterfaceStats *statsPtr);
};

#endif // CHECK_VIRTSYS_XML_H
