#ifndef SQLITEREADER_H
#define SQLITEREADER_H

#include "IDataReader.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

class SqlReader : public IDataReader {
public:
    DataModel read(const QString& path) override;
    // Реализация метода `read` из интерфейса `IDataReader`.
    // Читает данные из SQLite-базы данных по указанному пути.
    QString get() const override;
    // Реализация метода `get` из интерфейса `IDataReader`.
    // Возвращает строку "sqlite", указывая, что данный читатель работает с SQLite.
};



#endif // SQLITEREADER_H
