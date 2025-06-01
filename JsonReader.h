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
    QString get() const override;
};


#endif // JSONREADER_H
