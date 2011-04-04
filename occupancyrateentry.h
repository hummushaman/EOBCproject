#ifndef OCCUPANCYRATEENTRY_H
#define OCCUPANCYRATEENTRY_H
#include <QObject>

class OccupancyRateEntry
{
public:
    OccupancyRateEntry();
    OccupancyRateEntry(QString aDateChanged, QString aCareType, float anOccupancyRate);

private:
    QString getDateOfChange();
    QString getCareType(); //AC,CCC,LTC
    float getOccupancyRate();

    QString dateChanged;
    QString careType;
    float occupancyRate;
};

#endif // OCCUPANCYRATEENTRY_H
