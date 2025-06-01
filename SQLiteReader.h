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
    QString get() const override;
};



#endif // SQLITEREADER_H
