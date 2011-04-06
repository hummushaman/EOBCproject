/*
 This class is a wrapper for the database class. It does not rely on the
 underlying database in order to get the required information for
 the other subsystems.
 */

#include "datastorage.h"

int DataStorage::myFacilityID;
QString DataStorage::myFacilityIPaddress = "0.0.0.0";
QString DataStorage::currentUserType = "ADMIN";
bool DataStorage::isMain = true;

//call to the database to remove a patient from a bed [R: 2.7, 2.7.1]
void DataStorage::removePatientFromBed(int facilityID, QString HCN, QString dateRemoved)
{
    qDebug() << "Removing a patient from a bed";
    Database::Initialize()->removePatientFromBed(facilityID, HCN, dateRemoved);
}

//call to the database to assign a patient to a bed in a nursing home [R: 2.7, 2.7.1]
void DataStorage::assignPatientToBed(int facilityID, QString HCN,int areaid, QString dateAdded)
{
    qDebug() << "Assign a patient to a bed";
    Database::Initialize()->assignPatientToBed(facilityID, HCN, areaid, dateAdded);
}

//add beds of a certain care type to a facility  [R: 2.4, 2.4.1]
void DataStorage::addBeds(int facilityID, int numBeds, QString bedType)
{
    qDebug() << "Adding beds";
    Database::Initialize()->addBeds(facilityID, numBeds, bedType);
}
//removing a patient (inpatient or outpatient) from a waiting list [R: 2.6]
void DataStorage::removePatientFromWaitingList(int areaID, QString HCN, QString dateRemoved)
{
    qDebug() << "Removing a patient from waiting list";
    Database::Initialize()->removePatientFromWaitingList(areaID, HCN, dateRemoved);
}
//adding an inpatient to a waiting list [R: 2.5]
void DataStorage::addPatientToWaitingList(QString HCN,int areaID, QString dateAdded)
{
    qDebug() << "Adding an inpatient to a waiting list";
    Database::Initialize()->addPatientToWaitingList(HCN, areaID, dateAdded);
}
//adding an outpatient to a waiting list [R: 2.5]
void DataStorage::addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded)
{
    qDebug() << "Adding an outpatient to a waiting list";
    Database::Initialize()->addPatientToWaitingList(HCN, firstName, lastName, areaID, dateAdded);
}
//get all areas in the LHIN
QVector<int> DataStorage::getAllAreas()
{
    QVector<int> areaIDs = convertToOneFieldIntVector(Database::Initialize()->getAllAreas());
    return areaIDs;
}
//[R: 3.3.2]
QString DataStorage::getAreaName(int areaID)
{
    QSqlQuery areaNameQuery = Database::Initialize()->getAreaName(areaID);
    QString areaName = convertToOneString(areaNameQuery);
    return areaName;
}
//get the primary key of the area
int DataStorage::getAreaID(QString areaname)
{
    QSqlQuery areaIDQuery = Database::Initialize()->getAreaID(areaname);
    int areaID = convertToOneInt(areaIDQuery);
    return areaID;
}

//returns the facility IDs of all of the facilities in an area [R:1.8, 2.12]
QVector<int> DataStorage::getAllFacilitiesInArea(int areaID)
{
    QVector<int> facilityIDs = convertToOneFieldIntVector(Database::Initialize()->getAllFacilitiesInArea(areaID));
    return facilityIDs;
}
//returns the area ID of the facility
int DataStorage::getAreaForFacility(int facilityID)
{
    QSqlQuery areaIDQuery = Database::Initialize()->getAreaForFacility(facilityID);
    int areaID = convertToOneInt(areaIDQuery);
    return areaID;
}
//returns all facilities in the database
QVector<int> DataStorage::getAllFacilities()
{
    qDebug() << "Getting all of the facilities";
    QVector<int> facilityIDs = convertToOneFieldIntVector(Database::Initialize()->getAllFacilities());
    return facilityIDs;
}
//returns the name of the facility with the the passed in facility ID
QString DataStorage::getFacilityName(int facilityID)
{
    qDebug() << "Getting a facility's name";
    QSqlQuery facilityNameQuery = Database::Initialize()->getFacilityName(facilityID);
    QString facilityName = convertToOneString(facilityNameQuery);
    return facilityName;
}

int DataStorage::getFacilityX(int facilityID)
{
    qDebug() << "Getting a facility's X coordinate";
    QSqlQuery facilityXQuery = Database::Initialize()->getFacilityX(facilityID);
    int facilityX = convertToOneInt(facilityXQuery);
    return facilityX;
}

int DataStorage::getFacilityY(int facilityID)
{
    qDebug() << "Getting a facility's Y coordinate";
    QSqlQuery facilityYQuery = Database::Initialize()->getFacilityY(facilityID);
    int facilityY = convertToOneInt(facilityYQuery);
    return facilityY;
}
//returns the number of acute care beds at the hospital [R: 1.4, 1.5, 2.8]
int DataStorage::getTotalACBeds(int facilityID)
{
    qDebug() << "Getting total number of AC beds";
    QSqlQuery totalACBedsQuery = Database::Initialize()->getTotalACBeds(facilityID);
    int totalACBeds = convertToOneInt(totalACBedsQuery);
    return totalACBeds;
}
//returns the number of acute care beds occupied at the hospital [R: 1.4, 1.5, 2.8]
int DataStorage::getNumACBedsOccupied(int facilityID)
{
    qDebug() << "Getting number of AC beds occupied";
    QSqlQuery numACBedsOccupiedQuery = Database::Initialize()->getNumACBedsOccupied(facilityID);
    int numACBedsOccupied = convertToOneInt(numACBedsOccupiedQuery);
    return numACBedsOccupied;
}
//returns the number of complex continuing care beds at the hospital [R: 1.4, 1.5, 2.8]
int DataStorage::getTotalCCCBeds(int facilityID)
{
    qDebug() << "Getting total number of CCC beds";
    QSqlQuery totalCCCBedsQuery = Database::Initialize()->getTotalCCCBeds(facilityID);
    int totalCCCBeds = convertToOneInt(totalCCCBedsQuery);
    return totalCCCBeds;
}
//returns the number of CCC beds occupied at the hospital [R: 1.4, 1.5, 2.8]
int DataStorage::getNumCCCBedsOccupied(int facilityID)
{
    qDebug() << "Getting number of CCC beds occupied";
    QSqlQuery numCCCBedsOccupiedQuery = Database::Initialize()->getNumCCCBedsOccupied(facilityID);
    int numCCCBedsOccupied = convertToOneInt(numCCCBedsOccupiedQuery);
    return numCCCBedsOccupied;
}
//get the total number of beds at the facility [R: 2.8]
int DataStorage::getTotalNumBeds(int facilityID)
{
    qDebug() << "Getting total number of beds";
    QSqlQuery totalNumBedsQuery = Database::Initialize()->getTotalNumBeds(facilityID);
    int totalNumBeds = convertToOneInt(totalNumBedsQuery);
    return totalNumBeds;
}
//get the total number of beds occupied at the facility  [R: 2.8]
int DataStorage::getTotalNumBedsOccupied(int facilityID)
{
    qDebug() << "Getting number of beds occupied";
    QSqlQuery numTotalBedsOccupiedQuery = Database::Initialize()->getTotalNumBedsOccupied(facilityID);
    int numTotalBedsOccupied = convertToOneInt(numTotalBedsOccupiedQuery);
    return numTotalBedsOccupied;
}
//slightly redundant function. It is possible to find the count of LTC beds by checking the facility's type
int DataStorage::getTotalLTCBeds(int facilityID)
{
    QSqlQuery totalLTCBedsQuery = Database::Initialize()->getTotalLTCBeds(facilityID);
    return convertToOneInt(totalLTCBedsQuery);
}

int DataStorage::getNumLTCBedsOccupied(int facilityID)
{
    QSqlQuery numberOfLTCBedsQuery = Database::Initialize()->getNumLTCBedsOccupied(facilityID);
    return convertToOneInt(numberOfLTCBedsQuery);
}

//returns all of the inpatients at a facility by initializing a vector with their information [R: 1.7]
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
}
//[R: 2.5.7] for both functions that return part of the patient's name
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

//Returns whether the facility is a nursing home or hospital [R: 1.3]
QString DataStorage::getFacilityType(int facilityID)
{
    QSqlQuery facilityTypeQuery = Database::Initialize()->getFacilityType(facilityID);
    QString facilityType = convertToOneString(facilityTypeQuery);
    return facilityType;
}
//returns the occupancy rate log's entries from a date range (currently do not add entries to the database) [R: 3.4.1]
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
}
//Returns the database primary key of the facility
int DataStorage::getFacilityID(QString name)
{
    qDebug() << "Getting the facility ID";
    QSqlQuery facilityIDQuery = Database::Initialize()->getFacilityID(name);
    int facilityID = convertToOneInt(facilityIDQuery);
    return facilityID;
}
/*calls two function in the database class; first finds all of the outpatients on a waiting list and appends all of the inpatients on the same waiting list
  [R: 2.11]
*/
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
}
//gets the size of the waiting list in order to display it on the map
int DataStorage::getWaitingListSize(int areaID)
{

    QSqlQuery waitingListSizeQuery = Database::Initialize()->getWaitingListSize(areaID);
    return convertToOneInt(waitingListSizeQuery);
}

//logs are not fully implemented
QVector<WaitTimesEntry> DataStorage::getWaitTimesEntries(QString startDate, QString endDate, int areaID)
{

}

QVector<NumPatientsEntry> DataStorage::getWaitingListSizeEntries(QString startDate, QString endDate, int areaID)
{

}
//checks whether the guest attempting to log in has a valid user account [R: 1.1, 1.2]
bool DataStorage::isLoginValid(QString username, QString password)
{

    if(isDefaultUser(username, password))
    {
        return true;
    }
    else
    {
        QSqlQuery loginQuery = Database::Initialize()->isLoginValid(username, password);
        QString login = convertToOneString(loginQuery);
        return stringErrorCheck(login);
    }
}
//returns the user type in order to check their permissions
QString DataStorage::getUserType(QString username)
{
    qDebug() << "Getting the user's type";
    QSqlQuery userTypeQuery = Database::Initialize()->getUserType(username);
    return convertToOneString(userTypeQuery);
}
//adds a new user to the facility [R: 4.2]
void DataStorage::addUser(QString username, QString password, QString userType)
{
    qDebug() << "Trying to add a user";
    Database::Initialize()->addUser(username, password, userType);
}
//add a new facility [R: 4.3]
void DataStorage::addFacility(QString name, int x, int y, int area, int facilityID, QString facilityType)
{
    qDebug() << "Adding a new facility" << "Name: " << name << "x: " << x << " y" << y << "area " << area << " facilityid" <<facilityID << " facility type " << facilityType;
    Database::Initialize()->addFacility(name, x, y, area, facilityID, facilityType);
}

int DataStorage::myArea()
{
    return getAreaForFacility(DataStorage::myFacilityID);
}

int DataStorage::getMyFacilityID()
{
    return DataStorage::myFacilityID;
}

bool DataStorage::isMainFacility()
{
    return DataStorage::isMain;
}
//conversion between care types (as the message protocol uses ints)
int DataStorage::getCareType(QString care)
{
    QSqlQuery careTypeQuery = Database::Initialize()->getCareTypeID(care);
    return convertToOneInt(careTypeQuery);
}

QString DataStorage::getCareType(int care)
{
    QSqlQuery careTypeQuery = Database::Initialize()->getCareType(care);
    return convertToOneString(careTypeQuery);
}

void DataStorage::clearPatientsOnAreaWL(int area)
{
    Database::Initialize()->clearPatientsOnAreaWaitingList(area);
}

bool DataStorage::isInpatient(QString hcn)
{
    QSqlQuery inpatientQuery = Database::Initialize()->isInpatient(hcn);
    QString inpatientHCN = convertToOneString(inpatientQuery);
    return stringErrorCheck(inpatientHCN);
}

int DataStorage::getCurrentFacilityForPatient(QString hcn)
{
    QSqlQuery currentFacilityQuery = Database::Initialize()->getCurrentFacilityForPatient(hcn);
    return convertToOneInt(currentFacilityQuery);
}

QString DataStorage::getPatientDateAdmitted(QString hcn)
{
    QSqlQuery dateAdmittedQuery = Database::Initialize()->getPatientDateAdmitted(hcn);
    return convertToOneString(dateAdmittedQuery);
}

QString DataStorage::getPatientDateAdded(QString hcn, int areaID)
{
    QSqlQuery dateAddedQuery = Database::Initialize()->getPatientDateAdded(hcn, areaID);
    return convertToOneString(dateAddedQuery);
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

    }
    qDebug() << "One string: " << string;
    return string;
}


int DataStorage::convertToOneInt(QSqlQuery queryTemporary)
{
    bool okay;
    int integer = -1;
    while(queryTemporary.next())
    {
        integer = queryTemporary.value(0).toInt(&okay);

        if (!okay)
        {
            qDebug () << "Integer conversion failed";
            integer = -1;
        }
    }
    qDebug() << "One int: " << integer;
    return integer;
}



void DataStorage::clearPatientsAtFacility(int facilityID)
{
    Database::Initialize()->clearPatientsAtFacility(facilityID);
}

bool DataStorage::facilityExists(int facilityID)
{
    QSqlQuery facilityExistsQuery = Database::Initialize()->facilityExists(facilityID);
    int facility = convertToOneInt(facilityExistsQuery);
    return intErrorCheck(facility);
}

bool DataStorage::facilityNameExists(QString aName)
{
    int facilityID = convertToOneInt(Database::Initialize()->facilityNameExists(aName));
    return intErrorCheck(facilityID);
}

bool DataStorage::facilityExistsAtCoordinates(int x, int y)
{
    int facilityID = convertToOneInt(Database::Initialize()->facilityExistsAtCoordinates(x, y));
    return intErrorCheck(facilityID);
}

bool DataStorage::isUsernameInUse(QString aUsername, QString aPassword)
{
    QString username = convertToOneString(Database::Initialize()->isUsernameInUse(aUsername));
    bool permanentUser = stringErrorCheck(username);
    bool defaultUser = isDefaultUser(aUsername, aPassword);
    if (permanentUser || defaultUser)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DataStorage::intErrorCheck(int queryResult)
{
    if (queryResult == -1)
    {
        return false;
    }else{
        return true;
    }
}

bool DataStorage::stringErrorCheck(QString queryResult)
{
    if (queryResult.isEmpty())
    {
        return false;
    }
    return true;
}

bool DataStorage::isDefaultUser(QString username, QString password)
{
    QSettings settings("JNFconfig"); // opens the configuration file. File should be located in: home/<userfolder>/<yourusername>/.config

    settings.beginGroup("default_user");
    QString default_username =  settings.value("username").toString();
    QString default_password =  settings.value("password").toString();
    settings.endGroup();

    if((password == default_password) && (username == default_username))
    {
        return true;
    }
    return false;
}
