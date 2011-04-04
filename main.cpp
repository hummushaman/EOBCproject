/********
  CLASS NAME: Main
  PURPOSE: Starts up the system. Displays the login form to the user.

  TRACEABILITY: This class traces back to..

  CREATED BY: Nisrin Abou-Seido
  LAST MODIFIED: March 20, 2011

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
    w->show();



    QSettings settings("JNFconfig"); // opens the configuration file. File should be located in: home/<userfolder>/<yourusername>/.config
    //read configuration file

    //get the database path
    QString dbPath =  settings.value("db_filepath").toString();


    //get myFacilityID and IP address

    settings.beginReadArray("myFacility");

    DataStorage::myFacilityID= settings.value("id").toInt();
    DataStorage::myFacilityIPaddress= settings.value("IPaddress").toString();

    settings.endArray();


    //initializa the Message control which listens for incoming messages
    MessageControl* messageControl = new MessageControl();



   //pass "connection handle" to the Database class
   //handle errors if database connection fails
   //check that tables exist
   //close database connection
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "permanent");
        QMessageBox error;
        db.setDatabaseName("/home/4user3/jpowers3/eobc/database.db");
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
        }
    }


    //qDebug()<<xmlgenerator::patientOperationXML("Add","2343",3,4,true,"March 4, 2010","March 5, 2010","Paula","Moo",1,2);

    //qDebug()<<"bop";

    //qDebug()<<xmlgenerator::rebuild();
    //qDebug()<<xmlgenerator::rebuildResponse();
    qDebug()<<xmlgenerator::addFacility(3,1,34,45,5,6,8,"Homeland",true,"Hospital");
    qDebug()<<xmlgenerator::addBeds(4,3,1,0,0,true);



    return a.exec();
}
