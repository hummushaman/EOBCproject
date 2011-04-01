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
    void removePatientFromWaitingList(int areaID, QString HCN);

    void addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded, int currentFacility, int currentCareType); //inpatient

    void addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded); //outpatient

    QVector<int> getAllAreas();
    QString getAreaName(int areaID);

    int getAreaID(QString areaname);

    QVector<int> getAllFacilitiesInArea(int areaID);
    int getAreaForFacility(int facilityID);
    QVector<int> getAllFacilities();

    QString getFacilityName(int facilityID);

    float getFacilityX(int facilityID);
    float getFacilityY(int facilityID);
    float getTotalACBeds(int facilityID);
    float getNumACBedsOccupied(int facilityID);
    float getTotalCCCBeds(int facilityID);
    float getNumCCCBedsOccupied(int facilityID);
    float getTotalNumBeds(int facilityID);
    float getTotalNumBedsOccupied(int facilityID);

    QVector<Patient*> getPatientsAtFacility(int facilityID);

    QString getPatientFirstName(QString patientHCN);
    QString getPatientLastName(QString patientHCN);

    QString getFacilityType(int facilityID); //"Hospital" or "Nursing Home"

    QVector<OccupancyRateEntry>getOccupancyRateEntries(QString startDate, QString endDate, int careType, int facilityID);
    int getFacilityID(QString name);

    QVector<Patient*> getWaitingListPatients(int areaID);
    int getWaitingListSize(int areaID);
    QVector<WaitTimesEntry> getWaitTimesEntries(QString startDate, QString endDate, int areaID);
    QVector<NumPatientsEntry> getWaitingListSizeEntries(QString startDate, QString endDate, int areaID);

    bool isLoginValid(QString username, QString password);
    QString getUserType(QString username);
    int getUserFacility(QString username);

    int requestMismatch(int currentCareType, int requiredCareType, int areaID);

    void addUser(QString username, QString password, int userType); //for system administrators and LHIN staff
    void addUser(QString username, QString password, int userType, int facilityID); //facility staff
    void addFacility(QString name, float x, float y);

    ~Database();
private:
   Database();
   Database(QSqlDatabase aDatabaseConnection);
   //QSqlDatabase permanentDatabase;
   //QSqlDatabase temporaryDatabase;
   static Database* databaseClassInstance;
   //------------------------------------------------------------------------------------------------------------------
   //HELPER FUNCTIONS
   //------------------------------------------------------------------------------------------------------------------
   bool isMyFacility(int facilityID);
   QString getOneRecord(QString aQuery);
   //PRIVATE VERSIONS OF "DATASTORAGE CLASSES FUNCTIONS" TO REDUCE REDUNDANT CODE (due to the fact of two databases)
   //------------------------------------------------------------------------------------------------------------------
   void removePatientFromBed(QString databaseConnection, int facilityID, QString HCN, QString dateRemoved);
   //------------------------------------------------------------------------------------------------------------------
   int myFacilityID;


};

#endif // DATABASE_H



