#include "datastorage.h"

int DataStorage::myFacilityID = 0;
QString DataStorage::myFacilityIPaddress = "0.0.0.0";
QString DataStorage::usertype = "ADMIN";

int totalNumBeds = 0;
int totalACBeds = 0;
int totalCCCBeds = 0;
int occupiedBeds = 0;
int occupiedACBeds = 0;
int occupiedCCCBeds = 0;

DataStorage::DataStorage(QSqlDatabase databaseConnection)
{

    //request information from the other facilities?
    //create temporary database
    QSqlDatabase temporaryDatabase = QSqlDatabase::addDatabase("QSQLITE");
    temporaryDatabase.setDatabaseName(":memory:");

}

void DataStorage::removePatientFromBed(int facilityID, QString HCN)
{

}

 void DataStorage::assignPatientToBed(int facilityID, QString HCN)
{

}

void DataStorage::addBeds(int facilityID, int numBeds, QString bedtype)
{
       totalNumBeds += numBeds;
}

void DataStorage::removePatientFromWaitingList(int areaID, QString HCN)
{

}

 void DataStorage::addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded, int currentFacility, QString currentCareType) //inpatient
{

}

 void DataStorage::addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded) //outpatient
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

    return totalACBeds;
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

 QVector<OccupancyRateEntry> DataStorage::getOccupancyRateEntries(QString startDate, QString endDate, int careType, int facilityID)
{
    ///OccupancyRateEntry x = new OccupancyRateEntry();

    /*QVector<OccupancyRateEntry> log;
    log<<x;
    return log;*/
}

 int DataStorage::getFacilityID(QString name)
{

}

int DataStorage::getAreaID(QString areaname)
{

}
 QVector<Patient*> DataStorage::getWaitingListPatients(int areaID)
{
     QVector<Patient*> patients;
     Patient* patient1 = new Patient("12343653 xw", "Joe", "Smith");
     Patient* patient2 = new Patient("345645362 x","Rebecca", "Black");
     patients<<patient1<<patient2;
     return patients;
}

 int DataStorage::getWaitingListSize(int areaID)
{

}

 QVector<WaitTimesEntry> DataStorage::getWaitTimesEntries(QString startDate, QString endDate, int areaID)
{
    /* WaitTimesEntry x = new WaitTimesEntry();

     QVector<WaitTimesEntry> log;
     log<<x;
     return log;*/
}

 QVector<NumPatientsEntry> DataStorage::getWaitingListSizeEntries(QString startDate, QString endDate, int areaID)
{
    /*NumPatientsEntry x = new NumPatientsEntry();

     QVector<NumPatientsEntry> log;
     log<<x;
     return log;*/
}

 bool DataStorage::isLoginValid(QString username, QString password)
{
    //if((username == "JNF") && (password == "comp3004"))
     return true;
}

QString DataStorage::getUserType(QString username)
{
    return "FACILITY";
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

 QString DataStorage::getPatientFirstName(QString patientHCN)
{
    return "Bob";
}

QString DataStorage::getPatientLastName(QString patientHCN)
{
    return "Smith";
}
