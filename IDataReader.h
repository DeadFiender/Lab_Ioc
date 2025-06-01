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
    virtual ~IDataReader() = default;// Виртуальный деструктор
    virtual DataModel read(const QString& path) = 0;
    // Чисто виртуальный метод для чтения данных из файла.
    // Принимает путь к файлу (`path`) и возвращает объект `DataModel`, содержащий точки данных.

    // Расширение, например "json" или "sqlite"
    virtual QString get() const = 0;
// Чисто виртуальный метод, возвращающий расширение файла, поддерживаемое данным читателем.
    // Метод парсинга даты
    virtual QDateTime parseDate(const QString& raw) const;

private:
    static const QVector<QString> FORMAT_DATE;
    // Статический вектор строк, хранящий возможные форматы дат.
    // Используется для парсинга дат в методе `parseDate`.
};

#endif // IDATAREADER_H
