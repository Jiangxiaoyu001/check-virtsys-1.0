#ifndef CHECK_VIRTSTS_GENERNALWINDOW_H
#define CHECK_VIRTSTS_GENERNALWINDOW_H


#include <QObject>
#include <QTabWidget>
#include <QTableWidgetItem>

class CHECK_VIRTSYS_MANAGER;
class CHECK_VIRTSTS_GENERNALWINDOW
{
public:
    CHECK_VIRTSTS_GENERNALWINDOW(QWidget * parent=nullptr);
    ~CHECK_VIRTSTS_GENERNALWINDOW();
    QTableWidget * check_virtsys_getGenernalWin();
    void chech_virtsys_updataGenernalWin();
private:
    QTableWidget * m_genernalWin;
    QTableWidgetItem * m_tabItem;
    CHECK_VIRTSYS_MANAGER * virManager;
    void check_virtsys_genernalWinInit();
};

#endif // CHECK_VIRTSTS_GENERNALWINDOW_H
