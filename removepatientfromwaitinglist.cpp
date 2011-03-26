/********
  CLASS NAME: RemovePatientToWaitingList
  PURPOSE: To display a form for the user to patient a patient to waiting list. Then it will collect the data from the gui and pass it to the data storage classes
  TRACEABILITY: This class traces back to the RemovePatientToWaitingListControl class from Deliverable 2

  CREATED BY: Nisrin Abou-Seido
  LAST MODIFIED: March 20, 2011

***********/

#include "removepatientfromwaitinglist.h"
#include "ui_removepatientfromwaitinglist.h"

RemovePatientFromWaitingList::RemovePatientFromWaitingList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemovePatientFromWaitingList)
{
    ui->setupUi(this);
    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));
}

RemovePatientFromWaitingList::~RemovePatientFromWaitingList()
{
    delete ui;
}

void RemovePatientFromWaitingList::clickedOK()
{
    //get data from the GUI
    QString patientName;

    //request from the data storage classes that a patient be removed from a waiting list

    //close the form window


    close();

}
