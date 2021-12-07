#ifndef CHECK_VIRTSYS_NRCPUUSAGEWINDOW_H
#define CHECK_VIRTSYS_NRCPUUSAGEWINDOW_H

/* using forward declear , can avoid to include header-file by repeatedly*/
//class QChart ;

class QGraphicsScene;
class QWidget ;

#include <QtCharts>
class CHECK_VIRTSYS_NRCPUUSAGEWINDOW
{
public:
    CHECK_VIRTSYS_NRCPUUSAGEWINDOW(QWidget * parent=nullptr);
    ~CHECK_VIRTSYS_NRCPUUSAGEWINDOW();
private:
    QChart * nrcpuUsageChart;
    QChartView * nrcpuUsageChartView;
    QGraphicsScene * isSceneCPU;
};

#endif // CHECK_VIRTSYS_NRCPUUSAGEWINDOW_H
