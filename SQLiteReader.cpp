#include "SQLiteReader.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QDebug>

DataModel SqlReader::read(const QString& path) {
    static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "chart_sql_reader");
    DataModel result;

    db.setDatabaseName(path);
    if (!db.open()) {
        qWarning() << "Ошибка открытия SQLite:" << db.lastError().text();
                                                   return result;
    }

    QString tableName;
    QSqlQuery tablesQuery(db);
    if (tablesQuery.exec("SELECT name FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite_%' LIMIT 1")) {
        if (tablesQuery.next())
            tableName = tablesQuery.value(0).toString();
    }

    if (tableName.isEmpty()) {
        db.close();
        return result;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM " + tableName)) {
        db.close();
        return result;
    }

    while (query.next()) {
        QString rawDate = query.value(0).toString();
        double val = query.value(1).toDouble();

        QDateTime dt = parseDate(rawDate);
        if (dt.isValid())
            result.points.append({ dt, val });
    }

    db.close();
    return result;
}

QString SqlReader::get() const {
    return "sqlite";
}
