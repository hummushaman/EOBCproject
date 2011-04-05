#include "database.h"

//ADD ERROR CHECKING->AT LEAST MIGHT HAVE TO ADD GETRECORD() FOR FLOAT, GET RECORD FOR VECTOR (MAYBE BUT INTO THE DATASTORAGE CLASS!!!)

//TO DO: add log checking (complicated for waiting list related logging)
Database* Database::databaseClassInstance = NULL;

Database::~Database()
{
    QSqlDatabase::database("permanent").close();
    QSqlDatabase::removeDatabase("permanent");

    QSqlDatabase::database("temporary").close();
    QSqlDatabase::removeDatabase("temporary");

    delete databaseClassInstance;
}
Database* Database::Initialize()
{
    if (databaseClassInstance == NULL)
    {
        databaseClassInstance = new Database();
    }
    return databaseClassInstance;
}

Database::Database()
{
    //read in configuration file
    QSettings settings("JNFconfig");

    settings.beginReadArray("myFacility");
    QString facilityName = settings.value("name").toString();
    int area = settings.value("area").toInt();
    myFacilityID = settings.value("id").toInt();

    int x = settings.value("x").toInt();
    int y = settings.value("y").toInt();

    QString readMainFacility = settings.value("isMain").toString();
    QString facilityType = settings.value("facilityType").toString();
    qDebug() << "read in facility type: " << facilityType;
    settings.endArray();

    if(readMainFacility == "true")
    {
        isMainFacility = true;
    }
    else
    {
        isMainFacility = false;
    }
    settings.beginGroup("database");
    QString filename = settings.value("temp_db").toString();
    settings.endGroup();

    //now check that the database contains information about the facility in the configuration file
    QString aQuery = "SELECT facilityid FROM facility WHERE facilityid = " + QString::number(myFacilityID);
    QSqlQuery checkPermanent = queryDatabase(aQuery, "permanent");
    int facilityID = getID(checkPermanent);
    qDebug() << "ID in permanent database: " << facilityID;
    if (!(facilityID == myFacilityID))
    {
        aQuery = "SELECT facilitytypeid FROM facilitytypes WHERE facilitytype = '" + facilityType + "'";
        qDebug() << aQuery;
        QSqlQuery facilityTypeIDQuery = queryDatabase(aQuery, "permanent");

        int facilityTypeID = getID(facilityTypeIDQuery);
        qDebug() << "Permanent facility insertion: -id " << facilityTypeID;
        if (!(facilityTypeID == -1))
        {
            aQuery = "INSERT INTO facility (facilityid, areaid, facilitytypeid, name, x, y) VALUES (" + QString::number(myFacilityID) + ", " + QString::number(area) + ", " + QString::number(facilityTypeID) + ", '" + facilityName + "', " + QString::number(x) + ", " + QString::number(y) + ")";
            qDebug() << aQuery;
            queryDatabase(aQuery, "permanent");
            if (facilityType == "Hospital")
            {
                aQuery = "INSERT INTO hospital (hospitalid) VALUES (" + QString::number(myFacilityID) + ")";
                qDebug() << aQuery;
                queryDatabase(aQuery, "permanent");
            }
        }
    }

    {
        QSqlDatabase temporaryDatabase = QSqlDatabase::addDatabase("QSQLITE", "temporary");
        temporaryDatabase.setDatabaseName(":memory:");
    }
    //create temporary tables
    QSqlQuery queryTemporary(QSqlDatabase::database("temporary"));
    QSqlQuery queryPermanent(QSqlDatabase::database("permanent"));

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream input(&file);
        QString sqlQuery = "";
        int tableCount = 0;
        while (!input.atEnd())
        {
            QString line = input.readLine();
            QStringList list = line.split(";");
            if (list.size() == 1 && (!line.isEmpty()))
            {
                sqlQuery += list.takeFirst();
            }
            else if (list.size() > 1)
            {
                sqlQuery += list.takeFirst();
                queryTemporary.exec(sqlQuery);
                sqlQuery = "";
                ++tableCount;
            }
        }

        file.close();

        qDebug() << "Temporary Tables: " <<  QSqlDatabase::database("temporary").tables();
        qDebug() << "Permanent Tables: " <<  QSqlDatabase::database("permanent").tables();

        //add all of the permanent databases data to the temporary table: REALLY INEFFICIENT AT THE MOMENT
        for (int tableIndex = 0; tableIndex < tableCount; tableIndex++)
        {
            /*
        TESTING:

        qDebug() << "FOR LOOP: " << table;
        QString aQuery = "SELECT * FROM " +table;
        queryPermanent.exec(aQuery);
        QSqlRecord record = queryPermanent.record();
        for (int i = 0; i < record.count(); i++)
        {
            QString test = record.fieldName(i);
             qDebug() << "2nd FOR LOOP: " << test;

        }*/
            //EXAMPLES OF COPYING DATABASE TABLES
            //INSERT INTO X.TABLE(Id, Value) SELECT * FROM Y.TABLE;
            // $pdo->exec('CREATE TABLE bar AS SELECT * FROM filedb.foo');

            // QSqlQuery q("select * from employees");
            //QSqlRecord rec = q.record();

            //qDebug() << "Number of columns: " << rec.count();

            //int nameCol = rec.indexOf("name"); // index of the field "name"
            //while (q.next())
            //  qDebug() << q.value(nameCol).toString(); // output all names

            QString queryPermanentTable = "SELECT * FROM " + QSqlDatabase::database("permanent").tables().at(tableIndex);
            queryPermanent.exec(queryPermanentTable);
            QSqlRecord columns = queryPermanent.record();

            QString fieldTitles = " (";
            for (int columnIndex = 0; columnIndex < columns.count(); columnIndex++)
            {
                if (!((columnIndex + 1) == columns.count()))
                {
                    fieldTitles += columns.fieldName(columnIndex) + ",";
                }else
                {
                    fieldTitles += columns.fieldName(columnIndex) + ") ";
                }
            }
            while(queryPermanent.next())
            {

                QString fieldValues = " (";
                for (int columnIndex = 0; columnIndex < columns.count(); columnIndex++)
                {
                    QSqlField columnField = columns.field(columnIndex);

                    //check whether the column is a string (requires quotations to be a proper sql statement)
                    if (columnField.type() == QVariant::String)
                    {
                        fieldValues += "'" + queryPermanent.value(columnIndex).toString() + "'";
                    }
                    else
                    {
                        fieldValues += queryPermanent.value(columnIndex).toString();
                    }

                    //formatting
                    if (!((columnIndex + 1) == columns.count()))
                    {
                        fieldValues += ",";
                    }
                    else
                    {
                        fieldValues += ")";
                    }
                }
                QString insertIntoTemporaryTable = "INSERT INTO " + QSqlDatabase::database("temporary").tables().at(tableIndex) + fieldTitles + "VALUES" + fieldValues;
                //qDebug() << insertIntoTemporaryTable;
                queryTemporary.exec(insertIntoTemporaryTable);
            }

        }
        qDebug() << "NOW TESTING WHETHER THE INSERT WORKED: ";
        //print out temporary tables to double check that the data was copied
        for (int tableIndex = 0; tableIndex < tableCount; tableIndex++)
        {
            QString printTable = "SELECT * FROM " + QSqlDatabase::database("temporary").tables().at(tableIndex);
            qDebug() << printTable;
            queryTemporary.exec(printTable);
            QSqlRecord aRecord = queryTemporary.record();
            while(queryTemporary.next())
            {
                printTable = "";
                for (int i = 0; i < aRecord.count(); i++)
                {
                    printTable += queryTemporary.value(i).toString();
                }
                qDebug() << printTable;
            }
        }
    }
}

bool Database::isMyFacility(int facilityID)
{
    if (facilityID == myFacilityID)
    {
        return true;
    }
    return false;
}

void Database::removePatientFromBed(int facilityID, QString HCN, QString dateRemoved)
{
    removePatientFromBed("temporary", facilityID, HCN, dateRemoved);
    if (isMyFacility(facilityID))
    {
        removePatientFromBed("permanent", facilityID, HCN, dateRemoved);
    }
}

void Database::removePatientFromBed(QString databaseConnection, int facilityID, QString HCN, QString dateRemoved) //assuming inpatient
{
    QSqlQuery facilityTypeQueryResult = getFacilityType(facilityID);
    QString facilityType = getType(facilityTypeQueryResult);
    if (facilityType == "Hospital")
    {
        QString patientCurrentCareQuery = "SELECT currentcaretypeid FROM inpatient WHERE (inpatienthealthcarenumber = '" + HCN + "')";
        qDebug() << patientCurrentCareQuery;
        QSqlQuery patientCurrentCareQueryResult = queryDatabase(patientCurrentCareQuery, "temporary");
        int currentCareTypeID = getID(patientCurrentCareQueryResult);
        QString currentCareType = getType(getCareType(currentCareTypeID));

        if (currentCareType == "AC")
        {
            updateNumberOfACBedsOccupied(databaseConnection, facilityID, -1);
            updateTotalNumberOfBedsOccupied(databaseConnection, facilityID, -1, false);
        }
        else if (currentCareType == "CCC")
        {
            updateNumberOfCCCBedsOccupied(databaseConnection, facilityID, -1);
            updateTotalNumberOfBedsOccupied(databaseConnection, facilityID, -1, false);
        }
    }
    else if (facilityType == "Nursing Home")
    {
        updateTotalNumberOfBedsOccupied(databaseConnection, facilityID, -1, true);
    }
    QString deletePatientQuery = "DELETE FROM inpatient WHERE (inpatienthealthcarenumber = '" + HCN + "')";
    qDebug() << deletePatientQuery;
    updateDatabase(deletePatientQuery, databaseConnection);
}

void Database::updateNumberOfACBedsOccupied(QString databaseConnection, int facilityID, int amount)
{
    QString aQuery = "SELECT numACBedsOccupied FROM hospital WHERE (hospitalid = " + QString::number(facilityID) + ")";
    qDebug() << aQuery;
    QSqlQuery numberOfACBedsOccupiedQuery = queryDatabase(aQuery, databaseConnection);
    int numberOfACBedsOccupied = getID(numberOfACBedsOccupiedQuery) + amount; //odd function name-> maybe rename to get int

    qDebug() << "New number of AC beds occupied: " << numberOfACBedsOccupied;

    aQuery = "UPDATE hospital SET numACBedsOccupied = " + QString::number(numberOfACBedsOccupied) + " WHERE (hospitalid = " + QString::number(facilityID) + ")";
    qDebug() << aQuery;
    updateDatabase(aQuery, databaseConnection);

    if (isMyFacility(facilityID) && isPermanentDatabaseConnection(databaseConnection))
    {
        //update log ******************************
    }
}
bool Database::isPermanentDatabaseConnection(QString aConnection)
{
    if (aConnection == "permanent")
    {
        return true;
    }
    return false;
}

void Database::updateNumberOfCCCBedsOccupied(QString databaseConnection,int facilityID, int amount)
{
    QString aQuery = "SELECT numCCCBedsOccupied FROM hospital WHERE (hospitalid = " + QString::number(facilityID) + ")";
    qDebug() << aQuery;
    QSqlQuery numberOfCCCBedsOccupiedQuery = queryDatabase(aQuery, databaseConnection);
    int numberOfCCCBedsOccupied = getID(numberOfCCCBedsOccupiedQuery) + amount; //odd function name-> maybe rename to get int
    qDebug() << "New number of CCC beds occupied " << numberOfCCCBedsOccupied;
    aQuery = "UPDATE hospital SET numCCCBedsOccupied = " + QString::number(numberOfCCCBedsOccupied) + " WHERE (hospitalid = " + QString::number(facilityID) + ")";
    qDebug() << aQuery;
    updateDatabase(aQuery, databaseConnection);

    if (isMyFacility(facilityID) && isPermanentDatabaseConnection(databaseConnection))
    {
        //update log ******************************
    }
}

void Database::updateTotalNumberOfBedsOccupied(QString databaseConnection, int facilityID, int amount, bool updateLog)
{

    QString aQuery = "SELECT numBedsOccupied FROM facility WHERE (facilityid = " + QString::number(facilityID) + ")";
    qDebug() << aQuery;
    QSqlQuery totalNumberOfBedsOccupiedQuery = queryDatabase(aQuery, databaseConnection);
    int totalNumberOfBedsOccupied = getID(totalNumberOfBedsOccupiedQuery) + amount; //odd function name-> maybe rename to get int
    qDebug() << "New number of beds occupied: " << totalNumberOfBedsOccupied;
    aQuery = "UPDATE facility SET numBedsOccupied = " + QString::number(totalNumberOfBedsOccupied) + " WHERE (facilityid = " + QString::number(facilityID) + ")";
    qDebug() << aQuery;
    updateDatabase(aQuery, databaseConnection);

    if (isMyFacility(facilityID) && isPermanentDatabaseConnection(databaseConnection) && updateLog)
    {
        //update log ******************************
    }
}


void Database::assignPatientToBed(int facilityID, QString HCN, int areaID, QString dateAssigned) //only applicable to Nursing Home("LTC")
{
    QSqlQuery isInpatientQuery = isInpatient(HCN);
    QString aHealthCareNumber = getType(isInpatientQuery);
    int LTCID = getID(getCareTypeID("LTC")); //always assigning a patient to a nursing home (get the appropriate code)

    if (HCN == aHealthCareNumber) //the patient is an inpatient
    {
        QSqlQuery currentFacilityQueryResult = getCurrentFacilityForPatient(HCN);
        int currentFacility = getID(currentFacilityQueryResult);
        removePatientFromBed(currentFacility, HCN, dateAssigned); //will remove the patient from the permanent database if it is our facility
        removePatientFromAllWaitingLists(HCN, areaID, dateAssigned);

        if ((isMyFacility(currentFacility)) && (!isMyFacility(facilityID)))
        {
            removePatientFromBed("permanent", currentFacility, HCN, dateAssigned);
            QString addInpatient = "INSERT INTO inpatient(inpatienthealthcarenumber, currentFacilityid, dateAdmittedToFacility, currentCareTypeid) VALUES ('" + HCN + "', " + QString::number(facilityID) + ", '" + dateAssigned + "', " + QString::number(LTCID) + ")";
            qDebug() << addInpatient;
            updateDatabase(addInpatient, "permanent");
        }

        removePatientFromBed("temporary", currentFacility, HCN, dateAssigned);
        QString addInpatient = "INSERT INTO inpatient(inpatienthealthcarenumber, currentFacilityid, dateAdmittedToFacility, currentCareTypeid) VALUES ('" + HCN + "', " + QString::number(facilityID) + ", '" + dateAssigned + "', " + QString::number(LTCID) + ")";
        qDebug() << addInpatient;
        updateDatabase(addInpatient, "temporary");
    }
    else //check whether the patient is an outpatient
    {
        QString aQuery = "SELECT healthcarenumber FROM patient WHERE (healthcarenumber = '" + HCN + "')";
        QSqlQuery patientQuery = queryDatabase(aQuery, "temporary");
        aHealthCareNumber =  getType(patientQuery);

        if (HCN == aHealthCareNumber) //the patient is an outpatient
        {
            removePatientFromAllWaitingLists(HCN, areaID, dateAssigned);
            QString aQuery = "INSERT INTO inpatient (inpatienthealthcarenumber, currentFacilityid, dateAdmittedToFacility, currentCareTypeid) VALUES ('" + HCN + "', " + QString::number(facilityID) + ", '" + dateAssigned + "', 'LTC')";
            qDebug() << "Outpatient: " << aQuery;
            queryDatabase(aQuery, "temporary");

        }
    }
    updateTotalNumberOfBedsOccupied("temporary", facilityID, 1, false);
    if (isMyFacility(facilityID))
    {
        updateTotalNumberOfBedsOccupied("permanent", facilityID, 1, true);
    }
}

void Database::removePatientFromAllWaitingLists(QString HCN, int areaID, QString dateRemoved)
{
    QString aQuery = "DELETE FROM waitinglistentries WHERE (healthcarenumber = '" + HCN +"')";
    updateDatabase(aQuery, "temporary");
    if (isMyArea(areaID) && isMainFacility)
    {
        removePatientFromWaitingList("permanent", areaID, HCN, dateRemoved);
    }
}

void Database::addBeds(int facilityID, int numBeds, QString bedType)
{
    addBeds("temporary", facilityID, numBeds, bedType);
    if (isMyFacility(facilityID))
    {
        addBeds("permanent", facilityID, numBeds, bedType);
    }
}

void Database::addBeds(QString databaseConnection, int facilityID, int numBeds, QString bedType)
{
    QSqlQuery facilityTypeQueryResult = getFacilityType(facilityID);
    QString facilityType = getType(facilityTypeQueryResult);
    qDebug() << "Adding beds to: " << facilityType;

    if (facilityType == "Hospital")
    {
        if (bedType == "AC")
        {
            updateNumberOfACBeds(databaseConnection, facilityID, numBeds);
            updateTotalNumberOfBeds(databaseConnection, facilityID, numBeds, false);
        }
        else if (bedType == "CCC")
        {
            updateNumberOfCCCBeds(databaseConnection, facilityID, numBeds);
            updateTotalNumberOfBeds(databaseConnection, facilityID, numBeds, false);
        }

    }
    else if (facilityType == "Nursing Home")
    {
        updateTotalNumberOfBeds(databaseConnection, facilityID, numBeds, true);
    }
}

void Database::updateNumberOfACBeds(QString databaseConnection, int facilityID, int amount)
{
    qDebug() << "number of AC beds to add: " << amount;
    QString aQuery = "SELECT totalACBeds FROM hospital WHERE (hospitalid = " + QString::number(facilityID) + ")";
    qDebug() << aQuery;
    QSqlQuery numberOfACBedsQuery = queryDatabase(aQuery, databaseConnection);
    int oldnumber = getID(numberOfACBedsQuery);
    qDebug() << "Old number of AC beds: " << oldnumber;
    int numberOfACBeds = oldnumber + amount; //odd function name-> maybe rename to getInt
    qDebug() << "New number of AC beds: " << numberOfACBeds;
    aQuery = "UPDATE hospital SET totalACBeds = " + QString::number(numberOfACBeds) + " WHERE (hospitalid = " + QString::number(facilityID) + ")";
    qDebug() << aQuery;
    updateDatabase(aQuery, databaseConnection);

    if (isPermanentDatabaseConnection(databaseConnection))
    {
        //update log ******************************
    }
}

void Database::updateNumberOfCCCBeds(QString databaseConnection, int facilityID, int amount)
{
    QString aQuery = "SELECT totalCCCBeds FROM hospital WHERE (hospitalid = " + QString::number(facilityID) + ")";
    qDebug() << aQuery;
    QSqlQuery numberOfCCCBedsQuery = queryDatabase(aQuery, databaseConnection);
    int numberOfCCCBeds = getID(numberOfCCCBedsQuery) + amount; //odd function name-> maybe rename to get int
    qDebug() << "New number of CCC " << numberOfCCCBeds;
    aQuery = "UPDATE hospital SET totalCCCBeds = " + QString::number(numberOfCCCBeds) + " WHERE (hospitalid = " + QString::number(facilityID) + ")";
    qDebug() << aQuery;
    updateDatabase(aQuery, databaseConnection);
    if (isPermanentDatabaseConnection(databaseConnection))
    {
        //update log******************************
    }
}

void Database::updateTotalNumberOfBeds(QString databaseConnection, int facilityID, int amount, bool updateLog)
{
    QString aQuery = "SELECT totalBeds FROM facility WHERE facilityid = " + QString::number(facilityID);
    qDebug() << aQuery;
    QSqlQuery totalNumberOfBedsQuery = queryDatabase(aQuery, databaseConnection);
    int totalNumberOfBeds = getID(totalNumberOfBedsQuery) + amount; //odd function name-> maybe rename to get int
    aQuery = "UPDATE facility SET totalBeds = " + QString::number(totalNumberOfBeds) + " WHERE (facilityid = " + QString::number(facilityID) + ")";
    qDebug() << aQuery;
    updateDatabase(aQuery, databaseConnection);
    if (isPermanentDatabaseConnection(databaseConnection) && updateLog)
    {
        //update log******************************
    }
}

void Database::removePatientFromWaitingList(int areaID, QString HCN, QString dateRemoved)
{
    removePatientFromWaitingList("temporary", areaID, HCN, dateRemoved);
    if (isMainFacility && isMyArea(areaID))
    {
        removePatientFromWaitingList("permanent", areaID, HCN, dateRemoved);
    }
}
void Database::removePatientFromWaitingList(QString databaseConnection, int areaID, QString HCN, QString dateRemoved)
{
    QString aQuery = "DELETE FROM waitinglistentries WHERE (healthcarenumber = '" + HCN + "' AND " + "areaid = " + QString::number(areaID) + ")";
    updateDatabase(aQuery, databaseConnection);
    //update log! if permanent connection ***********************
}

//inpatient version: assumed that they are not on this the waiting list && they are already at a facility
void Database::addPatientToWaitingList(QString HCN, int areaID, QString dateAdded)
{

    addPatientToWaitingList("temporary", HCN, areaID, dateAdded);
    if (isMainFacility && isMyArea(areaID))
    {
        addPatientToWaitingList("permanent", HCN, areaID, dateAdded);
    }

}
//inpatient version: assumed that they are not on this waiting list && they are already at a facility
void Database::addPatientToWaitingList(QString databaseConnection, QString HCN, int areaID, QString dateAdded)
{
    QString aQuery = "INSERT INTO waitinglistentries (healthcarenumber, areaid, dateaddedtolist) VALUES ('" + HCN + "', " + QString::number(areaID) + ", '" + dateAdded + "')";
    qDebug() << aQuery;
    updateDatabase(aQuery, databaseConnection);
    //update log! if permanent connection ***********************
}


void Database::addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded) //outpatient
{
    addPatientToWaitingList("temporary", HCN, firstName, lastName, areaID, dateAdded);
    if (isMainFacility && isMyArea(areaID))
    {
        addPatientToWaitingList("permanent", HCN, firstName, lastName, areaID, dateAdded);
    }
}

//outpatient version: assumed that they are not on the waiting list
void Database::addPatientToWaitingList(QString databaseConnection, QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded)
{
    QString aQuery = "INSERT INTO patient (healthcarenumber, firstname, lastname, requiredcaretypeid) VALUES ('" + HCN + "', '" + firstName + "', '" + lastName + "', 3)";
    qDebug() << aQuery;
    updateDatabase(aQuery, databaseConnection);

    aQuery = "INSERT INTO waitinglistentries (healthcarenumber, areaid, dateaddedtolist) VALUES ('" + HCN + "', " + QString::number(areaID) + ", '" + dateAdded + "')";
    qDebug() << aQuery;
    updateDatabase(aQuery, databaseConnection);
    //update log! if my permanent database connection ***********************

    aQuery = "SELECT * FROM patient";
    qDebug() << "Printing out newly added patient";
    QSqlQuery query = queryDatabase(aQuery, "temporary");
    int columnCount = query.record().count();
    while (query.next())
    {
        QString print;
        for (int i = 0; i < columnCount; i++)
        {
            print += query.value(i).toString();
        }
        qDebug() << print;
    }
}

QSqlQuery Database::getAllAreas()
{
    QString aQuery = "SELECT areaid FROM area";
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getAreaName(int areaID)
{
    QString aQuery = "SELECT name FROM area WHERE areaid = " + QString::number(areaID);
    qDebug() << "getAreaName: " << aQuery;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getAreaID(QString areaname)
{
    QString aQuery = "SELECT areaid FROM area WHERE name = '" + areaname + "'";
    qDebug() << "getAreaID: " << aQuery;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getAllFacilitiesInArea(int areaID)
{
    QString aQuery = "SELECT facilityid FROM facility WHERE areaid = " + QString::number(areaID);
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getAreaForFacility(int facilityID)
{
    QString aQuery = "SELECT areaid FROM facility WHERE facilityid = " + QString::number(facilityID);
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getAllFacilities()
{
    QString aQuery = "SELECT facilityid FROM facility";
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getFacilityName(int facilityID)
{
    QString aQuery = "SELECT name FROM facility WHERE facilityid = " + QString::number(facilityID);
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getFacilityX(int facilityID)
{
    QString aQuery = "SELECT x FROM facility WHERE facilityid = " + QString::number(facilityID);
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getFacilityY(int facilityID)
{
    QString aQuery = "SELECT y FROM facility WHERE facilityid = " + QString::number(facilityID);
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getTotalACBeds(int facilityID)
{
    QString aQuery = "SELECT totalACBeds FROM hospital WHERE hospitalid = " + QString::number(facilityID);
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getNumACBedsOccupied(int facilityID)
{
    QString aQuery = "SELECT numACBedsOccupied FROM hospital WHERE hospitalid = " + QString::number(facilityID);
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getTotalCCCBeds(int facilityID)
{
    QString aQuery = "SELECT totalCCCBeds FROM hospital WHERE hospitalid = " + QString::number(facilityID);
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getNumCCCBedsOccupied(int facilityID)
{
    QString aQuery = "SELECT numCCCBedsOccupied FROM hospital WHERE hospitalid = " + QString::number(facilityID);
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getTotalNumBeds(int facilityID)
{
    QString aQuery = "SELECT totalBeds FROM facility WHERE facilityid = " + QString::number(facilityID);
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getTotalNumBedsOccupied(int facilityID)
{
    QString aQuery = "SELECT numBedsOccupied FROM facility WHERE facilityid = " + QString::number(facilityID);
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getPatientsAtFacility(int facilityID)
{
    QString aQuery = "SELECT healthcarenumber, firstname, lastname, requiredcaretype, currentcaretype, dateadmittedtofacility, currentfacilityid FROM"
                     "(SELECT * FROM"
                     "(SELECT * FROM inpatient JOIN patient ON (inpatienthealthcarenumber = healthcarenumber) WHERE currentfacilityid = " + QString::number(facilityID) +
                     "JOIN"
                     "(SELECT inpatienthealthcarenumber as hcn, caretype as currentcaretype FROM inpatient JOIN caretypes ON (currentcaretypeid = caretypeid)) ON (healthcarenumber = hcn))"
                     "JOIN"
                     "(SELECT healthcarenumber as healthcardnum, caretype as requiredcaretype FROM patient JOIN caretypes ON (requiredcaretypeid = caretypeid))"
                     "ON (healthcarenumber = healthcardnum)";
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getPatientFirstName(QString patientHCN)
{
    QString aQuery = "SELECT firstname FROM patient WHERE healthcarenumber = '" + patientHCN + "'";
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getPatientLastName(QString patientHCN)
{
    QString aQuery = "SELECT lastname FROM patient WHERE healthcarenumber = '" + patientHCN + "'";
    return queryDatabase(aQuery, "temporary");
}

//"Hospital" or "Nursing Home"
QSqlQuery Database::getFacilityType(int facilityID)
{
    QString aQuery = "SELECT facilitytype FROM "
                     "(SELECT * FROM facility JOIN facilitytypes ON (facility.facilitytypeid = facilitytypes.facilitytypeid) "
                     "WHERE facilityid = " + QString::number(facilityID) + ")";
    qDebug () << aQuery;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::queryDatabase(QString aQuery, QString aDatabaseConnection)
{
    QSqlQuery queryTemporary(QSqlDatabase::database(aDatabaseConnection));
    queryTemporary.exec(aQuery);
    return queryTemporary;
}

void Database::updateDatabase(QString aQuery, QString aDatabaseConnection)
{
    QSqlQuery queryTemporary(QSqlDatabase::database(aDatabaseConnection));
    queryTemporary.exec(aQuery);
}

QSqlQuery Database::getFacilityID(QString name)
{
    QString aQuery = "SELECT facilityid FROM facility WHERE name = '" + name + "'";
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getWaitingListInpatients(int areaID)
{
    QString aQuery =
            "SELECT healthcarenumber, firstname, lastname, requiredcaretype, currentcaretype, dateadmittedtofacility, currentfacilityid FROM "
            "(SELECT * FROM "
            "(SELECT * FROM "
            "(SELECT inpatienthealthcarenumber as hcn, caretype as currentcaretype FROM inpatient JOIN caretypes ON (currentcaretypeid = caretypeid)) "
            "JOIN "
            "(SELECT * FROM patient JOIN "
            "(SELECT * FROM waitinglistentries JOIN inpatient ON (healthcarenumber = inpatienthealthcarenumber)) "
            "ON (inpatienthealthcarenumber = patient.healthcarenumber) WHERE areaid = " + QString::number(areaID) + ") "
            "ON (inpatienthealthcarenumber = hcn)) "
            "JOIN "
            "(SELECT healthcarenumber as healthcarenum, caretype as requiredcaretype FROM patient JOIN caretypes ON (requiredcaretypeid = caretypeid)) "
            "ON (healthcarenum = inpatienthealthcarenumber))";
    qDebug() << "Get waiting list inpatients " << aQuery;
    return queryDatabase(aQuery, "temporary");
}


QSqlQuery Database::getWaitingListOutpatients(int areaID)
{
    QString aQuery =
            "SELECT healthcarenumber, firstname, lastname, requiredcaretype FROM "
            "(SELECT * FROM  waitinglistentries JOIN "
            "(SELECT * FROM "
            "(SELECT healthcarenumber as healthcarenum FROM patient WHERE healthcarenumber NOT IN (SELECT inpatienthealthcarenumber FROM inpatient)) "
            "JOIN "
            "(SELECT * FROM patient) "
            "ON (healthcarenumber = healthcarenum)) "
            "ON "
            "(waitinglistentries.healthcarenumber = healthcarenum) WHERE areaid = " + QString::number(areaID) + ") "
            "JOIN "
            "(SELECT healthcarenumber as hcn, caretype as requiredcaretype FROM patient JOIN caretypes ON (requiredcaretypeid = caretypeid)) "
            "ON "
            "(healthcarenumber = hcn)";
    qDebug() << "Get waiting list outpatients " << aQuery;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getWaitingListSize(int areaID) //MAP
{
    QString aQuery = "SELECT count(healthcarenumber) FROM waitinglistentries WHERE (areaid = " +  QString::number(areaID) + ")";
    qDebug() << aQuery;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getOccupancyRateEntries(QString startDate, QString endDate, QString careType, int facilityID)
{
    QString aQuery = "SELECT dateofchange, caretype, occupancyrate FROM "
                     "(SELECT * FROM occupancyratelog JOIN caretypes ON (occupancyratelog.caretypeid = caretypes.caretypeid))"
                     "WHERE (datetime(dateofchange) >= '" + startDate + "' AND datetime(dateofchange) <= '" + endDate + "' AND caretype = '" + careType + "' AND facilityid =" + QString::number(facilityID) + ")";
    return queryDatabase(aQuery, "permanent");
}

QSqlQuery Database::getWaitTimesEntries(QString startDate, QString endDate, int areaID)
{
    QString aQuery = "SELECT dateremoved, waittimesindays FROM "
                     "WHERE (datetime(dateremoved) >= '" + startDate + "' AND datetime(dateremoved) <= '" + endDate + "' AND waitinglistareaid = " + QString::number(areaID) + ")";
    return queryDatabase(aQuery, "permanent");
}

QSqlQuery Database::getWaitingListSizeEntries(QString startDate, QString endDate, int areaID)
{
    QString aQuery = "SELECT datechangednumpatients, numpatients FROM "
                     "WHERE (datetime(datechangednumpatients) >= '" + startDate + "' AND datetime(datechangednumpatients) <= '" + endDate + "' AND waitinglistareaid = " + QString::number(areaID) + ")";
    return queryDatabase(aQuery, "permanent");
}

QSqlQuery Database::isLoginValid(QString username, QString password) //USE A DIFFERENT NAME IN THIS CLASS
{
    QString aQuery = "SELECT username FROM users WHERE (username = '" + username + "' AND password = '" + password + "')";
    return queryDatabase(aQuery, "permanent");
}

QSqlQuery Database::getUserType(QString username)
{
    QString aQuery = "SELECT usertype FROM (SELECT * FROM users JOIN usertypes ON (users.usertypeid = usertypes.usertypeid)) WHERE username = '" + username + "'";
    return queryDatabase(aQuery, "permanent");
}

//for all user types
void Database::addUser(QString username, QString password, QString userType)
{
    int userTypeID = getUserTypeID(userType); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?

    QString aQuery = "INSERT INTO users (username, password, userTypeid) VALUES ('" + username + "', '" + password + "', " + QString::number(userTypeID) + ")";
    updateDatabase(aQuery, "permanent");
}

void Database::addFacility(QString name, int x, int y, int areaID, int facilityID, QString facilityType)
{
    int facilityTypeID = getFacilityTypeID(facilityType);
    qDebug() << "addFacility: type id " << facilityTypeID;
    QString aQuery = "INSERT INTO facility (facilityid, areaid, name, x, y, facilitytypeid) VALUES (" + QString::number(facilityID) + ", " +  QString::number(areaID) + ", '" + name + "', " +  QString::number(x) + ", " + QString::number(y) + ", " + QString::number(facilityTypeID) + ")";
    qDebug() << "addFacility query: " << aQuery;

    updateDatabase(aQuery, "temporary");

    if (facilityType == "Hospital")
    {

        aQuery = "INSERT INTO hospital (hospitalid) VALUES (" + QString::number(facilityID) + ")";
        qDebug() << "addFacility query (hospital): " << aQuery;
        updateDatabase(aQuery, "temporary");
    }
}

int Database::getUserTypeID(QString userType)
{
    QString aQuery = "SELECT usertypeid FROM usertypes WHERE userType = '" + userType +"'";
    QSqlQuery queryPermanent = queryDatabase(aQuery, "permanent");

    int userTypeID = getID(queryPermanent);
    return userTypeID;
}
int Database::getID(QSqlQuery queryTemporary)
{
    int ID = -1;
    bool okay;
    while(queryTemporary.next())
    {
        ID = queryTemporary.value(0).toInt(&okay); //*********************ADD CHECKS HERE AND TO THE FUNCTIONS THAT USE THEM
        if(!okay)
        {
            qDebug () << "Conversion to int failed in the database class";
        }
    }
    return ID;
}

int Database::getFacilityTypeID(QString facilityType)
{
    QString aQuery = "SELECT facilitytypeid FROM facilitytypes WHERE facilitytype = '" + facilityType + "'";
    QSqlQuery queryTemporary = queryDatabase(aQuery, "temporary");

    int facilityTypeID = getID(queryTemporary);
    return facilityTypeID;
}

QString Database::getType(QSqlQuery queryTemporary)
{
    QString type;

    while(queryTemporary.next())
    {
        type = queryTemporary.value(0).toString();
        qDebug () << "Get Type " <<type;
    }
    return type;
}

QSqlQuery Database::getCareType(int careType) //returns a string
{
    QString aQuery = "SELECT caretype FROM caretypes WHERE caretypeid = " + careType;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getCareTypeID(QString careType) //returns an int
{
    QString aQuery = "SELECT caretypeid FROM caretypes WHERE caretype = '" + careType +"'";
    return queryDatabase(aQuery, "temporary");
}

void Database::clearPatientsOnAreaWaitingList(int area)
{
    QString aQuery = "DELETE FROM waitinglistentries WHERE areaid = " + area;
    updateDatabase(aQuery, "temporary");
}

QSqlQuery Database::isInpatient(QString hcn)
{
    QString aQuery = "SELECT inpatienthealthcarenumber FROM inpatient WHERE inpatienthealthcarenumber = '" + hcn + "'";
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getCurrentFacilityForPatient(QString hcn)
{
    QString aQuery = "SELECT currentFacilityid FROM inpatient WHERE inpatienthealthcarenumber = '" + hcn + "'";
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getPatientDateAdmitted(QString hcn)
{
    QString aQuery = "SELECT dateAdmittedToFacility FROM inpatient WHERE inpatienthealthcarenumber = '" + hcn + "'";
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getPatientDateAdded(QString hcn, int areaID)
{
    QString aQuery = "SELECT dateAddedToList FROM waitinglistentries WHERE (healthcarenumber = '" + hcn + "' AND areaid = " + QString::number(areaID) + ")";
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::facilityExists(int facilityID)
{
    QString aQuery = "SELECT facilityid FROM facility WHERE facilityid = " + QString::number(facilityID);
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getTotalLTCBeds(int facilityID)
{
    QString aQuery = "SELECT totalBeds FROM (SELECT * FROM facility WHERE facilityid NOT IN (SELECT hospitalid FROM hospital)) WHERE facilityid = " + QString::number(facilityID);
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getNumLTCBedsOccupied(int facilityID)
{
    QString aQuery = "SELECT numBedsOccupied FROM (SELECT * FROM facility WHERE facilityid NOT IN (SELECT hospitalid FROM hospital)) WHERE facilityid = " + QString::number(facilityID);
    return queryDatabase(aQuery, "temporary");
}

void Database::clearPatientsAtFacility(int facilityID)
{
    //remove all inpatients at that facility
    QString aQuery = "DELETE FROM inpatient WHERE currentFacilityid = " + facilityID;
    updateDatabase(aQuery, "temporary");
    //clear beds
    QSqlQuery facilityTypeQueryResult = getFacilityType(facilityID);
    QString facilityType = getType(facilityTypeQueryResult);
    if (facilityType == "Hospital")
    {
        aQuery = "UPDATE hospital SET numACBedsOccupied = 0 WHERE (hospitalid = " + QString::number(facilityID) + ")";
        updateDatabase(aQuery, "temporary");
        aQuery = "UPDATE hospital SET numCCCBedsOccupied = 0 WHERE (hospitalid = " + QString::number(facilityID) + ")";
        updateDatabase(aQuery, "temporary");
        aQuery = "UPDATE facility SET numBedsOccupied = 0 WHERE (facilityid = " + QString::number(facilityID) + ")";
        updateDatabase(aQuery, "temporary");
    }
    else if (facilityType == "Nursing Home")
    {
        aQuery = "UPDATE facility SET numBedsOccupied = 0 WHERE (facilityid = " + QString::number(facilityID) + ")";
        updateDatabase(aQuery, "temporary");
    }
}

bool Database::isMyArea(int areaID)
{
    QSqlQuery anAreaIDQuery = getAreaForFacility(myFacilityID);
    int anAreaID = getID(anAreaIDQuery);
    if (anAreaID == areaID)
    {
        return true;
    }
    return false;
}
