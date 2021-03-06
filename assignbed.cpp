/*Class name: AssignBed
  Purpose: To display a form for the user to assign a patient to a bed. Then it will collect the data from the gui and pass it to the data storage classes
  Traceability: This class traces back to the AssignBedControl from Deliverable 2*/

/*Created by: Nisrin Abou-Seido*/


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



    //populate facilities combo box
    //only display nursing homes. Patients are being assigned from a waiting list. Therefore, they only require LTC.

    if(DataStorage::currentUserType== "FACILITY")
    {
        QString facilName = DataStorage::getFacilityName(DataStorage::myFacilityID);

        QString facilType = DataStorage::getFacilityType(DataStorage::myFacilityID);

        if(facilType == "Nursing Home")
             ui->comboBox_facilities->addItem(facilName);
        else
        {
            QMessageBox msgbox;
            msgbox.setText("As a facility staff at a hospital, you do not have permission to assign patients to a bed.");
            msgbox.exec();
        }



    }
    else
    {

        QVector<int> facilities = DataStorage::getAllFacilities();
        for(int i=0; i< facilities.size();i++)
        {
            QString facilName = DataStorage::getFacilityName(facilities.at(i));
            QString facilType = DataStorage::getFacilityType(facilities.at(i));

            if(facilType == "Nursing Home")
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
    int areaNum = DataStorage::getAreaForFacility(facilid);

    if(ret == QMessageBox::Ok)
    {
        //make sure that there are enough beds of the type that the patient requires.
        int freeLTCbeds = DataStorage::getTotalNumBeds(facilid) - DataStorage::getTotalNumBedsOccupied(facilid);

        if(freeLTCbeds > 0)
        {

            bool remote = true;
            if(facilid == DataStorage::myFacilityID)
                remote = false;

            QDateTime date = QDateTime::currentDateTime();
            QString dateAdmitted = date.toString("yyyy-MM-ddThh:mm:ss");

            QString dateAdded = DataStorage::getPatientDateAdded(patientHCN,areaNum);

            //call assignPatientToBed from datastorage class
            DataStorage::assignPatientToBed(facilid, patientHCN,areaNum,dateAdmitted);

            //call XMLGenerator
            QString operation = "Add";
            QString message = xmlgenerator::patientOperationXML(operation,patientHCN,facilid, areaNum, remote, dateAdded, dateAdmitted, firstname, lastname, DataStorage::getCareType("LTC"), DataStorage::getCareType("LTC"));


            if(remote == false)
            {
               MessageControl::sendMessageToAll(message);
               MessageControl::sendMessage(message,DataStorage::myFacilityID);
           }
            else
                MessageControl::sendMessage(message,facilid);



            close(); //if user clicks Cancel, we do *not* close the form
        }
        else
        {
            QMessageBox msgBox2;
            msgBox2.setText("There are no empty beds at this facility. Please select another facility.");
            msgBox2.exec();
        }
    }
}
void AssignBed::displayClicked()
{

    ui->listWidget_patients->clear();

    QString facilname = ui->comboBox_facilities->currentText();

    int facilID = DataStorage::getFacilityID(facilname);

    int areaid = DataStorage::getAreaForFacility(facilID);
    QString areaname = DataStorage::getAreaName(areaid);

    QVector<Patient> patients = DataStorage::getWaitingListPatients(areaid);

    for(int i=0; i< patients.size();i++)
    {
        QString patientname = patients[i].getHCN();
        ui->listWidget_patients->addItem(patientname);

    }

}
