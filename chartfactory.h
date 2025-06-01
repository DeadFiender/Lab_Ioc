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
    // Конструктор принимает список рендеров (объектов, реализующих интерфейс `IChartRender`)
    // и сохраняет их в приватном члене `m_renderers`.
    std::shared_ptr<IChartRender> get(const QString& type) {
        for (const auto& r : m_renderers)
            if (r->canRender(type))
                return r;
        return nullptr;
        // Метод `get` ищет рендер, который может отрендерить график указанного типа (`type`).
        // Для этого он перебирает все зарегистрированные рендеры и вызывает их метод `canRender`.
        // Если подходящий рендер найден, он возвращается. В противном случае возвращается `nullptr`.
    }

private:
    QVector<std::shared_ptr<IChartRender>> m_renderers;
    // Приватный член класса — список рендеров, которые могут быть использованы для отрисовки графиков.
};


#endif // CHARTFACTORY_H
