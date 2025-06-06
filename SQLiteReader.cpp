#include "SQLiteReader.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QDebug>

DataModel SqlReader::read(const QString& path) {
    static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "chart_sql_reader");//подключение к базе SQLite
    DataModel result;

    db.setDatabaseName(path);//какой файл SQLite будет использоваться для работы
    if (!db.open()) {
        qWarning() << "Ошибка открытия SQLite:" << db.lastError().text();
                                                   return result;
    }

    QString tableName;//для хранения имени таблицы
    QSqlQuery tablesQuery(db);//объект запроса tablesQuery, связанный с базой данных db
    if (tablesQuery.exec("SELECT name FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite_%' LIMIT 1")) {
        if (tablesQuery.next())//Проверяется, есть ли результат выполнения запроса (есть ли хотя бы одна таблица)
            tableName = tablesQuery.value(0).toString();
    }//Извлекается значение из первого столбца результата запроса (имя таблицы) и сохраняется в переменной tableName

    if (tableName.isEmpty()) {
        db.close();//если пусто закрыли базу вернули модель
        return result;
    }

    QSqlQuery query(db);//Создается новый объект запроса query, связанный с базой данных db
    if (!query.exec("SELECT * FROM " + tableName)) {//запроса на получение данных
        db.close();
        return result;
    }

    while (query.next()) {//Цикл проходит по всем строкам результата запроса
        QString rawDate = query.value(0).toString();//Извлекается значение из первого столбца текущей строки
        double val = query.value(1).toDouble();//Извлекается значение из второго столбца текущей строки

        QDateTime dt = parseDate(rawDate);//Вызывается метод parseDate, который пытается преобразовать строку с датой (rawDate) в объект QDateTime
        if (dt.isValid())//Проверяется, успешно ли преобразование даты
            result.points.append({ dt, val });//Если дата корректна, добавляется пара { QDateTime, double } в список точек модели данных result
    }

    db.close();
    return result;
}

QString SqlReader::get() const {
    return "sqlite";
}
