#include<QtXml>
#include<QString>
#include <algorithm>
#include <QDomDocument>
#include "check_virtsys_xml.h"
#include <vector>


CHECK_VIRTSYS_XML::CHECK_VIRTSYS_XML()
{

}

void CHECK_VIRTSYS_XML::check_virt_parseXml(const char * &xml)
{
    std::list<std::string> xmlList;

    auto *xmlMap=new std::map<std::string,std::list<std::string>>;
    QString tagName("");
    QDomDocument docment("");
    docment.setContent(QString(xml));
    QDomElement root=docment.documentElement();//read xml root node
    QDomNode node=root.firstChild(); //read xml firts child node
    QString name=root.attribute("type");
    while(!node.isNull()){
        tagName=node.toElement().tagName();
//        xmlMap->insert("root",{});
    }
}



void CHECK_VIRTSYS_XML::check_virt_parseXml_NetWorkInfo( const QString netWorkXml,
                                                        virDomainPtr dom,
                                                        struct _virDomainInterfaceStats *statsPtr)
{
    int test=0;
    int dom_state=-1;
    if(virDomainGetState(dom,&dom_state,0,0)<0){
        virErrorPtr err = virGetLastError();
        qDebug()<<"error :"<<err->message;
        return;
    }
    if(dom_state==VIR_DOMAIN_SHUTOFF || dom_state==VIR_DOMAIN_SHUTOFF){
        return;
    }
    //qDebug()<<"netWorkXml :"<<netWorkXml;
    QString tagName("");
    QDomDocument docment("");
    docment.setContent(netWorkXml);
    QDomElement root=docment.documentElement();//read xml root node
    QDomNode node=root.firstChild(); //read xml firts child node
    QString name=root.attribute("type");
//    struct _virDomainInterfaceStats stats;
    while(!node.isNull()){
        tagName=node.toElement().tagName();
        if(tagName.compare("devices")==0){
            QDomElement firstNode=root.firstChildElement("devices");
            for(;!firstNode.isNull();firstNode=firstNode.nextSiblingElement("devices")){
               // qDebug()<<"target_name :"<<firstNode.toElement().tagName();
                QDomElement secondNode=firstNode.firstChildElement("interface");
                for(;!secondNode.isNull();secondNode=secondNode.nextSiblingElement("interface")){
                     QDomElement thirdNode=secondNode.firstChildElement("target");
//                      for(;!thirdNode.isNull();thirdNode.nextSiblingElement("target")){
                          QString netIf=thirdNode.attribute("dev");
//                           qDebug()<<"target_name :"<<netIf;
//                          test++;
//                          qDebug()<<"test--:"<<test<<"dev"<<netIf;
                            virDomainInterfaceStats(dom,netIf.toLatin1().data(),statsPtr,sizeof(*statsPtr));
                            Check_Virtsys_VirtSysDataInfo * virDataInfo =reinterpret_cast<Check_Virtsys_VirtSysDataInfo *>(sender());
                            this->emit check_virt_emitSignal_saveNetWorkData(virDomainGetID(dom),netIf.toStdString(),*statsPtr,virDataInfo);
                }
                return;
            }
        }
        node=node.nextSibling();
    }
}




















