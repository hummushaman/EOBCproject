/********
  CLASS NAME: AddPatientToWaitingList
  PURPOSE: To display a form for the user to add a patient to waiting list. Then it will collect the data from the gui and pass it to the data storage classes
  TRACEABILITY: This class traces back to the AddPatientToWaitingListControl class from Deliverable 2

  CREATED BY: Nisrin Abou-Seido
  LAST MODIFIED: March 20, 2011

***********/

#include "addpatienttowaitinglist.h"
#include "ui_addpatienttowaitinglist.h"

#include "datastorage.h"
#include <QMessageBox>


AddPatientToWaitingList::AddPatientToWaitingList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddPatientToWaitingList)
{
    ui->setupUi(this);
    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));

    QVector<int> areas = DataStorage::getAllAreas();
    for (int i=0;i<areas.size();i++)
    {
        ui->comboBox_areas->addItem(DataStorage::getAreaName(areas.at(i)));

    }

    QVector<int> facilities = DataStorage::getAllFacilities();
    for (int i=0;i<facilities.size();i++)
    {
        ui->comboBox_facilities->addItem(DataStorage::getFacilityName(facilities.at(i)));

    }

}

AddPatientToWaitingList::~AddPatientToWaitingList()
{
    delete ui;
}

void AddPatientToWaitingList::clickedOK()
{
    //get data from the GUI

    QString firstname = ui->lineEdit_firstname->text();
    QString lastname = ui->lineEdit_lastname->text();
    QString HCN = ui->lineEdit_HCN->text();

    QString patientType = ui->comboBox_patientType->currentText();


    QDate dateAdded = ui->dateEdit_dateAdded->date();

    QDate dateAdmitted = ui->dateEdit_dateAdmitted->date();


    QString areaName = ui->comboBox_areas->currentText();

    QString careType = ui->comboBox_careType->currentText();
    QString facilName = ui->comboBox_facilities->currentText();

    QString s;

    QMessageBox msgBox;




    msgBox.setInformativeText("You have requested to add this patient to the waiting list of area. \n" + areaName + "Do you want to save and propogate this change?");
    msgBox.setStandardButtons( QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    if(ret == QMessageBox::Ok)
    {

        //areaid = DataStorage::getAreaID(areaName);
        int facilID = DataStorage::getFacilityID(facilName);

        if(patientType == "Inpatient")
        {
            //DataStorage::addPatientToWaitingList(HCN,firstname, lastname,areaid,dateAdded, dateAdmitted, facilID,careType);
        }
        else
        {
           // DataStorage::addPatientToWaitingList(HCN,firstname, lastname,areaid,dateAdded);
        }

        close();

    }


    close();

}
