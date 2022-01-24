#ifndef CHECK_VIRTSYS_H
#define CHECK_VIRTSYS_H

#include <QObject>


typedef enum _VIRDATATYPE_{
    VIRNODE_TYPE,
    VIRCONNECT_TYPE,
    VIRDOMAIN_TYPE,
    VIRNETWORK_TYPE,
    VIRSTORAGEVOL_TYPR,
}VIRDATATYPE;



typedef enum _interface_{
    VIRCONNECT_IF,
    VIRDOMAIN_IF,
    VIRNETWORK_IF,
    VIRNODE_IF,
    VIRSTORAGEVOL_IF,
    XML_IF,
    VIRDATA_IF,
    THREAD_IF
}_INTERFACE_TYPE_;

class CHECK_VIRTSYS
{

public:
    explicit CHECK_VIRTSYS(){};
    virtual ~CHECK_VIRTSYS(){};
    virtual void check_virtsys_SwitchPages()=0;
};

#endif // CHECK_VIRTSYS_H
