#include "database.h"
//ADD ERROR CHECKING->AT LEAST MIGHT HAVE TO ADD GETRECORD() FOR FLOAT, GET RECORD FOR VECTOR (MAYBE BUT INTO THE DATASTORAGE CLASS!!!)
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

}

void Database::removePatientFromBed(int facilityID, QString HCN, QString dateRemoved)
{
    removePatientFromBed("temporary", facilityID, HCN, dateRemoved);
    if (facilityID == myFacilityID)
    {
        removePatientFromBed("permanent", facilityID, HCN, dateRemoved);
    }
}

void Database::removePatientFromBed(QString databaseConnection, int facilityID, QString HCN, QString dateRemoved)
{
    /*QSqlQuery query(QSqlDatabase::database(databaseConnection));

    QString facilityType = getFacilityType(facilityID);
    if (facilityType == "Hospital")
    {
    }*/

    /*
--****REMOVE PATIENT FROM BED (int facilityID, int patientID, QDateTime aDateTime)**** Assumption: patient is an inpatient
--FIND THEIR FACILTIY

--do not like relying on codes; easier to see the string

QString facilityType = getFacilityType(int facilityID);

if (facilityType == "Hospital")
{
   SELECT care
   FROM careTypes JOIN ON
       (SELECT currentCareType
       FROM inpatient
       WHERE id = patientID)
   WHERE id = currentCareType;

   if (care == "AC")
   {
       updateNumberOfACBedsOccupied(facilityID, -1);
       updateTotalNumberOfBedsOccupied(facilityID, -1, false);

   }
   else if (care == "CCC")
   {
       updateNumberOfCCCBedsOccupied(facilityID, -1)
       updateTotalNumberOfBedsOccupied(facilityID, -1, false);
   }

}
else if (facilityType == "Nursing Home")
{
   updateTotalNumberOfBedsOccupied(facilityID, -1, true);
}

DELETE FROM inpatient WHERE (id = patientID);
     */



}

void Database::assignPatientToBed(int facilityID, QString HCN)
{

}

void Database::addBeds(int facilityID, int numBeds, QString bedType)
{

}

void Database::removePatientFromWaitingList(int areaID, QString HCN)
{

}
//inpatient version
void Database::addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded, int currentFacility, int currentCareType)
{

}
//outpatient version
void Database::addPatientToWaitingList(QString HCN, QString firstName, QString lastName, int areaID, QString dateAdded)
{

}

QVector<int> Database::getAllAreas()
{
    //REDUNDANT CODE****************************
    QVector<int> areaID = QVector<int>();
    QSqlQuery queryTemporary(QSqlDatabase::database("temporary"));
    QString aQuery = "SELECT areaid FROM area";
    queryTemporary.exec(aQuery);
    while (queryTemporary.next())
    {
        areaID.append(queryTemporary.value(0).toInt());
    }
    return areaID;
}

QString Database::getAreaName(int areaID)
{
    QString aQuery = "SELECT name FROM area WHERE areaid = " + areaID;
    QString areaName = getOneRecord(aQuery);
    return areaName;
}

int Database::getAreaID(QString areaname)
{
    QString aQuery = "SELECT areaid FROM area WHERE name =" + areaname;
    int areaID = getOneRecord(aQuery).toInt(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    return areaID;
}

QVector<int> Database::getAllFacilitiesInArea(int areaID)
{
    //REDUNDANT CODE******************************************
    QVector<int> facilityID = QVector<int>();
    QSqlQuery queryTemporary(QSqlDatabase::database("temporary"));
    QString aQuery = "SELECT facilityid FROM facility WHERE areaid = " + areaID;
    queryTemporary.exec(aQuery);
    while (queryTemporary.next())
    {
        facilityID.append(queryTemporary.value(0).toInt());
    }
    return facilityID;
}

int Database::getAreaForFacility(int facilityID)
{

}

QVector<int> Database::getAllFacilities()
{
    //REDUNDANT CODE******************************************
    QVector<int> facilityID = QVector<int>();
    QSqlQuery queryTemporary(QSqlDatabase::database("temporary"));
    QString aQuery = "SELECT facilityid FROM facility";
    queryTemporary.exec(aQuery);
    while (queryTemporary.next())
    {
        facilityID.append(queryTemporary.value(0).toInt());
    }
    return facilityID;
}

QString Database::getFacilityName(int facilityID)
{
    QString aQuery = "SELECT name FROM facility WHERE facilityid = " + facilityID;
    QString facilityName = getOneRecord(aQuery);
    return facilityName;
}

float Database::getFacilityX(int facilityID)
{
    QString aQuery = "SELECT x FROM facility WHERE facilityid = " + facilityID;
    float facilityX = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    return facilityX;
}

float Database::getFacilityY(int facilityID)
{
    QString aQuery = "SELECT y FROM facility WHERE facilityid = " + facilityID;
    float facilityY = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    return facilityY;
}

float Database::getTotalACBeds(int facilityID)
{
    QString aQuery = "SELECT totalACBeds FROM hospital WHERE hospitalid = " + facilityID;
    float totalACBeds = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    return totalACBeds;
}

float Database::getNumACBedsOccupied(int facilityID)
{
    QString aQuery = "SELECT numACBedsOccupied FROM hospital WHERE hospitalid = " + facilityID;
    float numACBedsOccupied = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    return numACBedsOccupied;
}

float Database::getTotalCCCBeds(int facilityID)
{
    QString aQuery = "SELECT totalCCCBeds FROM hospital WHERE hospitalid = " + facilityID;
    float totalCCCBeds = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    return totalCCCBeds;
}

float Database::getNumCCCBedsOccupied(int facilityID)
{
    QString aQuery = "SELECT numCCCBedsOccupied FROM hospital WHERE hospitalid = " + facilityID;
    float numCCCBedsOccupied = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    return numCCCBedsOccupied;
}

float Database::getTotalNumBeds(int facilityID)
{
    QString aQuery = "SELECT totalBeds FROM facility WHERE facilityid = " + facilityID;
    float totalNumBeds = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    return totalNumBeds;
}

float Database::getTotalNumBedsOccupied(int facilityID)
{
    QString aQuery = "SELECT numBedsOccupied FROM facility WHERE facilityid = " + facilityID;
    float totalNumBedsOccupied = getOneRecord(aQuery).toFloat(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    return totalNumBedsOccupied;
}

QVector<Patient*> Database::getPatientsAtFacility(int facilityID)
{

}

QString Database::getPatientFirstName(QString patientHCN)
{
    QString aQuery = "SELECT firstname FROM patient WHERE healthcarenumber = " + patientHCN;
    QString lastname = getOneRecord(aQuery);
    return lastname;
}

QString Database::getPatientLastName(QString patientHCN)
{
    QString aQuery = "SELECT lastname FROM patient WHERE healthcarenumber = " + patientHCN;
    QString lastname = getOneRecord(aQuery);
    return lastname;
}

//"Hospital" or "Nursing Home"
QString Database::getFacilityType(int facilityID)
{
    QString aQuery = "SELECT facilitytype FROM"
                        "(SELECT facilitytype FROM facility JOIN ON facilitytypes WHERE facility.facilitytypeid = facilitytypes.facilitytypeid)"
                        "WHERE facilityid = " + facilityID;

    QString facilityType = getOneRecord(aQuery);
    return facilityType;
}

QString Database::getOneRecord(QString aQuery)
{
    QSqlQuery queryTemporary(QSqlDatabase::database("temporary"));
    queryTemporary.exec(aQuery);
    QString queryResult;
    while(queryTemporary.next())
    {
        queryResult = queryTemporary.value(0).toString();
    }
    return queryResult;
}

QVector<OccupancyRateEntry> Database::getOccupancyRateEntries(QString startDate, QString endDate, int careType, int facilityID)
{

}

int Database::getFacilityID(QString name)
{
    QString aQuery = "SELECT facilityid FROM facility WHERE name = " + name;
    int facilityID = getOneRecord(aQuery).toInt(); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    return facilityID;
}

QVector<Patient*> Database::getWaitingListPatients(int areaID)
{
   //QString aQuery = "SELECT facilityid FROM facility WHERE name = " + patientHCN;
    //int facilityID = getOneRecord(aQuery); //POTENTIAL PROBLEM FOR CONVERSION: WHAT ABOUT IF IT'S A NULL STRING?
    //return facilityID;
}

int Database::getWaitingListSize(int areaID)
{

}

QVector<WaitTimesEntry> Database::getWaitTimesEntries(QString startDate, QString endDate, int areaID)
{

}

QVector<NumPatientsEntry> Database::getWaitingListSizeEntries(QString startDate, QString endDate, int areaID)
{

}

bool Database::isLoginValid(QString username, QString password)
{
    //kind of repeated code***************
    QString aQuery = "SELECT * FROM users WHERE (username = " + username + "AND password = " + password + ")";
    QSqlQuery queryTemporary(QSqlDatabase::database("temporary"));
    queryTemporary.exec(aQuery);
    if (queryTemporary.size() == 1) //there shouldn't be the same user...
    {
        return true;
    }
    return false;
}

QString Database::getUserType(QString username)
{
    //QString aQuery = "SELECT

}

int Database::getUserFacility(QString username)
{

}

int Database::requestMismatch(int currentCareType, int requiredCareType, int areaID)
{

}
//for system administrators and LHIN staff
void Database::addUser(QString username, QString password, int userType)
{

}
//facility staff
void Database::addUser(QString username, QString password, int userType, int facilityID)
{

}

void Database::addFacility(QString name, float x, float y)
{

}





