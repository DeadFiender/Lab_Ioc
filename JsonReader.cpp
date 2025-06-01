#include "JsonReader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

DataModel JsonReader::read(const QString& path) {
    DataModel result;
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) return result;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isArray()) return result;

    QJsonArray array = doc.array();
    for (const auto& val : array) {
        if (!val.isObject()) continue;

        QJsonObject obj = val.toObject();
        QDateTime dt;
        double number = 0;
        bool ok = false;

        for (const auto& v : obj) {
            if (v.isString()) dt = parseDate(v.toString());
            if (v.isDouble()) {
                number = v.toDouble();
                ok = true;
            }
        }

        if (dt.isValid() && ok)
            result.points.append({ dt, number });
    }

    return result;
}

QString JsonReader::get() const {
    return "json";
}
