/********
  CLASS NAME: RemovePatientToWaitingList
  PURPOSE: To display a form for the user to patient a patient to waiting list. Then it will collect the data from the gui and pass it to the data storage classes
  TRACEABILITY: This class traces back to the RemovePatientToWaitingListControl class from Deliverable 2

  CREATED BY: Nisrin Abou-Seido
  LAST MODIFIED: March 20, 2011

***********/

#include "removepatientfromwaitinglist.h"
#include "ui_removepatientfromwaitinglist.h"

#include"datastorage.h"
#include <QListWidgetItem>

RemovePatientFromWaitingList::RemovePatientFromWaitingList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemovePatientFromWaitingList)
{
    ui->setupUi(this);
    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));

    //CDADcb::CMessage* pMess = (CDADcb::CMessage*)i.value();

    //connect(ui->, SIGNAL(triggered()),this,SLOT(openAddBeds()));
   /*
    int facilID =
    Vector<Patient*> patients = DataStorage::getPatientsAtFacility(facilID);
    if( pMess )
    {
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setFlags( newItem->flags() | Qt::ItemIsUserCheckable );
            newItem->setCheckState(Qt::Unchecked);
            newItem->setText( pMess->name );
            newItem->setData( Qt::UserRole, pMess );
                    ui.messageList->insertItem( ui.messageList->count(), newItem);
    }


    ui->comboBox*/
}

RemovePatientFromWaitingList::~RemovePatientFromWaitingList()
{
    delete ui;
}

void RemovePatientFromWaitingList::displayPatients()
{

}


void RemovePatientFromWaitingList::clickedOK()
{
    //get data from the GUI
    QString patientName;

    //request from the data storage classes that a patient be removed from a waiting list

    //close the form window


    close();

}
