#include "viewwaitinglist.h"
#include "ui_viewwaitinglist.h"

#include "eobcproject.h"

ViewWaitingList::ViewWaitingList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewWaitingList)
{
    ui->setupUi(this);
    connect(ui->DisplayButton, SIGNAL(clicked()),this,SLOT(displayInformation()));

    QVector<int> areas = DataStorage::getAllAreas();
    for (int i=0;i<areas.size();i++)
    {
        ui->comboBox_areas->addItem(DataStorage::getAreaName(areas.at(i)));

    }
}

ViewWaitingList::~ViewWaitingList()
{
    delete ui;
}

void ViewWaitingList::displayInformation()
{
    QString areaName = ui->comboBox_areas->currentText();
    int areaID = DataStorage::getAreaID(areaName);

    QVector<InPatient*> patients = DataStorage::getPatientsAtFacility(areaID);

    for(int i= 0; i<patients.size();i++)
    {

        QString firstname = patients[i]->getFirstname();
        QString lastname = patients[i]->getLastname();
        ui->listWidget_patients->addItem(firstname + " " + lastname + " ("+ patients[i]->getHCN() + ")");

    }



}
