#ifndef JSONREADER_H
#define JSONREADER_H

#include "IDataReader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class JsonReader : public IDataReader {
public:
    DataModel read(const QString& path) override;
    // Реализация метода `read` из интерфейса `IDataReader`.
    // Читает данные из JSON-файла по указанному пути и возвращает объект `DataModel`.
    QString get() const override;
    // Реализация метода `get` из интерфейса `IDataReader`.
    // Возвращает строку "json", указывая, что данный читатель работает с JSON-файлами.
};


#endif // JSONREADER_H
