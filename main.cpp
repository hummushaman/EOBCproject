/********
  CLASS NAME: Main
  PURPOSE: Starts up the system. Displays the login form to the user.Gets information from the config file

  TRACEABILITY: Control class

  CREATED BY: Nisrin Abou-Seido

***********/


#include <QtGui/QApplication>
#include "login.h"

#include <iostream>

#include "eobcproject.h"
#include "messagecontrol.h"
#include "QDebug"
#include "xmlgenerator.h"
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

            //call Database constructor
            Database::Initialize();
            w->show();
        }
    }


    //DataStorage::populateTemporaryDatabase();

    QString message = xmlgenerator::rebuild();
    MessageControl::sendMessageToAll(message);


    //qDebug()<<xmlgenerator::rebuildResponse();
    //qDebug()<<xmlgenerator::addFacility(3,1,34,45,5,6,8,"Homeland",true,"Hospital");
    //qDebug()<<xmlgenerator::addBeds(4,3,1,0,0,true);


/*
    DataStorage::addFacility("The JNF hospital",400,400,3,3,"Hospital");
    DataStorage::addFacility("CHEO", 56, 45, 3, 23, "Hospital");
    DataStorage::addFacility("General Hospital", 70, 80, 2, 20, "Hospital");
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
    DataStorage::addPatientToWaitingList("14","Blob", "Smith",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("15","Bojb", "Smith",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("16","Boob", "Smith",2,"110112T11:33:54");
    DataStorage::addPatientToWaitingList("17","Bobo", "Smith",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("18","Boib", "Smith",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("19","Bobi", "Smith",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("20","Boub", "Smith",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("21","Boxb", "Smith",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("22","Bqob", "Smith",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("23","Bowb", "Smith",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("24","Boqb", "Smith",2,"100122T11:33:54");
    DataStorage::addPatientToWaitingList("25","Bo", "Smith",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("26","ob", "Smith",2,"120112T11:33:54");
    DataStorage::addPatientToWaitingList("27","o", "Smith",2,"120112T11:33:54");

    DataStorage::assignPatientToBed(3,"12",1,"120112T11:33:54");
    DataStorage::assignPatientToBed(3,"13",1,"120112T11:33:54");
    DataStorage::assignPatientToBed(3,"14",1,"120112T11:33:54");*/


    return a.exec();
}
