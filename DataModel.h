#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QDateTime>
#include <QVector>
#include <QDateTime>

struct DataModel {
    QVector<QPair<QDateTime, double>> points;
    // Структура данных для хранения точек графика.
    // Каждая точка представляет собой пару: дата (`QDateTime`) и значение (`double`).
};

#endif // DATAMODEL_H
