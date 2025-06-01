#ifndef LINECHARTRENDER_H
#define LINECHARTRENDER_H

#include "IChartRender.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>

class LineChartRender : public IChartRender {
public:
    bool canRender(const QString& type) const override {
        return type == "line";
    }

    QtCharts::QChartView* render(const DataModel& model, bool grayscale = false) override {
        using namespace QtCharts;

        auto *series = new QLineSeries();
        // Цвет линии до добавления
        if (grayscale) {
            series->setColor(Qt::black);
            series->setPen(QPen(Qt::black, 2));
        } else {
            series->setColor(Qt::blue);
            series->setPen(QPen(Qt::blue, 2));
        }
        for (const auto& p : model.points)
            series->append(p.first.toMSecsSinceEpoch(), p.second);



        auto *chart = new QChart();
        chart->addSeries(series);
        chart->legend()->hide();
        chart->setTitle("Линейный график");

        auto *axisX = new QDateTimeAxis();
        axisX->setFormat("dd.MM.yy");
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



#endif // LINECHARTRENDER_H
