#ifndef ICHARTRENDER_H
#define ICHARTRENDER_H

#include <QString>
#include <QVector>
#include <QPointF>
#include <QtCharts/QChartView>
#include "DataModel.h"

class IChartRender {
public:
    virtual ~IChartRender() = default;// Виртуальный деструктор.
    virtual bool canRender(const QString& type) const = 0;
    // Чисто виртуальный метод, который определяет, может ли рендер обработать указанный тип графика.
    // `type` — строка, описывающая тип графика (например, "bar" или "line").
    virtual QtCharts::QChartView* render(const DataModel& model, bool grayscale = false) = 0;
    // Чисто виртуальный метод для отрисовки графика.
    // Принимает модель данных (`DataModel`) и флаг `grayscale`, указывающий на использование черно-белого стиля.
    // Возвращает указатель на виджет `QChartView`.
};
#endif // ICHARTRENDER_H
