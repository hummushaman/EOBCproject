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

    connect(ui->DisplayButton,SIGNAL(clicked()),this,SLOT(displayPatients()));


    //populate area combo box
    QVector<int> areas = DataStorage::getAllAreas();

    for(int i=0; i< areas.size();i++)
    {
        QString areaname = DataStorage::getAreaName(areas[i]);
        ui->comboBox_areas->addItem(areaname);

    }
}

RemovePatientFromWaitingList::~RemovePatientFromWaitingList()
{
    delete ui;
}

void RemovePatientFromWaitingList::displayPatients()
{

    ui->listWidget_patients->clear();

    QString areaname = ui->comboBox_areas->currentText();

    int areaID = DataStorage::getAreaID(areaname);

    QVector<Patient*> patients = DataStorage::getWaitingListPatients(areaID);

    for(int i;i<patients.size();i++)
    {
        ui->listWidget_patients->addItem(patients[i]->getHCN());



    //attempt to add patients to the list as objects *is not working*


        /*if( patients[i])
        {
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setFlags( newItem->flags() | Qt::ItemIsUserCheckable );
            newItem->setCheckState(Qt::Unchecked);

            newItem->setText( patients[i]->getFirstname() + " " + patients[i]->getLastname() );


            newItem->setData( Qt::UserRole, patients[i] );
            ui->listWidget_patients->insertItem( ui->listWidget_patients->count(), newItem);
        }*/
    }
   // QObject * obj = qvariant_cast<QObject *>(item->data(Qt::UserRole));
    // from QObject* to myClass*
    //myClass * lmyClass = qobject_cast<myClass *>(obj);


}

void RemovePatientFromWaitingList::clickedOK()
{
    //get data from the GUI
    QString patientHCN = ui->listWidget_patients->currentItem()->text();

    //check that the user is sure this is what they want to do.

    QMessageBox msgBox;

    QString firstname = DataStorage::getPatientFirstName(patientHCN);
    QString lastname = DataStorage::getPatientLastName(patientHCN);

    QString areaname = ui->comboBox_areas->currentText();

    msgBox.setText("You have requested to *remove* the following patient from the waiting list for " +areaname+ ":\n\nHealth Card Number: " + patientHCN +"\nFirst Name: "+ firstname + "\nLast Name: " + lastname);

    msgBox.setInformativeText("Do you want to save and propogate this change?");
    msgBox.setStandardButtons( QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    int areaid = DataStorage::getAreaID(areaname);

    if(ret == QMessageBox::Ok)
    {   //call removePatientFromWaitingList from datastorage class

        DataStorage::removePatientFromWaitingList(areaid, patientHCN);

        close(); //if user clicks Cancel, we do *not* close the form

    }

}
