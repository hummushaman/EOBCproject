#include "occupancyrateentry.h"

OccupancyRateEntry::OccupancyRateEntry(){}

OccupancyRateEntry::OccupancyRateEntry(QString aDateChanged, QString aCareType, float anOccupancyRate)
{
    dateChanged = aDateChanged;
    careType = aCareType;
    occupancyRate = anOccupancyRate;
}


QString OccupancyRateEntry::getCareType()
{
    return careType;
}
float OccupancyRateEntry::getOccupancyRate()
{
    return occupancyRate;
}

QString OccupancyRateEntry::getDateOfChange()
{
    return dateChanged;
}
