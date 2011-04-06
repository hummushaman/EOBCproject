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
    static QString convertToOneString(QSqlQuery queryTemporary);
    static int convertToOneInt(QSqlQuery queryTemporary);
    static float convertToOneFloat(QSqlQuery queryTemporary);
    static bool intErrorCheck(int queryResult);
    static bool stringErrorCheck(QString queryResult);
    static bool isDefaultUser(QString username, QString password);

public:
    DataStorage();


    static int myFacilityID;
    static QString myFacilityIPaddress;
    static QString currentUserType;
    static bool isMain;

    //static void setMyFacilityID(int id);
    //static void setMyFacilityIPAddress(QString ipadress);
    //static void setCurrentUserType(QString aUserType);
    //static QString getCurrentUserType();

    static int myArea();
    static int getMyFacilityID();
    static QString getMyFacilityIPAddress();
    static bool isMainFacility();
    
    static void removePatientFromBed(int facilityID, QString HCN,QString dateRemoved);
    static void assignPatientToBed(int facilityID, QString HCN,int areaid, QString dateAdded);

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

    static int getFacilityX(int facilityID);
    static int getFacilityY(int facilityID);

    static int getTotalACBeds(int facilityID);
    static int getNumACBedsOccupied(int facilityID);

    static int getTotalCCCBeds(int facilityID);
    static int getNumCCCBedsOccupied(int facilityID);

    static int getTotalNumBeds(int facilityID);
    static int getTotalNumBedsOccupied(int facilityID);

    static int getTotalLTCBeds(int facilityID);
    static int getNumLTCBedsOccupied(int facilityID);

    static QVector<Inpatient> getPatientsAtFacility(int facilityID);

    static QString getPatientFirstName(QString patientHCN);
    static QString getPatientLastName(QString patientHCN);
    static bool isInpatient(QString hcn);
    static int getCurrentFacilityForPatient(QString hcn);
    static QString getPatientDateAdmitted(QString hcn);
    static QString getPatientDateAdded(QString hcn, int areaID);

    static QString getFacilityType(int facilityID); //"Hospital" or "Nursing Home"

    static QVector<OccupancyRateEntry>getOccupancyRateEntries(QString startDate, QString endDate, QString careType, int facilityID);
    static int getFacilityID(QString name);

    static QVector<Patient> getWaitingListPatients(int areaID);
    static int getWaitingListSize(int areaID);
    static QVector<WaitTimesEntry> getWaitTimesEntries(QString startDate, QString endDate, int areaID);
    static QVector<NumPatientsEntry> getWaitingListSizeEntries(QString startDate, QString endDate, int areaID);

    static bool isLoginValid(QString username, QString password);
    static QString getUserType(QString username);

    static void addUser(QString username, QString password, QString userType);
    static void addFacility(QString name, int x, int y, int area, int facilityID, QString facilityType);

    static int getCareType(QString care);
    static QString getCareType(int care);

    static void clearPatientsAtFacility(int facilityID);  //rename??
    static void clearPatientsOnAreaWL(int area);

    static bool facilityExists(int facilityID);

    //static void populateTemporaryDatabase();

    static bool facilityNameExists(QString aName);
    static bool facilityExistsAtCoordinates(int x, int y);
    static bool isUsernameInUse(QString aUsername, QString aPassword);
};

#endif // DATASTORAGE_H

