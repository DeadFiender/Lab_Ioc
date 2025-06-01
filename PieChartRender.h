#ifndef PIECHARTRENDER_H
#define PIECHARTRENDER_H

#include "IChartRender.h"
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>

class PieChartRender : public IChartRender {
public:
    bool canRender(const QString& type) const override {
        return type == "pie";
        // Метод проверяет, может ли данный класс рендерить круговую диаграмму.
    }

    QtCharts::QChartView* render(const DataModel& model, bool grayscale = false) override {
        using namespace QtCharts;

        auto *series = new QPieSeries();

        for (const auto& p : model.points) {
            QString label = p.first.toString("dd.MM");
            QPieSlice *slice = series->append(label, p.second);

            if (grayscale) {
                slice->setBrush(QBrush(Qt::black));
            }
        }

        auto *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Круговая диаграмма");
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);

        return new QChartView(chart);
    }
};

#endif // PIECHARTRENDER_H
