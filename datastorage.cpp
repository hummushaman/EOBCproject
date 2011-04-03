#include "datastorage.h"

int DataStorage::myFacilityID = 0;
QString DataStorage::myFacilityIPaddress = "0.0.0.0";
QString DataStorage::usertype = "ADMIN";

void DataStorage::removePatientFromBed(int facilityID, QString HCN,int areaid, QString dateRemoved) //i don't need area...
{
    Database::Initialize()->removePatientFromBed(facilityID, HCN, dateRemoved);
}

void DataStorage::assignPatientToBed(int facilityID, QString HCN,int areaid, QString dateAdded)
{
    //Database::Initialize()->assignPatientToBed(); MORE COMPLEX THAN I ORIGINALLY THOUGHT
}


void DataStorage::addBeds(int facilityID, int numBeds, QString bedType)
{
    Database::Initialize()->addBeds(facilityID, numBeds, bedType);
}

void DataStorage::removePatientFromWaitingList(int areaID, QString HCN, QString dateRemoved)
{
    Database::Initialize()->removePatientFromWaitingList(areaID, HCN, dateRemoved);
}


void DataStorage::addPatientToWaitingList(QString HCN,int areaID, QString dateAdded)  //inpatient
{
    Database::Initialize()->addPatientToWaitingList(HCN, areaID, dateAdded);
}

void DataStorage::addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded) //outpatient
{
    Database::Initialize()->addPatientToWaitingList(HCN, firstName, lastName, areaID, dateAdded);
}

QVector<int> DataStorage::getAllAreas()
{
    QVector<int> areaIDs = convertToOneFieldIntVector(Database::Initialize()->getAllAreas());
    return areaIDs;
}

QString DataStorage::getAreaName(int areaID)
{

}

int DataStorage::getAreaID(QString areaname)
{

}

QVector<int> DataStorage::getAllFacilitiesInArea(int areaID)
{

}

int DataStorage::getAreaForFacility(int facilityID)
{

}

QVector<int> DataStorage::getAllFacilities()
{

}

QString DataStorage::getFacilityName(int facilityID)
{

}

float DataStorage::getFacilityX(int facilityID)
{

}

float DataStorage::getFacilityY(int facilityID)
{

}

int DataStorage::getTotalACBeds(int facilityID)
{

}

int DataStorage::getNumACBedsOccupied(int facilityID)
{

}

int DataStorage::getTotalCCCBeds(int facilityID)
{

}

int DataStorage::getNumCCCBedsOccupied(int facilityID)
{

}

int DataStorage::getTotalNumBeds(int facilityID)
{

}

int DataStorage::getTotalNumBedsOccupied(int facilityID)
{

}

//what about LTC occupied? kind of a redundant function but it assumes that you have no knowledge of the database class (which is good)
int DataStorage::getTotalLTCBeds(int facilityID)
{

}


QVector<Inpatient*> DataStorage::getPatientsAtFacility(int facilityID)
{

}

QString DataStorage::getPatientFirstName(QString patientHCN)
{

}

QString DataStorage::getPatientLastName(QString patientHCN)
{

}


QString DataStorage::getFacilityType(int facilityID) //"Hospital" or "Nursing Home"
{

}

QVector<OccupancyRateEntry >DataStorage::getOccupancyRateEntries(QString startDate, QString endDate, QString careType, int facilityID)
{

}

int DataStorage::getFacilityID(QString name)
{

}

QVector<Patient*> DataStorage::getWaitingListPatients(int areaID)
{

}

int DataStorage::getWaitingListSize(int areaID)
{

}

QVector<WaitTimesEntry> DataStorage::getWaitTimesEntries(QString startDate, QString endDate, int areaID)
{

}

QVector<NumPatientsEntry> DataStorage::getWaitingListSizeEntries(QString startDate, QString endDate, int areaID)
{

}

bool DataStorage::isLoginValid(QString username, QString password)
{

}

QString DataStorage::getUserType(QString username)
{

}

//static int getUserFacility(QString username); useless since we only store our own users

int DataStorage::requestMismatch(QString currentCareType, QString requiredCareType, int areaID)
{

}

void DataStorage::addUser(QString username, QString password, QString userType) //for system administrators and LHIN staff
{

}

void DataStorage::addUser(QString username, QString password, QString userType, int facilityID) //facility staff
{

}

void DataStorage::addFacility(QString name, float x, float y, int area, int facilityID, QString facilityType)
{

}

int DataStorage::myArea()
{

}

int DataStorage::getMyFacilityID()
{

}

bool DataStorage::isMainFacility()
{

}

int DataStorage::getCareType(QString care)
{

}

QString DataStorage::getCareType(int care)
{

}

void DataStorage::clearPatientsOnAreaWL(int area)
{

}

bool DataStorage::isInpatient(QString hcn)
{

}

int DataStorage::getCurrentFacilityForPatient(QString hcn)
{

}

QString DataStorage::getPatientDateAdmitted(QString hcn)
{

}

QString DataStorage::getPatientDateAdded(QString hcn)
{

}

QVector<int> DataStorage::convertToOneFieldIntVector(QSqlQuery aQuery)
{
    printQueryResults(aQuery);
    QVector<int> intVector;
    while (aQuery.next())
    {
        intVector.append(aQuery.value(0).toInt());
    }
    return intVector;
}

void DataStorage::printQueryResults(QSqlQuery aQuery)
{
    qDebug() << "Query results: ";
    QString row;
    int numberOfColumns = aQuery.record().count();
    while (aQuery.next())
    {
        row = "";
        for (int columnIndex = 0; columnIndex < numberOfColumns; columnIndex++)
        {
            row += aQuery.value(columnIndex).toString() + " ";
        }
        qDebug() << row;
    }
}
