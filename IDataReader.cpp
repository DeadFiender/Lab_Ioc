#include "IDataReader.h"

const QVector<QString> IDataReader::FORMAT_DATE = {
    "dd.MM.yyyy HH:mm", "dd.MM.yyyy",
    "yyyy.MM.dd HH:mm", "yyyy.MM.dd",
    "dd-MM-yyyy HH:mm", "dd-MM-yyyy",
    "yyyy-MM-dd HH:mm", "yyyy-MM-dd"
};
// Статический вектор строк, хранящий возможные форматы дат.
// Используется для парсинга дат в методе `parseDate`.

QDateTime IDataReader::parseDate(const QString& raw) const {
    for (const auto& format : FORMAT_DATE) {
        QDateTime dt = QDateTime::fromString(raw, format);
        if (dt.isValid()) return dt;
        // Попытка преобразовать строку в объект `QDateTime` с использованием каждого формата.
        // Если преобразование успешно, возвращается объект `QDateTime`.
    }

    // Альтернатива: "date minutes"
    const auto parts = raw.split(' ');
    if (parts.size() == 2) {
        QDate d = QDate::fromString(parts[0], "dd.MM.yyyy");
        bool ok = false;
        int mins = parts[1].toInt(&ok);
        if (d.isValid() && ok)
            return d.startOfDay().addSecs(mins * 60);
        // Если строка имеет формат "дата минуты", преобразуем её в `QDateTime`.
    }

    return {};
}
