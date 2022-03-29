#ifndef CHECK_VIRTSYS_WINDOW_H
#define CHECK_VIRTSYS_WINDOW_H
#include "check_virtsys.h"
#include <QWidget>
#include <QObject>
#include <QListWidget>
#include <QFile>
#include <QDebug>
#include <map>
#include <QFont>
#include <QTimer>
#include <QtCharts>
#include <QGraphicsWidget>
#include <QApplication>
#include <QPushButton> //
#include <QStackedWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include "check_virtsys_manager.h"
//#include "Check_Virtsys_VirtSysDomWindow.h"
//#include "Check_Virtsys_virtSysNetWorkWindow.h"


class CHECK_VIRTSTS_GENERNAL;
class CHECK_VIRTSYS_ABOUTDIALOG;
class CHECK_VIRTSYS_DETAILEDWINDOW;
class Check_Virtsys_Window:public QWidget

{
    Q_OBJECT
public:
    Check_Virtsys_Window(QWidget * parent=nullptr);
    ~Check_Virtsys_Window();
    QWidget *& check_virtsys_getWindow(){ return m_MainWidget;}
private:
    std::list<QWidget *> windowList;
    QTime  m_time;
    QTimer timer;
    size_t mesc;
    bool m_timerStatus;
    QWidget * m_MainWidget;
    QListWidget * m_listWidget;
    QStackedWidget *m_staWidget;
    QListWidgetItem * m_listWinItem;


    CHECK_VIRTSYS_MANAGER * virManager;
    CHECK_VIRTSTS_GENERNAL * genWidget;
    CHECK_VIRTSYS_ABOUTDIALOG * aboutDialog;
    CHECK_VIRTSYS_DETAILEDWINDOW * detailWidget;
    Check_Virtsys_VirtSysDomWindow * domWidget;

    Check_Virtsys_virtSysNetWorkWindow * netWorkWidget;

    /* set window background */


    void addWindowList();
    void setBackground();
    void removeWindlwList();
    void Check_Virtsys_CreateLayout();
    void check_virtsys_setWindowSize();
    void Check_Virtsys_startTimer();
    void Check_Virtsys_stopTimer();

    void Check_Virtsys_WindowInit();
    void Check_Virtsys_InsertListWinItem(int row=0);
    void Check_Virtsys_AddListWinItem();
    void Check_Virtsys_RemoveListWinItem();
    void Check_Virtsys_loadStyleSheet();
    void Check_Virtsys_tabWidget_DomainInfo();
    void Check_Virtsys_tabWidget_NetWorkInfo();

    void Check_Virtsys_updataChart_cpuUsage();
    void Check_Virtsys_updataChart_netWorkUsage();

    void Check_Virtsys_tabWidgetUpdate_NetWorkInfo();
    void Check_Virtsys_tabWidgetUpdate_NetWorkInfo_test();

    bool check_virtsys_vailedTime();
private:
    signals:
private slots:
    void Check_Virtsys_changedListItem();
    void check_virtsys_SwitchPages() ;
    void Check_Virtsys_updataWidget();
    void Check_Virtsys_tabWidDomain_updataItem();
    void Check_Virtsys_tabWidNetWork_updataItem();

};

#endif // CHECK_VIRTSYS_WINDOW_H
