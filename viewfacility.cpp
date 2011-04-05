
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



    if(DataStorage::getFacilityType(facilID) == "Hospital")
    {
            int totalACBeds = DataStorage::getTotalACBeds(facilID);
            int totalCCCBeds = DataStorage::getTotalCCCBeds(facilID);

            float numCCCoccupied = DataStorage::getNumCCCBedsOccupied(facilID);
            float numACoccupied = DataStorage::getNumACBedsOccupied(facilID);

            float occRateAC;
            float occRateCCC;


            if (totalACBeds != 0)
                occRateAC = numACoccupied/totalACBeds * 100;
            else
                occRateAC = 0;


            if(totalCCCBeds != 0)
                occRateCCC = numCCCoccupied/totalCCCBeds * 100;
            else
                occRateCCC = 0;


            ui->label_numACbeds->setText( QString::number(totalACBeds));
            ui->label_numCCCbeds->setText(QString::number(totalCCCBeds));

            ui->label_occRateAC->setText(QString::number(occRateAC) + "%");
            ui->label_occRateCCC->setText(QString::number(occRateCCC) + "%");

    }
    else
    {
        ui->label_numACbeds->setText( "N/A");
        ui->label_numCCCbeds->setText("N/A");
        ui->label_occRateAC->setText("N/A");
        ui->label_occRateCCC->setText("N/A");

    }

    float totalNumBeds = DataStorage::getTotalNumBeds(facilID);
    float totalBedsOccupied = DataStorage::getTotalNumBedsOccupied(facilID);

    float occRate;
    if(totalNumBeds != 0)
        occRate= (totalBedsOccupied/totalNumBeds) * 100;
    else
        occRate = 0;


    //print to the labels
    //use formatting to limit the occrate to 2 decimal spaces

    ui->label_totalNumBeds->setText(QString::number(totalNumBeds));
    ui->label_overallOccRate->setText(QString::number(occRate) + "%");


}
