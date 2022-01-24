#ifndef CHECK_VIRTSYS_VIRTSYSDOMINFO_H
#define CHECK_VIRTSYS_VIRTSYSDOMINFO_H

#include <vector>
#include <map>
#include <iostream>
#include <QWidget>
#include <QObject>
#include <QTabWidget>
#include <QTableWidgetItem>
#include "check_virtsys_manager.h"
#include "check_virtsys_virtsysdatainfo.h"


class  CHECK_VIRTSYS_MANAGER ;
class Check_Virtsys_VirtSysDomWindow:public QTableWidget
{
public:
    Check_Virtsys_VirtSysDomWindow(QWidget * parent=nullptr);
    ~Check_Virtsys_VirtSysDomWindow();
     void check_virtsys_updataDomInfoTabWin();
private:
    CHECK_VIRTSYS_MANAGER * virManager;
     CHECK_VIRTSYS_THREAD * thread;
    friend class Check_Virtsys_Window;
    void  check_virtsys_domWinInit();
};

#endif // CHECK_VIRTSYS_VIRTSYSDOMINFO_H
