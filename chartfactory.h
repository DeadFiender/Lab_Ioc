#ifndef CHARTFACTORY_H
#define CHARTFACTORY_H

#include <QString>
#include <QVector>
#include <memory>
#include "IChartRender.h"

class ChartFactory {
public:
    ChartFactory(const QVector<std::shared_ptr<IChartRender>>& renderers)
        : m_renderers(renderers) {}

    std::shared_ptr<IChartRender> get(const QString& type) {
        for (const auto& r : m_renderers)
            if (r->canRender(type))
                return r;
        return nullptr;
    }

private:
    QVector<std::shared_ptr<IChartRender>> m_renderers;
};


#endif // CHARTFACTORY_H
