/********
***********/


#include <QtGui/QApplication>
#include "login.h"

#include <iostream>

#include "eobcproject.h"
#include "messagecontrol.h"
using namespace std;


/*******make sure the file JNFconfig.conf is in home/<userfolder>/<yourusername>/.config directory*************/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login *w = new Login();


    QSettings settings("JNFconfig"); // opens the configuration file. File should be located in: home/<userfolder>/<yourusername>/.config

    //get the database path
    settings.beginGroup("database");
    QString dbPath =  settings.value("db_filepath").toString();
    qDebug() << dbPath;

    settings.endGroup();

    //get myFacilityID and IP address and whether facility is a main facility

    settings.beginGroup("myfacility");

    DataStorage::myFacilityID= settings.value("id").toInt();
    DataStorage::myFacilityIPaddress= settings.value("IPaddress").toString();
    QString is_main= settings.value("isMain").toString();

    settings.endGroup();

    qDebug() << is_main;
    if(is_main == "true")
        DataStorage::isMain = true;
    else
        DataStorage::isMain = false;


    qDebug() << DataStorage::isMain;
    qDebug() << DataStorage::isMainFacility();


    //initialize the Message control which listens for incoming messages
    MessageControl* messageControl = new MessageControl();

    //pass "connection handle" to the Database class
    //handle errors if database connection fails
    //check that tables exist
    //close database connection
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "permanent");
        QMessageBox error;
        db.setDatabaseName(dbPath);
        //connect to the database
        bool isOpen = db.open();
        if (!isOpen){
            //handle the errors if the database connection fails
            error.setText("Connection failed");
            error.exec();
        }else {
            //pass the connection to the Database class through the DataStorage class
            //also need to check that tables exist
            Database::Initialize();
            w->show();
        }
    }

    return a.exec();
}
