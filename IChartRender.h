#ifndef ICHARTRENDER_H
#define ICHARTRENDER_H

#include <QString>
#include <QVector>
#include <QPointF>
#include <QtCharts/QChartView>
#include "DataModel.h"

class IChartRender {
public:
    virtual ~IChartRender() = default;
    virtual bool canRender(const QString& type) const = 0;
    virtual QtCharts::QChartView* render(const DataModel& model, bool grayscale = false) = 0;
};
#endif // ICHARTRENDER_H
