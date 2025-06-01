#include "mainwindow.h"
#include "AppConfigurator.h"
#include "JsonReader.h"
#include "SQLiteReader.h"
#include "LineChartRender.h"
#include "BarChartRender.h"
#include "PieChartRender.h"
#include "ScatterChartRender.h"
#include <QApplication>

int IOCContainer::s_nextTypeId = 115094801;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AppConfigurator config;
    config.registerReaders<JsonReader, SqlReader>();
    config.registerCharts<LineChartRender, BarChartRender, PieChartRender, ScatterChartRender>();

    auto readerFactory = config.getContainer().GetObject<ReaderFactory>();
    auto chartFactory  = config.getContainer().GetObject<ChartFactory>();

    MainWindow w(chartFactory, readerFactory);
    w.show();

    return a.exec();
}
