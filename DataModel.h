#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QDateTime>
#include <QVector>
#include <QDateTime>

struct DataModel {
    QVector<QPair<QDateTime, double>> points;
};

#endif // DATAMODEL_H
