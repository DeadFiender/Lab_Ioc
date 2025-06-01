#ifndef SCATTERCHARTRENDER_H
#define SCATTERCHARTRENDER_H

#include "IChartRender.h"
#include <QtCharts/QScatterSeries>
#include <QtCharts/QChart>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

class ScatterChartRender : public IChartRender {
public:
    bool canRender(const QString& type) const override {
        return type == "scatter";
        // Метод проверяет, может ли данный класс рендерить точечную диаграмму.
        // Возвращает `true`, если тип графика равен "scatter".
    }

    QtCharts::QChartView* render(const DataModel& model, bool grayscale = false) override {
        using namespace QtCharts;

        auto *series = new QScatterSeries();
        for (const auto& p : model.points)
            series->append(p.first.toMSecsSinceEpoch(), p.second);
        // Добавление точек данных в серию. Дата преобразуется в миллисекунды с начала эпохи.

        series->setMarkerSize(10.0);
        // Установка размера маркера для точек.

        if (grayscale)
            series->setColor(Qt::black);

        auto *chart = new QChart();
        chart->addSeries(series);// Создание графика и добавление в него серии данных.
         chart->legend()->hide();
        chart->setTitle("Точечная диаграмма");

        auto *axisX = new QDateTimeAxis();
        axisX->setFormat("dd.MM");
        axisX->setTitleText("Дата");// Создание оси X с форматом даты "день.месяц" и заголовком.

        auto *axisY = new QValueAxis();
        axisY->setTitleText("Значение");

        chart->addAxis(axisX, Qt::AlignBottom);
        chart->addAxis(axisY, Qt::AlignLeft);// Добавление осей к графику с указанием их расположения.
        series->attachAxis(axisX);
        series->attachAxis(axisY);// Привязка осей к серии данных.

        return new QChartView(chart);// Создание и возврат виджета `QChartView`, который отображает график.
    }
};


#endif // SCATTERCHARTRENDER_H
