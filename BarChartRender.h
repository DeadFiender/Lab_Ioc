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
        // Реализация метода `canRender` из интерфейса `IChartRender`.
        // Метод проверяет, может ли данный класс отрендерить график указанного типа.
        // В данном случае он поддерживает только тип "bar" (столбчатая диаграмма).
    }

    QtCharts::QChartView* render(const DataModel& model, bool grayscale = false) override {
        using namespace QtCharts;

        auto *set = new QBarSet("Значения");// Каждый столбец будет иметь имя "Значения".
        QStringList categories;// Список категорий (меток для оси X).

        for (const auto& p : model.points) {//проход по всем парам дата-значение
            *set << p.second;//добавление в контейнер сет значений
            categories << p.first.toString("dd.MM");// Преобразование даты (`p.first`) в строку формата "день.месяц" и добавление в категории.
        }

        if (grayscale)
            set->setColor(Qt::black);

        auto *series = new QBarSeries();//серия данных для столб диаграммы
        series->append(set);//Метод append добавляет набор данных (set) в серию QBarSeries

        auto *chart = new QChart();
        chart->addSeries(series);// Создание графика
        chart->legend()->hide();// Скрытие легенды графика.
        chart->setTitle("Столбчатая диаграмма");

        auto *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        axisX->setTitleText("Дата");
// Создание оси X с категориями (датами) и установка её заголовка.

        auto *axisY = new QValueAxis();
        axisY->setTitleText("Значение");
// Создание оси Y и установка её заголовка.
        chart->addAxis(axisX, Qt::AlignBottom);
        chart->addAxis(axisY, Qt::AlignLeft);// Привязка осей к серии данных.
        series->attachAxis(axisX);
        series->attachAxis(axisY);

        return new QChartView(chart);
    }
};

#endif // BARCHARTRENDER_H
