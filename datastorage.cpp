#include "datastorage.h"

int DataStorage::myFacilityID = 0;
QString DataStorage::myFacilityIPaddress = "0.0.0.0";
QString DataStorage::currentUserType = "ADMIN";

void DataStorage::removePatientFromBed(int facilityID, QString HCN, QString dateRemoved) //i don't need area...
{
<<<<<<< HEAD
=======
    qDebug() << "Removing a patient from a bed";
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    Database::Initialize()->removePatientFromBed(facilityID, HCN, dateRemoved);
}

void DataStorage::assignPatientToBed(int facilityID, QString HCN,int areaid, QString dateAdded)
{
    //Database::Initialize()->assignPatientToBed(); MORE COMPLEX THAN I ORIGINALLY THOUGHT
}

<<<<<<< HEAD

void DataStorage::addBeds(int facilityID, int numBeds, QString bedType)
{
=======
void DataStorage::addBeds(int facilityID, int numBeds, QString bedType)
{
    qDebug() << "Adding beds";
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    Database::Initialize()->addBeds(facilityID, numBeds, bedType);
}

void DataStorage::removePatientFromWaitingList(int areaID, QString HCN, QString dateRemoved)
{
<<<<<<< HEAD
    Database::Initialize()->removePatientFromWaitingList(areaID, HCN, dateRemoved);
}


void DataStorage::addPatientToWaitingList(QString HCN,int areaID, QString dateAdded)  //inpatient
{
=======
    qDebug() << "Removing a patient from waiting list";
    Database::Initialize()->removePatientFromWaitingList(areaID, HCN, dateRemoved);
}

void DataStorage::addPatientToWaitingList(QString HCN,int areaID, QString dateAdded)  //inpatient
{
    qDebug() << "Adding an inpatient to a waiting list";
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    Database::Initialize()->addPatientToWaitingList(HCN, areaID, dateAdded);
}

void DataStorage::addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded) //outpatient
{
<<<<<<< HEAD
=======
    qDebug() << "Adding an outpatient to a waiting list";
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    Database::Initialize()->addPatientToWaitingList(HCN, firstName, lastName, areaID, dateAdded);
}

QVector<int> DataStorage::getAllAreas()
{
    QVector<int> areaIDs = convertToOneFieldIntVector(Database::Initialize()->getAllAreas());
    return areaIDs;
}

QString DataStorage::getAreaName(int areaID)
{
<<<<<<< HEAD
    qDebug() << "Getting area name for " << areaID;
=======
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
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
<<<<<<< HEAD
=======
    qDebug() << "Getting all of the facilities";
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    QVector<int> facilityIDs = convertToOneFieldIntVector(Database::Initialize()->getAllFacilities());
    return facilityIDs;
}

QString DataStorage::getFacilityName(int facilityID)
{
<<<<<<< HEAD
=======
    qDebug() << "Getting a facility's names";
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    QSqlQuery facilityNameQuery = Database::Initialize()->getFacilityName(facilityID);
    QString facilityName = convertToOneString(facilityNameQuery);
    return facilityName;
}

float DataStorage::getFacilityX(int facilityID)
{
<<<<<<< HEAD
=======
    qDebug() << "Getting a facility's X";
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    QSqlQuery facilityXQuery = Database::Initialize()->getFacilityX(facilityID);
    float facilityX = convertToOneFloat(facilityXQuery);
    return facilityX;
}

float DataStorage::getFacilityY(int facilityID)
{
<<<<<<< HEAD
=======
    qDebug() << "Getting a facility's Y";
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    QSqlQuery facilityYQuery = Database::Initialize()->getFacilityY(facilityID);
    float facilityY = convertToOneFloat(facilityYQuery);
    return facilityY;
}

int DataStorage::getTotalACBeds(int facilityID)
{
<<<<<<< HEAD
=======
    qDebug() << "Getting total number of AC beds";
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    QSqlQuery totalACBedsQuery = Database::Initialize()->getTotalACBeds(facilityID);
    int totalACBeds = convertToOneInt(totalACBedsQuery);
    return totalACBeds;
}

int DataStorage::getNumACBedsOccupied(int facilityID)
{
<<<<<<< HEAD
=======
    qDebug() << "Getting number of AC beds occupied";
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    QSqlQuery numACBedsOccupiedQuery = Database::Initialize()->getNumACBedsOccupied(facilityID);
    int numACBedsOccupied = convertToOneInt(numACBedsOccupiedQuery);
    return numACBedsOccupied;
}

int DataStorage::getTotalCCCBeds(int facilityID)
{
<<<<<<< HEAD
=======
    qDebug() << "Getting total number of CCC beds";
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    QSqlQuery totalCCCBedsQuery = Database::Initialize()->getTotalCCCBeds(facilityID);
    int totalCCCBeds = convertToOneInt(totalCCCBedsQuery);
    return totalCCCBeds;
}

int DataStorage::getNumCCCBedsOccupied(int facilityID)
{
<<<<<<< HEAD
=======
    qDebug() << "Getting number of CCC beds occupied";
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    QSqlQuery numCCCBedsOccupiedQuery = Database::Initialize()->getNumCCCBedsOccupied(facilityID);
    int numCCCBedsOccupied = convertToOneInt(numCCCBedsOccupiedQuery);
    return numCCCBedsOccupied;
}

int DataStorage::getTotalNumBeds(int facilityID)
{
<<<<<<< HEAD
=======
    qDebug() << "Getting total number of beds";
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    QSqlQuery totalNumBedsQuery = Database::Initialize()->getTotalNumBeds(facilityID);
    int totalNumBeds = convertToOneInt(totalNumBedsQuery);
    return totalNumBeds;
}

int DataStorage::getTotalNumBedsOccupied(int facilityID)
{
<<<<<<< HEAD
=======
    qDebug() << "Getting number of beds occupied ";
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
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


<<<<<<< HEAD
QVector<Inpatient*> DataStorage::getPatientsAtFacility(int facilityID) //kind of complicated query
{

=======
QVector<Inpatient> DataStorage::getPatientsAtFacility(int facilityID)
{

    QSqlQuery patientsAtFacilityQuery = Database::Initialize()->getPatientsAtFacility(facilityID);

    QVector<Inpatient> inpatients;

    QString hcn;
    QString firstName;
    QString lastName;
    QString requiredCare;
    QString currentCare;
    QString dateAdmitted;
    int currentFacility;

    while(patientsAtFacilityQuery.next())
    {
        hcn = patientsAtFacilityQuery.value(0).toString();
        firstName = patientsAtFacilityQuery.value(1).toString();
        lastName = patientsAtFacilityQuery.value(2).toString();
        requiredCare = patientsAtFacilityQuery.value(3).toString();
        currentCare = patientsAtFacilityQuery.value(4).toString();
        dateAdmitted = patientsAtFacilityQuery.value(5).toString();
        currentFacility = patientsAtFacilityQuery.value(6).toInt();
        Inpatient anInpatient(hcn, firstName, lastName, requiredCare, currentCare, dateAdmitted, currentFacility);
        inpatients.append(anInpatient);
    }
    qDebug() << "Size of inpatients: " << inpatients.size();
    return inpatients;
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
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

<<<<<<< HEAD
QVector<OccupancyRateEntry >DataStorage::getOccupancyRateEntries(QString startDate, QString endDate, QString careType, int facilityID)
{
    //SELECT dateofchange, caretype, occupancyrate FROM
    //QSqlQuery



=======
QVector<OccupancyRateEntry>DataStorage::getOccupancyRateEntries(QString startDate, QString endDate, QString careType, int facilityID)
{
    QSqlQuery occupancyRateEntryQuery = Database::Initialize()->getOccupancyRateEntries(startDate, endDate, careType, facilityID);
    QVector<OccupancyRateEntry> occupancyRateEntries;
    QString dateChangedField;
    QString careTypeField;
    float occupancyRateField;

    while(occupancyRateEntryQuery.next())
    {
        dateChangedField = occupancyRateEntryQuery.value(0).toString();
        careTypeField = occupancyRateEntryQuery.value(1).toString();
        occupancyRateField = occupancyRateEntryQuery.value(2).toFloat();

        OccupancyRateEntry entry(dateChangedField, careTypeField, occupancyRateField);
        occupancyRateEntries.append(entry);
    }
    qDebug() << "Occupancy rate entry size: " << occupancyRateEntries.size();
    return occupancyRateEntries;
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
}

int DataStorage::getFacilityID(QString name)
{
<<<<<<< HEAD

}

QVector<Patient*> DataStorage::getWaitingListPatients(int areaID)
{

=======
    qDebug() << "Getting the facility ID";
    QSqlQuery facilityIDQuery = Database::Initialize()->getFacilityID(name);
    int facilityID = convertToOneInt(facilityIDQuery);
    return facilityID;
}

QVector<Patient> DataStorage::getWaitingListPatients(int areaID)
{

    QSqlQuery outpatientQuery = Database::Initialize()->getWaitingListOutpatients(areaID);
    QVector<Patient> patients;
    QString healthCareNumber;
    QString firstName;
    QString lastName;
    QString requiredCare;

    while (outpatientQuery.next())
    {
        healthCareNumber = outpatientQuery.value(0).toString() ;
        firstName = outpatientQuery.value(1).toString();
        lastName = outpatientQuery.value(2).toString();
        requiredCare = outpatientQuery.value(3).toString();
        qDebug() << "Outpatient " << healthCareNumber << firstName << lastName << requiredCare;
        Patient anOutpatient(healthCareNumber, firstName, lastName, requiredCare);
        patients.append(anOutpatient);
    }

    QSqlQuery inpatientQuery = Database::Initialize()->getWaitingListInpatients(areaID);
    QString currentCareType;
    QString dateAdmitted;
    int currentFacility;
    while (inpatientQuery.next())
    {
        healthCareNumber = inpatientQuery.value(0).toString() ;
        firstName = inpatientQuery.value(1).toString();
        lastName = inpatientQuery.value(2).toString();
        requiredCare = inpatientQuery.value(3).toString();
        currentCareType = inpatientQuery.value(4).toString();
        dateAdmitted = inpatientQuery.value(5).toString();
        currentFacility = inpatientQuery.value(6).toInt();
        Inpatient anInpatient(healthCareNumber, firstName, lastName, requiredCare, currentCareType, dateAdmitted, currentFacility);
        patients.append(anInpatient);
    }
    qDebug() << "Waiting list patient size: "<< patients.size();
    return patients;
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
}

int DataStorage::getWaitingListSize(int areaID)
{

<<<<<<< HEAD
=======
    QSqlQuery waitingListSizeQuery = Database::Initialize()->getWaitingListSize(areaID);
    return convertToOneInt(waitingListSizeQuery);
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
}

QVector<WaitTimesEntry> DataStorage::getWaitTimesEntries(QString startDate, QString endDate, int areaID)
{

}

QVector<NumPatientsEntry> DataStorage::getWaitingListSizeEntries(QString startDate, QString endDate, int areaID)
{

}

bool DataStorage::isLoginValid(QString username, QString password)
{
<<<<<<< HEAD
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
=======

    return true;
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
}

QString DataStorage::getUserType(QString username)
{
<<<<<<< HEAD

}

//static int getUserFacility(QString username); useless since we only store our own users

=======
    qDebug() << "Getting the user's type";
    QSqlQuery userTypeQuery = Database::Initialize()->getUserType(username);
    return convertToOneString(userTypeQuery);
}

>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
int DataStorage::requestMismatch(QString currentCareType, QString requiredCareType, int areaID)
{

}

<<<<<<< HEAD
void DataStorage::addUser(QString username, QString password, QString userType) //for system administrators and LHIN staff
{

=======
void DataStorage::addUser(QString username, QString password, QString userType)
{
    qDebug() << "Trying to add a user";
    Database::Initialize()->addUser(username, password, userType);
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
}

void DataStorage::addFacility(QString name, float x, float y, int area, int facilityID, QString facilityType)
{
<<<<<<< HEAD

=======
    qDebug() << "Adding a new facility" << "Name: " << name << "x: " << x << " y" << y << "area " << area << " facilityid" <<facilityID << " facility type " << facilityType;
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    Database::Initialize()->addFacility(name, x, y, area, facilityID, facilityType);
}

int DataStorage::myArea()
{

<<<<<<< HEAD
=======
    return getAreaForFacility(DataStorage::myFacilityID);
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
}

int DataStorage::getMyFacilityID()
{
<<<<<<< HEAD

}

bool DataStorage::isMainFacility()
=======
    return DataStorage::myFacilityID;
}

bool DataStorage::isMainFacility() //need to add this to the configure file
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
{

}

int DataStorage::getCareType(QString care)
{
<<<<<<< HEAD

=======
    QSqlQuery careTypeQuery = Database::Initialize()->getCareTypeID(care);
    return convertToOneInt(careTypeQuery);
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
}

QString DataStorage::getCareType(int care)
{
<<<<<<< HEAD

=======
    QSqlQuery careTypeQuery = Database::Initialize()->getCareType(care);
    return convertToOneString(careTypeQuery);
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
}

void DataStorage::clearPatientsOnAreaWL(int area)
{

}

bool DataStorage::isInpatient(QString hcn)
{
<<<<<<< HEAD

=======
    QSqlQuery inpatientQuery = Database::Initialize()->isInpatient(hcn);
    QString inpatientHCN = convertToOneString(inpatientQuery);
    if (inpatientHCN.isEmpty())
    {
        return false;
    }
    return true;
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
}

int DataStorage::getCurrentFacilityForPatient(QString hcn)
{
<<<<<<< HEAD

=======
    QSqlQuery currentFacilityQuery = Database::Initialize()->getCurrentFacilityForPatient(hcn);
    return convertToOneInt(currentFacilityQuery);
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
}

QString DataStorage::getPatientDateAdmitted(QString hcn)
{
<<<<<<< HEAD

}

QString DataStorage::getPatientDateAdded(QString hcn)
{

=======
    QSqlQuery dateAdmittedQuery = Database::Initialize()->getPatientDateAdmitted(hcn);
    return convertToOneString(dateAdmittedQuery);
}

QString DataStorage::getPatientDateAdded(QString hcn, int areaID)
{
    QSqlQuery dateAddedQuery = Database::Initialize()->getPatientDateAdded(hcn, areaID);
    return convertToOneString(dateAddedQuery);
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
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
<<<<<<< HEAD
        qDebug() << "One string: " << string;
    }
=======

    }
    qDebug() << "One string: " << string;
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    return string;
}


int DataStorage::convertToOneInt(QSqlQuery queryTemporary)
{
<<<<<<< HEAD
    int integer;
    while(queryTemporary.next())
    {

        integer = queryTemporary.value(0).toInt();
        qDebug() << "One int: " << integer;
    }
=======
    bool okay;
    int integer = -1;
    while(queryTemporary.next())
    {
        integer = queryTemporary.value(0).toInt(&okay);

        if (!okay)
        {
            integer = -1;
        }

    }
    qDebug() << "One int: " << integer;
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    return integer;
}

float DataStorage::convertToOneFloat(QSqlQuery queryTemporary)
{
<<<<<<< HEAD
    float aFloat;
    while(queryTemporary.next())
    {
        aFloat = queryTemporary.value(0).toFloat();
        qDebug() << "One float: " << aFloat;
    }
=======
    bool okay;
    float aFloat = -1.0;
    while(queryTemporary.next())
    {
        aFloat = queryTemporary.value(0).toFloat();
        if (!okay)
        {
            aFloat = -1.0;
        }

    }
    qDebug() << "One float: " << aFloat;
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
    return aFloat;
}

void DataStorage::clearPatientsAtFacility(int facilNum)
{

}

bool DataStorage::facilityExists(int facilityID)
{
<<<<<<< HEAD

=======
    QSqlQuery facilityExistsQuery = Database::Initialize()->facilityExists(facilityID);
    int facility = convertToOneInt(facilityExistsQuery);
    if (facility == -1)
    {
        return false;
    }
    return true;
>>>>>>> 67e3fb678d2aa50a453f2b852e15340f1c961e26
}
