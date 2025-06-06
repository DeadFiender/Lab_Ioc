#include "JsonReader.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

DataModel JsonReader::read(const QString& path) {
    DataModel result;
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)) return result;
    // Открытие файла для чтения. Если файл не открывается, возвращается пустая модель данных.

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    // Чтение содержимого файла и преобразование его в объект `QJsonDocument`.

    if (!doc.isArray()) return result;
    // Проверка, является ли документ массивом JSON. Если нет, возвращается пустая модель данных.

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
            // Обработка значений объекта JSON:
            // - Если значение — строка, пытаемся парсить её как дату.
            // - Если значение — число, сохраняем его.
        }

        if (dt.isValid() && ok)
            result.points.append({ dt, number });
        // Если дата и число корректны, добавляем их в модель данных.
    }

    return result;
}

QString JsonReader::get() const {
    return "json";
    // Возвращает строку "json", указывая, что данный читатель работает с JSON-файлами.
}
