/********
  CLASS NAME: AddFacility
  PURPOSE: To display a form for the system administrator to add a user to a facility. Then it will collect the data from the gui and pass it to the data storage classes
  TRACEABILITY: This class traces back to the AddUserControl class from Deliverable 2

  CREATED BY: Nisrin Abou-Seido
  LAST MODIFIED: March 20, 2011

***********/

#include "adduser.h"
#include "ui_adduser.h"

AddUser::AddUser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);
    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));
}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::clickedOK()
{
    //close();

}
