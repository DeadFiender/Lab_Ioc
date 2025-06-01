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
    // Регистрация Readers данных (JSON и SQLite).
    config.registerCharts<LineChartRender, BarChartRender, PieChartRender, ScatterChartRender>();
    // Регистрация рендеров графиков (линейный, столбчатый, круговой, точечный).

    auto readerFactory = config.getContainer().GetObject<ReaderFactory>();
    // Получение фабрики Readers данных.
    auto chartFactory  = config.getContainer().GetObject<ChartFactory>();
    // Получение фабрики рендеров графиков.

    MainWindow w(chartFactory, readerFactory);
    // Создание главного окна приложения с передачей фабрик.
    w.show();

    return a.exec();
}
