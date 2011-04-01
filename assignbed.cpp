/*Class name: AssignBed
  Purpose: To display a form for the user to assign a patient to a bed. Then it will collect the data from the gui and pass it to the data storage classes
  Traceability: This class traces back to the AssignBedControl from Deliverable 2*/

/*Created by: Nisrin Abou-Seido
  Last modified: March 20, 2011*/


#include "assignbed.h"
#include "ui_assignbed.h"

#include "eobcproject.h"

AssignBed::AssignBed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssignBed)
{
    ui->setupUi(this);
    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));
    connect(ui->DisplayButton, SIGNAL(clicked()), this, SLOT(displayClicked()));



    //populate facilities combo box //Shoudl we only show long term care facilities????????

    if(DataStorage::usertype == "FACILITY")
    {
        QString facilName = DataStorage::getFacilityName(DataStorage::myFacilityID);
        ui->comboBox_facilities->addItem(facilName);

    }
    else
    {
        QVector<int> facilities = DataStorage::getAllFacilities();
        for(int i=0; i< facilities.size();i++)
        {
            QString facilName = DataStorage::getFacilityName(facilities.at(i));
           ui->comboBox_facilities->addItem(facilName);
        }
    }
}

AssignBed::~AssignBed()
{
    delete ui;
}

void AssignBed::clickedOK()
{
    //get data from the GUI
    QString patientHCN = ui->listWidget_patients->currentItem()->text();

    //check that the user is sure this is what they want to do.

    QMessageBox msgBox;

    QString firstname = DataStorage::getPatientFirstName(patientHCN);
    QString lastname = DataStorage::getPatientLastName(patientHCN);

    QString facilname = ui->comboBox_facilities->currentText();

    msgBox.setText("You have requested to *assign a bed* to the following patient at facility \" " +facilname+ "\":\n\nHealth Card Number: " + patientHCN +"\nFirst Name: "+ firstname + "\nLast Name: " + lastname);

    msgBox.setInformativeText("Do you want to save and propogate this change?");
    msgBox.setStandardButtons( QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    int facilid = DataStorage::getFacilityID(facilname);

    if(ret == QMessageBox::Ok)
    {   //call removePatientFromBed from datastorage class

        DataStorage::removePatientFromBed(facilid, patientHCN);

        close(); //if user clicks Cancel, we do *not* close the form

    }
}
void AssignBed::displayClicked()
{

    ui->listWidget_patients->clear();

    QString facilname = ui->comboBox_facilities->currentText();

    int facilID = DataStorage::getFacilityID(facilname);

    int areaid = DataStorage::getAreaForFacility(facilID);
    QString areaname = DataStorage::getAreaName(areaid);

    QVector<Patient*> patients = DataStorage::getWaitingListPatients(areaid);

    for(int i=0; i< patients.size();i++)
    {
        QString patientname = patients[i]->getHCN();
        ui->listWidget_patients->addItem(patientname);

    }

}
