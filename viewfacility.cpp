#include "viewfacility.h"
#include "ui_viewfacility.h"

#include"datastorage.h"

ViewFacility::ViewFacility(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewFacility)
{
    ui->setupUi(this);

    connect(ui->DisplayButton, SIGNAL(clicked()),this,SLOT(displayInformation()));

}

ViewFacility::~ViewFacility()
{
    delete ui;
}


void ViewFacility::displayInformation()
{
    QString facilName = ui->comboBox_facilities->currentText();
    int facilID = DataStorage::getFacilityID(facilName);

    QVector<Patient*> patients = DataStorage::getPatientsAtFacility(facilID);

    for(int i= 0; i<patients.size();i++)
    {
        //need to add these functions to DataStorage

        QString firstname = patients[i]->getFirstname();

        QString lastname = patients[i]->getLastname();

        ui->listWidget_patients->addItem(firstname + " " + lastname + " ("+ patients[i]->getHCN() + ")");

    }

}
