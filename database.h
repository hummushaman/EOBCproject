#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QVector>
#include "patient.h"
#include "waittimesentry.h"
#include "numpatientsentry.h"
#include "occupancyrateentry.h"
#include <QMessageBox>
#include<QSqlQuery>
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlField>
#include <QSettings>

using namespace std;

class Database
{
public:
    //static Database* Initialize(QSqlDatabase aDatabaseConnection); DO NOT NEED
    static Database* Initialize();

    void removePatientFromBed(int facilityID, QString HCN, QString dateRemoved);
    void assignPatientToBed(int facilityID, QString HCN);
    void addBeds(int facilityID, int numBeds, QString bedType);

    void removePatientFromWaitingList(int areaID, QString HCN, QString dateRemoved);
    void addPatientToWaitingList(QString HCN, int areaID, QString dateAdded); //inpatient
    void addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded); //outpatient

    QSqlQuery getAllAreas();
    QSqlQuery getAreaName(int areaID);

    QSqlQuery getAreaID(QString areaname);

    QSqlQuery getAllFacilitiesInArea(int areaID);
    QSqlQuery getAreaForFacility(int facilityID);
    QSqlQuery getAllFacilities();

    QSqlQuery getFacilityName(int facilityID);

    QSqlQuery getFacilityX(int facilityID);
    QSqlQuery getFacilityY(int facilityID);
    QSqlQuery getTotalACBeds(int facilityID);
    QSqlQuery getNumACBedsOccupied(int facilityID);
    QSqlQuery getTotalCCCBeds(int facilityID);
    QSqlQuery getNumCCCBedsOccupied(int facilityID);
    QSqlQuery getTotalNumBeds(int facilityID);
    QSqlQuery getTotalNumBedsOccupied(int facilityID);

    QSqlQuery getPatientsAtFacility(int facilityID);

    QSqlQuery getPatientFirstName(QString patientHCN);
    QSqlQuery getPatientLastName(QString patientHCN);

    QSqlQuery getFacilityType(int facilityID); //"Hospital" or "Nursing Home"

    QSqlQuery getOccupancyRateEntries(QString startDate, QString endDate, QString careType, int facilityID);
    QSqlQuery getFacilityID(QString name);

    QSqlQuery getWaitingListInpatients(int areaID);
    QSqlQuery getWaitingListOutpatients(int areaID);

    QSqlQuery getWaitingListSize(int areaID);
    QSqlQuery getWaitTimesEntries(QString startDate, QString endDate, int areaID);
    QSqlQuery getWaitingListSizeEntries(QString startDate, QString endDate, int areaID);

    QSqlQuery isLoginValid(QString username, QString password);
    QSqlQuery getUserType(QString username);
    QSqlQuery getUserFacility(QString username);

    void addUser(QString username, QString password, QString userType);
    void addFacility(QString name, float x, float y, int areaID, int facilityID, QString facilityType);
    QSqlQuery getCareType(int careType);
    QSqlQuery getCareTypeID(QString careType);

    void clearPatientsOnAreaWaitingList(int area);
    void clearPatientsAtFacility(int facilityID);

    QSqlQuery isInpatient(QString hcn);
    QSqlQuery getCurrentFacilityForPatient(QString hcn);
    QSqlQuery getPatientDateAdmitted(QString hcn);
    QSqlQuery getPatientDateAdded(QString hcn, int areaID);
    QSqlQuery facilityExists(int facilityID);

    QSqlQuery getTotalLTCBeds(int facilityID);
    QSqlQuery getNumLTCBedsOccupied(int facilityID);


    ~Database();
private:
    Database();
    //QSqlDatabase permanentDatabase;
    //QSqlDatabase temporaryDatabase;
    static Database* databaseClassInstance;
    //------------------------------------------------------------------------------------------------------------------
    //HELPER FUNCTIONS
    //------------------------------------------------------------------------------------------------------------------
    bool isMyFacility(int facilityID);
    int getUserTypeID(QString username, QString password, QString userType);
    QSqlQuery queryDatabase(QString aQuery, QString databaseConnection);
    void updateDatabase(QString aQuery, QString databaseConnection);
    int getID(QSqlQuery queryTemporary);
    int getFacilityTypeID(QString facilityType);
    QString getType(QSqlQuery queryTemporary);
    bool isPermanentDatabaseConnection(QString aConnection);

    void updateNumberOfACBedsOccupied(QString databaseConnection, int facilityID, int amount);
    void updateNumberOfCCCBedsOccupied(QString databaseConnection, int facilityID, int amount);
    void updateTotalNumberOfBedsOccupied(QString databaseConnection, int facilityID, int amount, bool updateLog);

    void updateNumberOfACBeds(QString databaseConnection, int facilityID, int amount);
    void updateNumberOfCCCBeds(QString databaseConnection, int facilityID, int amount);
    void updateTotalNumberOfBeds(QString databaseConnection, int facilityID, int amount, bool updateLog);
    //PRIVATE VERSIONS OF "DATASTORAGE CLASSES FUNCTIONS" TO REDUCE REDUNDANT CODE (due to the fact of two databases)
    //------------------------------------------------------------------------------------------------------------------
    void removePatientFromBed(QString databaseConnection, int facilityID, QString HCN, QString dateRemoved);
    void removePatientFromWaitingList(QString databaseConnection, int areaID, QString HCN, QString dateRemoved);
    void addPatientToWaitingList(QString databaseConnection, QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded);
    void assignPatientToBed(QString databaseConnection, int facilityID, QString HCN, int areaID, QString dateAssigned);

    void addPatientToWaitingList(QString databaseConnection, QString HCN, int areaID, QString dateAdded);
    void addBeds(QString databaseConnection, int facilityID, int numBeds, QString bedType);

    //------------------------------------------------------------------------------------------------------------------
    int myFacilityID;
};

#endif // DATABASE_H


