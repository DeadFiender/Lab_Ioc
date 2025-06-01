#ifndef IDATAREADER_H
#define IDATAREADER_H

#include <QString>
#include <QVector>
#include <QPointF>
#include <QPair>
#include <QDateTime>
#include "DataModel.h"

class IDataReader {
public:
    virtual ~IDataReader() = default;

    // Основной метод чтения данных
    virtual DataModel read(const QString& path) = 0;

    // Расширение, например "json" или "sqlite"
    virtual QString get() const = 0;

    // Метод парсинга даты
    virtual QDateTime parseDate(const QString& raw) const;

private:
    static const QVector<QString> FORMAT_DATE;
};

#endif // IDATAREADER_H
