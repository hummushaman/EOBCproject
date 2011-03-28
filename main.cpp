/********
  CLASS NAME: Main
  PURPOSE: Starts up the system. Displays the login form to the user.

  TRACEABILITY: This class traces back to..

  CREATED BY: Nisrin Abou-Seido
  LAST MODIFIED: March 20, 2011

***********/


#include <QtGui/QApplication>
#include "login.h"


#include "eobcproject.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();

    //read configuration file
    //should include:
    //  database path
    //  myFacilityID
    //  IP addresses of other facilities ( mapped to FacilityID's)
    //


    //connect to the database
    //pass "connection handle" to the Database class
        //handle errors if database connection fails
                //check that tables exist


    //initialize DataStorage object

    //storage = DataStorage();






   // std::cout << "Hello";



    //close database connection
    return a.exec();
}
