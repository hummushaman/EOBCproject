#include "datastorage.h"

DataStorage::DataStorage()
{
}

static void DataStorage::removePatientFromBed(int facilityID, int patientID)
{

}

static void DataStorage::assignPatientToBed(int facilityID, int patientID)
{

}

static void DataStorage::addBeds(int facilityID, int numBeds, int bedType)
{

}

static void DataStorage::removePatientFromWaitingList(int areaID, int patientID)
{

}

static void DataStorage::addPatientToWaitingList(QString firstName, QString lastName, int areaID, QDate dateAdded, QDate dateAdmittedToFacility, int currentFacility, int currentCareType) //inpatient
{

}

static void DataStorage::addPatientToWaitingList(QString firstName, QString lastName, int areaID, QDate dateAdded) //outpatient
{

}

static QVector<int> DataStorage::getAllAreas()
{

}

static QString DataStorage::getAreaName(int areaID)
{

}

static QVector<int> DataStorage::getAllFacilitiesInArea(int areaID)
{

}

static int DataStorage::getAreaForFacility(int facilityID)
{

}

static QVector<int> DataStorage::getAllFacilities()
{

}

static float DataStorage::getFacilityX(int facilityID)
{


}

static float DataStorage::getFacilityY(int facilityID)
{

}

static float DataStorage::getTotalACBeds(int facilityID)
{

}

static float DataStorage::getNumACBedsOccupied(int facilityID)
{


}

static float DataStorage::getTotalCCCBeds(int facilityID)
{

}

static float DataStorage::getNumCCCBedsOccupied(int facilityID)
{

}

static float DataStorage::getTotalNumBeds(int facilityID)
{

}

static float DataStorage::getTotalNumBedsOccupied(int facilityID)
{

}

static QVector<Patient> DataStorage::getPatientsAtFacility(int facilityID)
{

}

static int DataStorage::getFacilityType(int facilityID)     //0=hospital, 1=nursinghome
{

}

static QVector<OccupancyRateEntry> DataStorage::getOccupancyRateEntries(QDate startDate, QDate endDate, int careType, int facilityID)
{

}

static int DataStorage::getFacilityID(QString name)
{

}

static QVector<Patient> DataStorage::getWaitingListPatients(int areaID)
{

}

static int DataStorage::getWaitingListSize(int areaID)
{

}

static QVector<WaitTimesEntry> DataStorage::getWaitTimesEntries(QDate startDate, QDate endDate, int areaID)
{

}

static QVector<NumPatientsEntry> DataStorage::getWaitingListSizeEntries(QDate startDate, QDate endDate, int areaID)
{

}

static bool DataStorage::isLoginValid(QString username, QString password)
{

}

static int DataStorage::getUserType(QString username)
{

}

static int DataStorage::getUserFacility(QString username)
{

}

static int DataStorage::requestMismatch(int currentCareType, int requiredCareType, int areaID)
{

}

static void DataStorage::addUser(QString username, QString password, int userType) //for system administrators and LHIN staff
{

}

static void DataStorage::addUser(QString  username, QString  password, int userType, int facilityID) //facility staff
{

}

static void DataStorage::addFacility(QString name, float x, float y)
{

}
