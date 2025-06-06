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
        // Метод проверяет, может ли данный класс рендерить линейный график.
        // Возвращает `true`, если тип графика равен "line".
    }

    QtCharts::QChartView* render(const DataModel& model, bool grayscale = false) override {
        using namespace QtCharts;

        auto *series = new QLineSeries();
        // Цвет линии до добавления
        if (grayscale) {
            series->setColor(Qt::black);
            series->setPen(QPen(Qt::black, 2));//если график ЧБ
        } else {
            series->setColor(Qt::blue);
            series->setPen(QPen(Qt::blue, 2));
        }
        for (const auto& p : model.points)
            series->append(p.first.toMSecsSinceEpoch(), p.second);
        // Добавление точек данных в серию. Дата преобразуется в миллисекунды с начала эпохи

        auto *chart = new QChart();
        chart->addSeries(series);// Создание графика и добавление в него данных.
        chart->legend()->hide();
        chart->setTitle("Линейный график");

        auto *axisX = new QDateTimeAxis();
        axisX->setFormat("dd.MM.yy");
        axisX->setTitleText("Дата");
        // Создание оси X с форматом даты "день.месяц.год" и заголовком.

        auto *axisY = new QValueAxis();
        axisY->setTitleText("Значение");

        chart->addAxis(axisX, Qt::AlignBottom);
        chart->addAxis(axisY, Qt::AlignLeft);// Добавление осей к графику с указанием их расположения.
        series->attachAxis(axisX);
        series->attachAxis(axisY);

        return new QChartView(chart);//возврат виджета `QChartView`, который отображает график.
    }
};



#endif // LINECHARTRENDER_H
