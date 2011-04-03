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
    //permanentDatabase = aDatabaseConnection;
    {
        // temporaryDatabase =
        QSqlDatabase temporaryDatabase = QSqlDatabase::addDatabase("QSQLITE", "temporary");
        temporaryDatabase.setDatabaseName(":memory:");
    }
    //create temporary tables
    QSqlQuery queryTemporary(QSqlDatabase::database("temporary"));
    QSqlQuery queryPermanent(QSqlDatabase::database("permanent"));

    QFile file("/home/4user3/jpowers3/eobc/database.sql");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
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
    /*   qDebug() << "NOW TESTING WHETHER THE INSERT WORKED: ";
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
    }*/
    QSettings settings("JNFconfig"); // opens the configuration file. File should be located in: home/<userfolder>/<yourusername>/.config
    //get myFacilityID
    settings.beginReadArray("myFacility");
    myFacilityID = settings.value("id").toInt();
    settings.endArray();
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
        QString patientCurrentCareQuery = "SELECT currentcaretypeid FROM inpatient WHERE (inpatienthealthcarenumber = " + HCN + ")";
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
    QString deletePatientQuery = "DELETE FROM inpatient WHERE inpatienthealthcarenumber = " + HCN;
    updateDatabase(deletePatientQuery, databaseConnection);
}

void Database::updateNumberOfACBedsOccupied(QString databaseConnection, int facilityID, int amount)
{
    QString aQuery = "SELECT numACBedsOccupied FROM hospital WHERE hospitalid = " + facilityID;
    int numberOfCCCBedsOccupied = getID(aQuery) + amount; //odd function name-> maybe rename to get int

    aQuery = "UPDATE hospital SET numACBedsOccupied = " + QString::number(numberOfCCCBedsOccupied) + " WHERE hospitalid = " + facilityID;
    updateDatabase(aQuery, databaseConnection);

    if (isMyFacility(facilityID) && isPermanentDatabaseConnection(databaseConnection))
    {
        //update log
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
    QString aQuery = "SELECT numCCCBedsOccupied FROM hospital WHERE hospitalid = " + facilityID;
    int numberOfCCCBedsOccupied = getID(aQuery) + amount; //odd function name-> maybe rename to get int

    aQuery = "UPDATE hospital SET numCCCBedsOccupied = " + QString::number(numberOfCCCBedsOccupied) + " WHERE hospitalid = " + facilityID;
    updateDatabase(aQuery, databaseConnection);

    if (isMyFacility(facilityID) && isPermanentDatabaseConnection(databaseConnection))
    {
        //update log
    }
}

void Database::updateTotalNumberOfBedsOccupied(QString databaseConnection, int facilityID, int amount, bool updateLog)
{

    QString aQuery = "SELECT numBedsOccupied FROM facility WHERE facilityid = " + facilityID;
    int totalNumberOfBedsOccupied = getID(aQuery) + amount; //odd function name-> maybe rename to get int

    aQuery = "UPDATE facility SET numBedsOccupied = " + QString::number(totalNumberOfBedsOccupied) + " WHERE facilityid = " + facilityID;
    updateDatabase(aQuery, databaseConnection);

    if (isMyFacility(facilityID) && isPermanentDatabaseConnection(databaseConnection) && updateLog)
    {
        //update log
    }
}

void Database::assignPatientToBed(QString databaseConnection, int facilityID, QString HCN, int areaID, QString dateAssigned) //only applicable to Nursing Home("LTC")
{

    QString currentFacilityQuery = "SELECT currentFacilityid FROM "
                                   "(SELECT * FROM patient JOIN ON inpatient WHERE healthcarenumber = inpatienthealthcarenumber) WHERE heathcarenumber = " + HCN;
    QSqlQuery currentFacilityQueryResult = queryDatabase(currentFacilityQuery, "temporary");

    if (currentFacilityQueryResult.size() == 1) //might not work in SQLite
    {
        int currentFacility = getID(currentFacilityQueryResult);
        removePatientFromBed(databaseConnection, currentFacility, HCN, dateAssigned);
        removePatientFromWaitingList(databaseConnection, areaID, HCN, dateAssigned);
    }
    QSqlQuery facilityTypeQueryResult = getFacilityType(facilityID);
    QString facilityType = getType(facilityTypeQueryResult);

    if (facilityType == "Hospital")
    {
        QString patientCurrentCareQuery = "SELECT currentcaretypeid FROM inpatient WHERE (inpatienthealthcarenumber = " + HCN + ")";
        QSqlQuery patientCurrentCareQueryResult = queryDatabase(patientCurrentCareQuery, "temporary");
        int currentCareTypeID = getID(patientCurrentCareQueryResult);
        QString currentCareType = getType(getCareType(currentCareTypeID));

        if (currentCareType == "AC")
        {
            updateNumberOfACBedsOccupied(databaseConnection, facilityID, 1);
            updateTotalNumberOfBedsOccupied(databaseConnection, facilityID, 1, false);
        }
        else if (currentCareType == "CCC")
        {
            updateNumberOfCCCBedsOccupied(databaseConnection, facilityID, 1);
            updateTotalNumberOfBedsOccupied(databaseConnection, facilityID, 1, false);
        }

    }
    else if (facilityType == "Nursing Home")
    {
        updateTotalNumberOfBedsOccupied(databaseConnection, facilityID, 1, true);
    }
    QString updatePatient = "UPDATE inpatient SET currentfacilityid = " + QString::number(facilityID) + " WHERE inpatienthealthcarenumber =" + HCN;
    updateDatabase(updatePatient, databaseConnection);
    updatePatient = "UPDATE inpatient SET currentfacilityid = 'LTC' WHERE inpatienthealthcarenumber =" + HCN;
    //update the log
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
    QString aQuery = "SELECT totalACBeds FROM hospital WHERE hospitalid = " + facilityID;
    int numberOfACBeds = getID(aQuery) + amount; //odd function name-> maybe rename to get int

    aQuery = "UPDATE hospital SET totalACBeds = " + QString::number(numberOfACBeds) + " WHERE hospitalid = " + facilityID;
    updateDatabase(aQuery, databaseConnection);

    if (isMyFacility(facilityID) && isPermanentDatabaseConnection(databaseConnection))
    {
        //update log
    }
}

void Database::updateNumberOfCCCBeds(QString databaseConnection, int facilityID, int amount)
{
    QString aQuery = "SELECT totalCCCBeds FROM hospital WHERE hospitalid = " + facilityID;
    int numberOfCCCBeds = getID(aQuery) + amount; //odd function name-> maybe rename to get int

    aQuery = "UPDATE hospital SET totalCCCBeds = " + QString::number(numberOfCCCBeds) + " WHERE hospitalid = " + facilityID;
    updateDatabase(aQuery, databaseConnection);
    if (isMyFacility(facilityID) && isPermanentDatabaseConnection(databaseConnection))
    {
        //update log
    }
}

void Database::updateTotalNumberOfBeds(QString databaseConnection, int facilityID, int amount, bool updateLog)
{
    QString aQuery = "SELECT totalBeds FROM facility WHERE facilityid = " + facilityID;
    int totalNumberOfBeds = getID(aQuery) + amount; //odd function name-> maybe rename to get int

    aQuery = "UPDATE facility SET totalBeds = " + QString::number(totalNumberOfBeds) + " WHERE facilityid = " + facilityID;
    updateDatabase(aQuery, databaseConnection);
    if (isMyFacility(facilityID) && isPermanentDatabaseConnection(databaseConnection) && updateLog)
    {
        //update log
    }
}

void Database::removePatientFromWaitingList(int areaID, QString HCN, QString dateRemoved)
{
    removePatientFromWaitingList("temporary", areaID, HCN, dateRemoved);
    //if (//am I a main facility && is this my area?) ************************************
    // {
    //   removePatientFromWaitingList("permanent", areaID, HCN, dateRemoved);
    // }
}
void Database::removePatientFromWaitingList(QString databaseConnection, int areaID, QString HCN, QString dateRemoved)
{
    QString aQuery = "DELETE FROM waitinglistentries WHERE (healthcarenumber = " + HCN + " AND " + "areaid" + areaID + ")";
    updateDatabase(aQuery, databaseConnection);
    //update log! if my facility ***********************
}

//inpatient version: assumed that they are not on this the waiting list && they are already at a facility
void Database::addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded, int currentFacility, QString currentCareType)
{

    addPatientToWaitingList("temporary", HCN, areaID, dateAdded);
    //if (//am I a main facility && is this my area?) ************************************
    // {
    //    addPatientToWaitingList("permanent", HCN, areaID, dateAdded);
    // }

}
//inpatient version: assumed that they are not on this waiting list && they are already at a facility
void Database::addPatientToWaitingList(QString databaseConnection, QString HCN, int areaID, QString dateAdded)
{
    QString aQuery = "INSERT INTO waitinglistentries (heathcardnumber, areaid, dateaddedtolist) VALUES INTO (" + HCN + ", " + areaID + ", " + dateAdded + ")";
    updateDatabase(aQuery, databaseConnection);
    //update log! if my facility ***********************
}

void Database::addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded) //outpatient
{
    addPatientToWaitingList("temporary", HCN, firstName, lastName, areaID, dateAdded);
    //if (//am I a main facility && is this my area?) ************************************
    // {
    //addPatientToWaitingList("permanent", HCN, firstName, lastName, areaID, dateAdded);
    // }
}

//outpatient version: assumed that they are not on the waiting list
void Database::addPatientToWaitingList(QString databaseConnection, QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded)
{
    QString aQuery = "INSERT INTO patient (heathcardnumber, firstname, lastname, requiredcaretype) VALUES INTO (" + HCN + ", " + firstName + ", " + lastName + ", 'LTC')";
    updateDatabase(aQuery, databaseConnection);

    aQuery = "INSERT INTO waitinglistentries (heathcardnumber, areaid, dateaddedtolist) VALUES INTO (" + HCN + ", " + areaID + ", " + dateAdded + ")";
    updateDatabase(aQuery, databaseConnection);
    //update log! if my facility ***********************
}

QSqlQuery Database::getAllAreas()
{
    //REDUNDANT CODE****************************
    //    QVector<int> areaID = QVector<int>();
    //  QSqlQuery queryTemporary(QSqlDatabase::database("temporary"));
    QString aQuery = "SELECT areaid FROM area";
    //queryTemporary.exec(aQuery);
    //while (queryTemporary.next())
    //{
    //  areaID.append(queryTemporary.value(0).toInt());
    //  }
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getAreaName(int areaID)
{
    QString aQuery = "SELECT name FROM area WHERE areaid = " + areaID;
    //QString areaName = getOneRecord(aQuery);
    //return areaName;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getAreaID(QString areaname)
{
    QString aQuery = "SELECT areaid FROM area WHERE name =" + areaname;
    //int areaID = getOneRecord(aQuery).toInt(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    //return areaID;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getAllFacilitiesInArea(int areaID)
{
    //REDUNDANT CODE******************************************
    //QVector<int> facilityID = QVector<int>();
    //QSqlQuery queryTemporary(QSqlDatabase::database("temporary"));
    QString aQuery = "SELECT facilityid FROM facility WHERE areaid = " + areaID;
    // queryTemporary.exec(aQuery);
    //while (queryTemporary.next())
    //{
    //    facilityID.append(queryTemporary.value(0).toInt());
    //
    //return facilityID;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getAreaForFacility(int facilityID)
{
    QString aQuery = "SELECT areaid FROM facility WHERE facilityid = " + facilityID;
    //int areaID = getOneRecord(aQuery).toInt(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    //return areaID;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getAllFacilities()
{
    //REDUNDANT CODE******************************************
    //QVector<int> facilityID = QVector<int>();
    //QSqlQuery queryTemporary(QSqlDatabase::database("temporary"));
    QString aQuery = "SELECT facilityid FROM facility";
    //queryTemporary.exec(aQuery);
    // while (queryTemporary.next())
    //{
    //    facilityID.append(queryTemporary.value(0).toInt());
    //}
    //return facilityID;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getFacilityName(int facilityID)
{
    QString aQuery = "SELECT name FROM facility WHERE facilityid = " + facilityID;
    //QString facilityName = getOneRecord(aQuery);
    // return facilityName;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getFacilityX(int facilityID)
{
    QString aQuery = "SELECT x FROM facility WHERE facilityid = " + facilityID;
    //float facilityX = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    //return facilityX;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getFacilityY(int facilityID)
{
    QString aQuery = "SELECT y FROM facility WHERE facilityid = " + facilityID;
    //float facilityY = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    //return facilityY;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getTotalACBeds(int facilityID)
{
    QString aQuery = "SELECT totalACBeds FROM hospital WHERE hospitalid = " + facilityID;
    //float totalACBeds = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    // return totalACBeds;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getNumACBedsOccupied(int facilityID)
{
    QString aQuery = "SELECT numACBedsOccupied FROM hospital WHERE hospitalid = " + facilityID;
    //float numACBedsOccupied = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    //return numACBedsOccupied;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getTotalCCCBeds(int facilityID)
{
    QString aQuery = "SELECT totalCCCBeds FROM hospital WHERE hospitalid = " + facilityID;
    //float totalCCCBeds = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    //return totalCCCBeds;
    return queryDatabase(aQuery, "temporary");

}

QSqlQuery Database::getNumCCCBedsOccupied(int facilityID)
{
    QString aQuery = "SELECT numCCCBedsOccupied FROM hospital WHERE hospitalid = " + facilityID;
    //float numCCCBedsOccupied = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    //return numCCCBedsOccupied;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getTotalNumBeds(int facilityID)
{
    QString aQuery = "SELECT totalBeds FROM facility WHERE facilityid = " + facilityID;
    //float totalNumBeds = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    //return totalNumBeds;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getTotalNumBedsOccupied(int facilityID)
{
    QString aQuery = "SELECT numBedsOccupied FROM facility WHERE facilityid = " + facilityID;
    //float totalNumBedsOccupied = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    //return totalNumBedsOccupied;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getPatientsAtFacility(int facilityID) //ALL INPATIENTS!!
{
    QString aQuery = "SELECT * FROM inpatient WHERE currentfacilityid =" + facilityID;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getPatientFirstName(QString patientHCN)
{
    QString aQuery = "SELECT firstname FROM patient WHERE healthcarenumber = " + patientHCN;
    //QString lastname = getOneRecord(aQuery);
    //return lastname;
    return queryDatabase(aQuery, "temporary");
}

QSqlQuery Database::getPatientLastName(QString patientHCN)
{
    QString aQuery = "SELECT lastname FROM patient WHERE healthcarenumber = " + patientHCN;
    //QString lastname = getOneRecord(aQuery);
    //return lastname;
    return queryDatabase(aQuery, "temporary");
}

//"Hospital" or "Nursing Home"
QSqlQuery Database::getFacilityType(int facilityID)
{
    QString aQuery = "SELECT facilitytype FROM"
                     "(SELECT facilitytype FROM facility JOIN ON facilitytypes WHERE facility.facilitytypeid = facilitytypes.facilitytypeid)"
                     "WHERE facilityid = " + facilityID;

    //QString facilityType = getOneRecord(aQuery);
    //return facilityType;
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
    QString aQuery = "SELECT facilityid FROM facility WHERE name = " + name;
    //int facilityID = getOneRecord(aQuery).toInt(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    //return facilityID;
    return queryDatabase(aQuery, "temporary");

}

QSqlQuery Database::getWaitingListInpatients(int areaID)
{


}


QSqlQuery Database::getWaitingListOutpatients(int areaID)
{


}

QSqlQuery Database::getWaitingListSize(int areaID) //MAP
{

}

QSqlQuery Database::getOccupancyRateEntries(QString startDate, QString endDate, int careType, int facilityID) //REPORT
{

}

QSqlQuery Database::getWaitTimesEntries(QString startDate, QString endDate, int areaID) //REPORT
{

}

QSqlQuery Database::getWaitingListSizeEntries(QString startDate, QString endDate, int areaID) //REPORT
{

}

QSqlQuery Database::isLoginValid(QString username, QString password) //USE A DIFFERENT NAME IN THIS CLASS
{
    //kind of repeated code***************
    QString aQuery = "SELECT * FROM users WHERE (username = " + username + "AND password = " + password + ")";
    //QSqlQuery queryTemporary(QSqlDatabase::database("temporary"));
    //queryTemporary.exec(aQuery);
    // if (queryTemporary.size() == 1) //there shouldn't be the same user...
    //{
    //    return true;
    // }
    //return false;
    return queryDatabase(aQuery, "permanent");
}

QSqlQuery Database::getUserType(QString username)
{
    QString aQuery = "SELECT usertype FROM (SELECT * FROM users JOIN ON usertypes WHERE (users.usertypeid = usertypes.usertypeid)) WHERE username = " + username;
    //QString userType = getOneRecord(aQuery);
    //return userType;
    return queryDatabase(aQuery, "permanent");
}


QSqlQuery Database::requestMismatch(int currentCareType, int requiredCareType, int areaID) //REPORT
{

}

//for all user types
void Database::addUser(QString username, QString password, QString userType)
{
    int userTypeID = getUserTypeID(username, password, userType); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?

    QString aQuery = "INSERT INTO users (username, password, userTypeid) VALUES (" + username + ", " + password + ", " + userTypeID + ")";
    updateDatabase(aQuery, "permanent");
}

void Database::addFacility(QString name, float x, float y, int areaID, int facilityID, QString facilityType)
{
    //DEFAULTING ALL NUMERICAL VALUES TO 0 (AUTOMATICAL?)
    int facilityTypeID = getFacilityTypeID(facilityType);

    QString aQuery = "INSERT INTO facility (facilityid, areaid, name, x, y, facilitytypeid) VALUES (" + QString::number(facilityID) + ", " +  areaID + ", " + name + ", " + x + ", " + y + ", " + facilityTypeID + ")";
    updateDatabase(aQuery, "temporary");

    if (facilityType == "Hospital")
    {
        aQuery = "INSERT INTO hospital (hospitalid) VALUES (" + QString::number(facilityID) + ")";
        updateDatabase(aQuery, "temporary");
    }
}

int Database::getUserTypeID(QString username, QString password, QString userType)
{
    QString aQuery = "SELECT usertypeid FROM usertypes WHERE userType = " + userType;
    QSqlQuery queryTemporary = queryDatabase(aQuery, "permanent");

    int userTypeID = getID(queryTemporary);
    return userTypeID;
}
int Database::getID(QSqlQuery queryTemporary)
{
    int ID;

    while(queryTemporary.next())
    {
        ID = queryTemporary.value(0).toInt();
    }
    return ID;
}

int Database::getFacilityTypeID(QString facilityType)
{
    QString aQuery = "SELECT facilitytypeid FROM facilitytypes WHERE facilitytype = " + facilityType;
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
    QString aQuery = "SELECT caretypeid FROM caretypes WHERE caretype = " + careType;
    return queryDatabase(aQuery, "temporary");
}
