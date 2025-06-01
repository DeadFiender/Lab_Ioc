#ifndef BARCHARTRENDER_H
#define BARCHARTRENDER_H

#include "IChartRender.h"
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QDateTimeAxis>

class BarChartRender : public IChartRender {
public:
    bool canRender(const QString& type) const override {
        return type == "bar";
    }

    QtCharts::QChartView* render(const DataModel& model, bool grayscale = false) override {
        using namespace QtCharts;

        auto *set = new QBarSet("Значения");
        QStringList categories;

        for (const auto& p : model.points) {
            *set << p.second;
            categories << p.first.toString("dd.MM");
        }

        if (grayscale)
            set->setColor(Qt::black);

        auto *series = new QBarSeries();
        series->append(set);

        auto *chart = new QChart();
        chart->addSeries(series);
        chart->legend()->hide();
        chart->setTitle("Столбчатая диаграмма");

        auto *axisX = new QBarCategoryAxis();
        axisX->append(categories);
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

#endif // BARCHARTRENDER_H
