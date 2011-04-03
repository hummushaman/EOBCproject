//DATASTORAGE HEADER

#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "inpatient.h"
#include "patient.h"
#include "waittimesentry.h"
#include "numpatientsentry.h"
#include "occupancyrateentry.h"

#include <QDateTime>
#include <QVector>
#include <QSqlDatabase>

#include "database.h"

class DataStorage
{
private:
    //Database *database;

    //helper functions
    static QVector<int> convertToOneFieldIntVector(QSqlQuery aQuery);
    static void printQueryResults(QSqlQuery aQuery);

public:
    DataStorage();
    static int myFacilityID;
    static QString myFacilityIPaddress;
    static QString usertype;

    static void removePatientFromBed(int facilityID, QString HCN,int areaid, QString dateRemoved);
    static void assignPatientToBed(int facilityID, QString HCN,int areaid, QString dateAdded);;

    static void addBeds(int facilityID, int numBeds, QString bedType);
    static void removePatientFromWaitingList(int areaID, QString HCN, QString dateRemoved);

    static void addPatientToWaitingList(QString HCN,int areaID, QString dateAdded); //inpatient
    static void addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded); //outpatient

    static QVector<int> getAllAreas();
    static QString getAreaName(int areaID);

    static int getAreaID(QString areaname);

    static QVector<int> getAllFacilitiesInArea(int areaID);
    static int getAreaForFacility(int facilityID);
    static QVector<int> getAllFacilities();

    static QString getFacilityName(int facilityID);

    static float getFacilityX(int facilityID);
    static float getFacilityY(int facilityID);
    static int getTotalACBeds(int facilityID);
    static int getNumACBedsOccupied(int facilityID);
    static int getTotalCCCBeds(int facilityID);
    static int getNumCCCBedsOccupied(int facilityID);
    static int getTotalNumBeds(int facilityID);
    static int getTotalNumBedsOccupied(int facilityID);

    //what about LTC occupied? kind of a redundant function but it assumes that you have no knowledge of the database class (which is good)
    static int getTotalLTCBeds(int facilityID);


    static QVector<Inpatient*> getPatientsAtFacility(int facilityID);

    static QString getPatientFirstName(QString patientHCN);
    static QString getPatientLastName(QString patientHCN);


    static QString getFacilityType(int facilityID); //"Hospital" or "Nursing Home"

    static QVector<OccupancyRateEntry>getOccupancyRateEntries(QString startDate, QString endDate, QString careType, int facilityID);
    static int getFacilityID(QString name);

    static QVector<Patient*> getWaitingListPatients(int areaID);
    static int getWaitingListSize(int areaID);
    static QVector<WaitTimesEntry> getWaitTimesEntries(QString startDate, QString endDate, int areaID);
    static QVector<NumPatientsEntry> getWaitingListSizeEntries(QString startDate, QString endDate, int areaID);

    static bool isLoginValid(QString username, QString password);
    static QString getUserType(QString username);
    //static int getUserFacility(QString username); useless since we only store our own users

    static int requestMismatch(QString currentCareType, QString requiredCareType, int areaID);

    static void addUser(QString username, QString password, QString userType); //for system administrators and LHIN staff
    static void addUser(QString username, QString password, QString userType, int facilityID); //facility staff
    static void addFacility(QString name, float x, float y, int area, int facilityID, QString facilityType);

    static int myArea();
    static int getMyFacilityID();
    static bool isMainFacility();

    static int getCareType(QString care);
    static QString getCareType(int care);

    static void clearPatientsOnAreaWL(int area);
    static bool isInpatient(QString hcn);
    static int getCurrentFacilityForPatient(QString hcn);
    static QString getPatientDateAdmitted(QString hcn);
    static QString getPatientDateAdded(QString hcn);

};

#endif // DATASTORAGE_H

