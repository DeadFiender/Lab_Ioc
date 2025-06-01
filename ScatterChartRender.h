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
    }

    QtCharts::QChartView* render(const DataModel& model, bool grayscale = false) override {
        using namespace QtCharts;

        auto *series = new QScatterSeries();
        for (const auto& p : model.points)
            series->append(p.first.toMSecsSinceEpoch(), p.second);

        series->setMarkerSize(10.0);

        if (grayscale)
            series->setColor(Qt::black);

        auto *chart = new QChart();
        chart->addSeries(series);
         chart->legend()->hide();
        chart->setTitle("Точечная диаграмма");

        auto *axisX = new QDateTimeAxis();
        axisX->setFormat("dd.MM");
        axisX->setTitleText("Дата");

        auto *axisY = new QValueAxis();
        axisY->setTitleText("Значение");

        chart->addAxis(axisX, Qt::AlignBottom);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisX);
        series->attachAxis(axisY);

        return new QChartView(chart);
    }
};


#endif // SCATTERCHARTRENDER_H
