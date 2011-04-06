#include "datastorage.h"

int DataStorage::myFacilityID; // = 0;
QString DataStorage::myFacilityIPaddress = "0.0.0.0";
QString DataStorage::currentUserType = "ADMIN";
bool DataStorage::isMain = true;

void DataStorage::removePatientFromBed(int facilityID, QString HCN, QString dateRemoved)
{
    qDebug() << "Removing a patient from a bed";
    Database::Initialize()->removePatientFromBed(facilityID, HCN, dateRemoved);
}

void DataStorage::assignPatientToBed(int facilityID, QString HCN,int areaid, QString dateAdded)
{
    qDebug() << "Assign a patient to a bed";
    Database::Initialize()->assignPatientToBed(facilityID, HCN, areaid, dateAdded);
}

void DataStorage::addBeds(int facilityID, int numBeds, QString bedType)
{

    qDebug() << "Adding beds";
    Database::Initialize()->addBeds(facilityID, numBeds, bedType);
}

void DataStorage::removePatientFromWaitingList(int areaID, QString HCN, QString dateRemoved)
{
    qDebug() << "Removing a patient from waiting list";
    Database::Initialize()->removePatientFromWaitingList(areaID, HCN, dateRemoved);
}

void DataStorage::addPatientToWaitingList(QString HCN,int areaID, QString dateAdded)  //inpatient
{
    qDebug() << "Adding an inpatient to a waiting list";
    Database::Initialize()->addPatientToWaitingList(HCN, areaID, dateAdded);
}

void DataStorage::addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded) //outpatient
{
    qDebug() << "Adding an outpatient to a waiting list";
    Database::Initialize()->addPatientToWaitingList(HCN, firstName, lastName, areaID, dateAdded);
}

QVector<int> DataStorage::getAllAreas()
{
    QVector<int> areaIDs = convertToOneFieldIntVector(Database::Initialize()->getAllAreas());
    return areaIDs;
}

QString DataStorage::getAreaName(int areaID)
{
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
    qDebug() << "Getting all of the facilities";
    QVector<int> facilityIDs = convertToOneFieldIntVector(Database::Initialize()->getAllFacilities());
    return facilityIDs;
}

QString DataStorage::getFacilityName(int facilityID)
{
    qDebug() << "Getting a facility's names";
    QSqlQuery facilityNameQuery = Database::Initialize()->getFacilityName(facilityID);
    QString facilityName = convertToOneString(facilityNameQuery);
    return facilityName;
}

int DataStorage::getFacilityX(int facilityID)
{
    qDebug() << "Getting a facility's X";
    QSqlQuery facilityXQuery = Database::Initialize()->getFacilityX(facilityID);
    int facilityX = convertToOneInt(facilityXQuery);
    return facilityX;
}

int DataStorage::getFacilityY(int facilityID)
{
    qDebug() << "Getting a facility's Y";
    QSqlQuery facilityYQuery = Database::Initialize()->getFacilityY(facilityID);
    int facilityY = convertToOneInt(facilityYQuery);
    return facilityY;
}

int DataStorage::getTotalACBeds(int facilityID)
{
    qDebug() << "Getting total number of AC beds";
    QSqlQuery totalACBedsQuery = Database::Initialize()->getTotalACBeds(facilityID);
    int totalACBeds = convertToOneInt(totalACBedsQuery);
    return totalACBeds;
}

int DataStorage::getNumACBedsOccupied(int facilityID)
{
    qDebug() << "Getting number of AC beds occupied";
    QSqlQuery numACBedsOccupiedQuery = Database::Initialize()->getNumACBedsOccupied(facilityID);
    int numACBedsOccupied = convertToOneInt(numACBedsOccupiedQuery);
    return numACBedsOccupied;
}

int DataStorage::getTotalCCCBeds(int facilityID)
{
    qDebug() << "Getting total number of CCC beds";
    QSqlQuery totalCCCBedsQuery = Database::Initialize()->getTotalCCCBeds(facilityID);
    int totalCCCBeds = convertToOneInt(totalCCCBedsQuery);
    return totalCCCBeds;
}

int DataStorage::getNumCCCBedsOccupied(int facilityID)
{
    qDebug() << "Getting number of CCC beds occupied";
    QSqlQuery numCCCBedsOccupiedQuery = Database::Initialize()->getNumCCCBedsOccupied(facilityID);
    int numCCCBedsOccupied = convertToOneInt(numCCCBedsOccupiedQuery);
    return numCCCBedsOccupied;
}

int DataStorage::getTotalNumBeds(int facilityID)
{
    qDebug() << "Getting total number of beds";
    QSqlQuery totalNumBedsQuery = Database::Initialize()->getTotalNumBeds(facilityID);
    int totalNumBeds = convertToOneInt(totalNumBedsQuery);
    return totalNumBeds;
}

int DataStorage::getTotalNumBedsOccupied(int facilityID)
{
    qDebug() << "Getting number of beds occupied ";
    QSqlQuery numTotalBedsOccupiedQuery = Database::Initialize()->getTotalNumBedsOccupied(facilityID);
    int numTotalBedsOccupied = convertToOneInt(numTotalBedsOccupiedQuery);
    return numTotalBedsOccupied;
}


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

int DataStorage::getFacilityID(QString name)
{
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
}

int DataStorage::getWaitingListSize(int areaID)
{

    QSqlQuery waitingListSizeQuery = Database::Initialize()->getWaitingListSize(areaID);
    return convertToOneInt(waitingListSizeQuery);
}

QVector<WaitTimesEntry> DataStorage::getWaitTimesEntries(QString startDate, QString endDate, int areaID)
{

}

QVector<NumPatientsEntry> DataStorage::getWaitingListSizeEntries(QString startDate, QString endDate, int areaID)
{

}

bool DataStorage::isLoginValid(QString username, QString password)
{



    return true; /***************this line is ONLY FOR TESTING****************************************************/




    QSettings settings("JNFconfig"); // opens the configuration file. File should be located in: home/<userfolder>/<yourusername>/.config

    settings.beginGroup("default_user");
    QString default_username =  settings.value("username").toString();
    QString default_password =  settings.value("password").toString();
    settings.endGroup();

    if((password == default_password) && (username == default_username))
    {
        return true;
    }
    else
    {
        QSqlQuery loginQuery = Database::Initialize()->isLoginValid(username, password);
        QString login = convertToOneString(loginQuery);
        if (login.isEmpty())
        {
            return false;
        }else{
            return true;
        }
    }
}

QString DataStorage::getUserType(QString username)
{
    qDebug() << "Getting the user's type";
    QSqlQuery userTypeQuery = Database::Initialize()->getUserType(username);
    return convertToOneString(userTypeQuery);
}

void DataStorage::addUser(QString username, QString password, QString userType)
{
    qDebug() << "Trying to add a user";
    Database::Initialize()->addUser(username, password, userType);
}

void DataStorage::addFacility(QString name, int x, int y, int area, int facilityID, QString facilityType)
{
    qDebug() << "Adding a new facility" << "Name: " << name << "x: " << x << " y" << y << "area " << area << " facilityid" <<facilityID << " facility type " << facilityType;
    Database::Initialize()->addFacility(name, x, y, area, facilityID, facilityType);
    qDebug() <<"Facility X: ";
    getFacilityX(facilityID);
    qDebug() <<"Facility Y: ";
    getFacilityY(facilityID);

}

int DataStorage::myArea()
{
    return getAreaForFacility(DataStorage::myFacilityID);
}

int DataStorage::getMyFacilityID()
{
    return DataStorage::myFacilityID;
}

bool DataStorage::isMainFacility() //need to add this to the configure file
{
    return DataStorage::isMain;
}

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
    if (inpatientHCN.isEmpty())
    {
        return false;
    }
    return true;
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
    if (facility == -1)
    {
        return false;
    }
    return true;
}

void DataStorage::populateTemporaryDatabase()
{
    //insert temporary data into the database for testing
    DataStorage::addFacility("Hospital 1", 56, 45, 0, 23, "Hospital");
    DataStorage::addFacility("Hospital 2", 70, 80, 2, 20, "Hospital");
    DataStorage::addFacility("Nursing Home 1",200,200,5,15, "Nursing Home");

    DataStorage::addBeds(3,10,"AC");
    DataStorage::addBeds(3,14,"CCC");

    DataStorage::addBeds(23,24,"AC");
    DataStorage::addBeds(23,5,"CCC");

    DataStorage::addBeds(15,14,"LTC");

    DataStorage::addPatientToWaitingList("12","Joe", "Black",1,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("13","Jane", "Black",1,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("14","Bob", "Smith",1,"120112T11:33:54");

    DataStorage::addPatientToWaitingList("12","Joe", "Black",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("13","Jane", "Black",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("14","Bob", "Smith",2,"120112T11:33:54");

    DataStorage::assignPatientToBed(3,"12",1,"120112T11:33:54");
    DataStorage::assignPatientToBed(3,"13",1,"120112T11:33:54");
    DataStorage::assignPatientToBed(3,"14",1,"120112T11:33:54");


}
