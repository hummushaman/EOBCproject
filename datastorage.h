//DATASTORAGE HEADER

#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "patient.h"
#include "waittimesentry.h"
#include "numpatientsentry.h"
#include "occupancyrateentry.h"
#include <QVector>
#include <QDate>
class DataStorage
{
public:
    DataStorage();

    static void removePatientFromBed(int facilityID, int patientID);
    static void assignPatientToBed(int facilityID, int patientID);
    static void addBeds(int facilityID, int numBeds, QString bedType);
    static void removePatientFromWaitingList(int areaID, int patientID);

    static void addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QDate dateAdded, QDate dateAdmittedToFacility, int currentFacility, int currentCareType); //inpatient

    static void addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QDate dateAdded); //outpatient

    static QVector<int> getAllAreas();
    static QString getAreaName(int areaID);

    static QVector<int> getAllFacilitiesInArea(int areaID);
    static int getAreaForFacility(int facilityID);
    static QVector<int> getAllFacilities();

    static QString getFacilityName(int facilityID);

    static float getFacilityX(int facilityID);
    static float getFacilityY(int facilityID);
    static float getTotalACBeds(int facilityID);
    static float getNumACBedsOccupied(int facilityID);
    static float getTotalCCCBeds(int facilityID);
    static float getNumCCCBedsOccupied(int facilityID);
    static float getTotalNumBeds(int facilityID);
    static float getTotalNumBedsOccupied(int facilityID);

    static QVector<Patient*> getPatientsAtFacility(int facilityID);

    static QString getFacilityType(int facilityID); //"Hospital" or "Nursing Home"

    static QVector<OccupancyRateEntry>getOccupancyRateEntries(QDate startDate, QDate endDate, int careType, int facilityID);
    static int getFacilityID(QString name);

    static QVector<Patient*> getWaitingListPatients(int areaID);
    static int getWaitingListSize(int areaID);
    static QVector<WaitTimesEntry> getWaitTimesEntries(QDate startDate, QDate endDate, int areaID);
    static QVector<NumPatientsEntry> getWaitingListSizeEntries(QDate startDate, QDate endDate, int areaID);

    static bool isLoginValid(QString username, QString password);
    static int getUserType(QString username);
    static int getUserFacility(QString username);

    static int requestMismatch(int currentCareType, int requiredCareType, int areaID);

    static void addUser(QString username, QString password, int userType); //for system administrators and LHIN staff
    static void addUser(QString username, QString password, int userType, int facilityID); //facility staff
    static void addFacility(QString name, float x, float y);
};

#endif // DATASTORAGE_H
