
#include "viewfacility.h"
#include "ui_viewfacility.h"



ViewFacility::ViewFacility(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewFacility)
{
    ui->setupUi(this);

    connect(ui->DisplayButton, SIGNAL(clicked()),this,SLOT(displayInformation()));


    QVector<int> facilities = DataStorage::getAllFacilities();
    for(int i=0; i< facilities.size();i++)
     {
            QString facilName = DataStorage::getFacilityName(facilities.at(i));
            ui->comboBox_facilities->addItem(facilName);
     }

}

ViewFacility::~ViewFacility()
{
    delete ui;
}


void ViewFacility::displayInformation()
{
    QString facilName = ui->comboBox_facilities->currentText();

    int facilID = DataStorage::getFacilityID(facilName);

    QVector<Inpatient> patients = DataStorage::getPatientsAtFacility(facilID);


    for(int i= 0; i<patients.size();i++)
    {

        QString firstname = patients[i].getFirstname();
        QString lastname = patients[i].getLastname();
        ui->listWidget_patients->addItem(firstname + " " + lastname + " ("+ patients[i].getHCN() + ")");

    }


    //get occupancy rate information

    /***********change data storage class so that the following functions actually return something!!*********/

    float totalNumBeds = DataStorage::getTotalNumBeds(facilID);
    float totalBedsOccupied = DataStorage::getTotalNumBedsOccupied(facilID);

    float occRate = totalBedsOccupied/ totalNumBeds * 100;

    int totalACBeds = DataStorage::getTotalACBeds(facilID);
    int totalCCCBeds = DataStorage::getTotalCCCBeds(facilID);

    int numCCCoccupied = DataStorage::getNumCCCBedsOccupied(facilID);
    int numACoccupied = DataStorage::getNumACBedsOccupied(facilID);

    //print to the labels
    //use formatting to limit the occrate to 2 decimal spaces

    ui->label_numACbeds->setText( QString::number(totalACBeds));

}
