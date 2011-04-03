#include "datastorage.h"

int DataStorage::myFacilityID = 0;
QString DataStorage::myFacilityIPaddress = "0.0.0.0";
QString DataStorage::currentUserType = "ADMIN";

void DataStorage::removePatientFromBed(int facilityID, QString HCN, QString dateRemoved) //i don't need area...
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
    qDebug() << "Getting area name for " << areaID;
    QSqlQuery areaNameQuery = Database::Initialize()->getAreaName(areaID);
    QString areaName = convertToOneString(areaNameQuery);
    return areaName;
}

int DataStorage::getAreaID(QString areaname)
{
    QSqlQuery areaIDQuery = Database::Initialize()->getAreaID(areaname);
    int areaID = convertToOneInt(areaIDQuery);
    return areaID;
}

QVector<int> DataStorage::getAllFacilitiesInArea(int areaID)
{
    QVector<int> facilityIDs = convertToOneFieldIntVector(Database::Initialize()->getAllFacilitiesInArea(areaID));
    return facilityIDs;
}

int DataStorage::getAreaForFacility(int facilityID)
{
    QSqlQuery areaIDQuery = Database::Initialize()->getAreaForFacility(facilityID);
    int areaID = convertToOneInt(areaIDQuery);
    return areaID;
}

QVector<int> DataStorage::getAllFacilities()
{
    QVector<int> facilityIDs = convertToOneFieldIntVector(Database::Initialize()->getAllFacilities());
    return facilityIDs;
}

QString DataStorage::getFacilityName(int facilityID)
{
    QSqlQuery facilityNameQuery = Database::Initialize()->getFacilityName(facilityID);
    QString facilityName = convertToOneString(facilityNameQuery);
    return facilityName;
}

float DataStorage::getFacilityX(int facilityID)
{
    QSqlQuery facilityXQuery = Database::Initialize()->getFacilityX(facilityID);
    float facilityX = convertToOneFloat(facilityXQuery);
    return facilityX;
}

float DataStorage::getFacilityY(int facilityID)
{
    QSqlQuery facilityYQuery = Database::Initialize()->getFacilityY(facilityID);
    float facilityY = convertToOneFloat(facilityYQuery);
    return facilityY;
}

int DataStorage::getTotalACBeds(int facilityID)
{
    QSqlQuery totalACBedsQuery = Database::Initialize()->getTotalACBeds(facilityID);
    int totalACBeds = convertToOneInt(totalACBedsQuery);
    return totalACBeds;
}

int DataStorage::getNumACBedsOccupied(int facilityID)
{
    QSqlQuery numACBedsOccupiedQuery = Database::Initialize()->getNumACBedsOccupied(facilityID);
    int numACBedsOccupied = convertToOneInt(numACBedsOccupiedQuery);
    return numACBedsOccupied;
}

int DataStorage::getTotalCCCBeds(int facilityID)
{
    QSqlQuery totalCCCBedsQuery = Database::Initialize()->getTotalCCCBeds(facilityID);
    int totalCCCBeds = convertToOneInt(totalCCCBedsQuery);
    return totalCCCBeds;
}

int DataStorage::getNumCCCBedsOccupied(int facilityID)
{
    QSqlQuery numCCCBedsOccupiedQuery = Database::Initialize()->getNumCCCBedsOccupied(facilityID);
    int numCCCBedsOccupied = convertToOneInt(numCCCBedsOccupiedQuery);
    return numCCCBedsOccupied;
}

int DataStorage::getTotalNumBeds(int facilityID)
{
    QSqlQuery totalNumBedsQuery = Database::Initialize()->getTotalNumBeds(facilityID);
    int totalNumBeds = convertToOneInt(totalNumBedsQuery);
    return totalNumBeds;
}

int DataStorage::getTotalNumBedsOccupied(int facilityID)
{
    QSqlQuery numTotalBedsOccupiedQuery = Database::Initialize()->getTotalNumBedsOccupied(facilityID);
    int numTotalBedsOccupied = convertToOneInt(numTotalBedsOccupiedQuery);
    return numTotalBedsOccupied;
}


int DataStorage::getTotalLTCBeds(int facilityID)
{

}

int DataStorage::getNumLTCBedsOccupied(int facilityID)
{

}


QVector<Inpatient*> DataStorage::getPatientsAtFacility(int facilityID) //kind of complicated query
{

}

QString DataStorage::getPatientFirstName(QString patientHCN)
{
    QSqlQuery patientFirstNameQuery = Database::Initialize()->getPatientFirstName(patientHCN);
    QString patientFirstName = convertToOneString(patientFirstNameQuery);
    return patientFirstName;
}

QString DataStorage::getPatientLastName(QString patientHCN)
{
    QSqlQuery patientLastNameQuery = Database::Initialize()->getPatientLastName(patientHCN);
    QString patientLastName = convertToOneString(patientLastNameQuery);
    return patientLastName;
}


QString DataStorage::getFacilityType(int facilityID) //"Hospital" or "Nursing Home"
{
    QSqlQuery facilityTypeQuery = Database::Initialize()->getFacilityType(facilityID);
    QString facilityType = convertToOneString(facilityTypeQuery);
    return facilityType;
}

QVector<OccupancyRateEntry >DataStorage::getOccupancyRateEntries(QString startDate, QString endDate, QString careType, int facilityID)
{
    //SELECT dateofchange, caretype, occupancyrate FROM
    //QSqlQuery



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
    QSettings settings("JNFconfig");
    settings.beginGroup("default_user");
    QString default_username = settings.value("username").toString();
    QString default_password = settings.value("password").toString();
    QString default_usertype = settings.value("userType").toString();


    //qDebug() << username;
    //qDebug() << password;

    //qDebug() << default_username;
    //qDebug() << default_password;
    //qDebug() << default_usertype;

    if((username == default_username) && (password == default_password))
    {
        DataStorage::currentUserType = default_usertype;
        return true;
    }
    else
        //return false;
        return true; //just for testing :)
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

void DataStorage::addFacility(QString name, float x, float y, int area, int facilityID, QString facilityType)
{

    Database::Initialize()->addFacility(name, x, y, area, facilityID, facilityType);
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
    QVector<int> intVector;

    while (aQuery.next())
    {
        int integer = aQuery.value(0).toInt();
        qDebug() << "Integer (vector): " << integer;
        intVector.append(integer);
    }

    qDebug() << "Size of integer vector: " << intVector.size();
    return intVector;
}

QString DataStorage::convertToOneString(QSqlQuery queryTemporary)
{
    QString string;
    qDebug() << "Converting one field to a string: ";
    while(queryTemporary.next())
    {

        string = queryTemporary.value(0).toString();
        qDebug() << "One string: " << string;
    }
    return string;
}


int DataStorage::convertToOneInt(QSqlQuery queryTemporary)
{
    int integer;
    while(queryTemporary.next())
    {

        integer = queryTemporary.value(0).toInt();
        qDebug() << "One int: " << integer;
    }
    return integer;
}

float DataStorage::convertToOneFloat(QSqlQuery queryTemporary)
{
    float aFloat;
    while(queryTemporary.next())
    {
        aFloat = queryTemporary.value(0).toFloat();
        qDebug() << "One float: " << aFloat;
    }
    return aFloat;
}

void DataStorage::clearPatientsAtFacility(int facilNum)
{

}

bool DataStorage::facilityExists(int facilityID)
{

}
