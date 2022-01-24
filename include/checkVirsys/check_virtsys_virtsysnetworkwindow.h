#ifndef CHECK_VIRTSYS_VIRTSYSNETWORKINFO_H
#define CHECK_VIRTSYS_VIRTSYSNETWORKINFO_H

#include <vector>
#include <map>
#include <iostream>
#include <QWidget>
#include <QObject>
#include <QTabWidget>
#include <QTableWidgetItem>
#include "check_virtsys_manager.h"

//#include "check_virtsys_manager.h"
#include "check_virtsys_virtsysdatainfo.h"

class CHECK_VIRTSYS_MANAGER;
class Check_Virtsys_virtSysNetWorkWindow:public QTableWidget
{
public:
    Check_Virtsys_virtSysNetWorkWindow(QWidget * parent=nullptr);
    ~ Check_Virtsys_virtSysNetWorkWindow();
private:
    QTableWidget * m_netWorkTabWidget;
    friend class Check_Virtsys_Window;
    CHECK_VIRTSYS_MANAGER * virManager;
    CHECK_VIRTSYS_THREAD * thread;
    void check_virtsys_netWorkWidInit();
    void check_virtsys_updataNetworkTabWid();
    void check_virtsys_virNetWorkDevName(char *xml , char * dev_name);
};

#endif // CHECK_VIRTSYS_VIRTSYSNETWORKINFO_H
