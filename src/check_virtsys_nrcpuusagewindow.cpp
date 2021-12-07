

#include "check_virtsys_nrcpuusagewindow.h"

using namespace QtCharts;
CHECK_VIRTSYS_NRCPUUSAGEWINDOW::CHECK_VIRTSYS_NRCPUUSAGEWINDOW(QWidget *parent):
    nrcpuUsageChart(new QtCharts::QChart()),
    nrcpuUsageChartView(new QtCharts::QChartView(parent))
{
    nrcpuUsageChartView->setChart(nrcpuUsageChart);
}
