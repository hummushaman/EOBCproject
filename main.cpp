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

    DataStorage::myFacilityID = settings.value("id").toInt();
    DataStorage::myFacilityIPaddress = settings.value("IPaddress").toString();

    settings.endArray();

   QMessageBox msgbox;
    //msgbox.setText("This facility's information:\nID: "+ QString::number(DataStorage::myFacilityID) + "\nIPaddress: " + DataStorage::myFacilityIPaddress);
   // msgbox.exec();



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


    return a.exec();
}
