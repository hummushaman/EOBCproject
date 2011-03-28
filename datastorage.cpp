#include "datastorage.h"

DataStorage::DataStorage()
{
}

void DataStorage::removePatientFromBed(int facilityID, int patientID)
{


}

 void DataStorage::assignPatientToBed(int facilityID, int patientID)
{

}

void DataStorage::addBeds(int facilityID, int numBeds, QString bedtype)
{

}

void DataStorage::removePatientFromWaitingList(int areaID, int patientID)
{

}

 void DataStorage::addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QDate dateAdded, QDate dateAdmittedToFacility, int currentFacility, int currentCareType) //inpatient
{

}

 void DataStorage::addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QDate dateAdded) //outpatient
{

}

 QVector<int> DataStorage::getAllAreas()
{
    QVector<int> areas;
    areas <<1<<2<<3;
    return areas;

}

 QString DataStorage::getAreaName(int areaID)
{
    QString aString = " An Area";
    return aString;
}

 QVector<int> DataStorage::getAllFacilitiesInArea(int areaID)
{
     QVector<int> facilities;
     facilities << 1 << 2 << 3;
     return facilities;

}

 int DataStorage::getAreaForFacility(int facilityID)
{

}

 QVector<int> DataStorage::getAllFacilities()
{
     QVector<int> facilities;
     facilities << 1 << 2 << 3;
     return facilities;
}

 QString DataStorage::getFacilityName(int facilityID)
 {
    QString facilname = "a facility";
    return facilname;
 }

 float DataStorage::getFacilityX(int facilityID)
{


}

 float DataStorage::getFacilityY(int facilityID)
{

}

 float DataStorage::getTotalACBeds(int facilityID)
{

}

 float DataStorage::getNumACBedsOccupied(int facilityID)
{


}

 float DataStorage::getTotalCCCBeds(int facilityID)
{

}

 float DataStorage::getNumCCCBedsOccupied(int facilityID)
{

}

 float DataStorage::getTotalNumBeds(int facilityID)
{

}

 float DataStorage::getTotalNumBedsOccupied(int facilityID)
{

}

 QVector<Patient*> DataStorage::getPatientsAtFacility(int facilityID)
{
    QVector<Patient*> patients;
    Patient* patient1 = new Patient("1234 pw", "Joe", "Smith");
    Patient* patient2 = new Patient("3456 x","Mary", "Black");
    patients<<patient1<<patient2;
    return patients;
}

QString DataStorage::getFacilityType(int facilityID)     //0=hospital, 1=nursinghome
{
    if (facilityID == 0)
        return "Hospital";
    else return "Nursing Home";

}

 QVector<OccupancyRateEntry> DataStorage::getOccupancyRateEntries(QDate startDate, QDate endDate, int careType, int facilityID)
{
    ///OccupancyRateEntry x = new OccupancyRateEntry();

    /*QVector<OccupancyRateEntry> log;
    log<<x;
    return log;*/
}

 int DataStorage::getFacilityID(QString name)
{

}

 QVector<Patient*> DataStorage::getWaitingListPatients(int areaID)
{
     /*Patient x = new Patient();

     QVector<Patient> log;
     log<<x;

     return log;*/
}

 int DataStorage::getWaitingListSize(int areaID)
{

}

 QVector<WaitTimesEntry> DataStorage::getWaitTimesEntries(QDate startDate, QDate endDate, int areaID)
{
    /* WaitTimesEntry x = new WaitTimesEntry();

     QVector<WaitTimesEntry> log;
     log<<x;
     return log;*/
}

 QVector<NumPatientsEntry> DataStorage::getWaitingListSizeEntries(QDate startDate, QDate endDate, int areaID)
{
    /*NumPatientsEntry x = new NumPatientsEntry();

     QVector<NumPatientsEntry> log;
     log<<x;
     return log;*/
}

 bool DataStorage::isLoginValid(QString username, QString password)
{

}

 int DataStorage::getUserType(QString username)
{

}

 int DataStorage::getUserFacility(QString username)
{

}

 int DataStorage::requestMismatch(int currentCareType, int requiredCareType, int areaID)
{

}

 void DataStorage::addUser(QString username, QString password, int userType) //for system administrators and LHIN staff
{

}

 void DataStorage::addUser(QString  username, QString  password, int userType, int facilityID) //facility staff
{

}

 void DataStorage::addFacility(QString name, float x, float y)
{

}
