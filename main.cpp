/********
***********/


#include <QtGui/QApplication>
#include "login.h"

#include "eobcproject.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //read configuration file
    //should include:
    //  database path
    //  myFacilityID
    //  IP addresses of other facilities ( mapped to FacilityID's)
    //
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
    Login w;
    w.show();


    //pass "connection handle" to the Database class
    //handle errors if database connection fails
    //check that tables exist
    //close database connection
    return a.exec();
}
