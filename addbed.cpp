/********
  CLASS NAME: AddBed
  PURPOSE: To display a form for the user to add beds to a facility. Then it will collect the data from the gui and pass it to the data storage classes
  TRACEABILITY: This class traces back to the AddBedsControl class from Deliverable 2

  CREATED BY: Nisrin Abou-Seido
  LAST MODIFIED: March 20, 2011

***********/

#include "addbed.h"
#include "ui_addbed.h"

#include <QMessageBox>
#include "datastorage.h"
#include <iostream>
#include <string>

using namespace std;

AddBed::AddBed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddBed)
{
    ui->setupUi(this);
    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));

    QVector<int> facilities = DataStorage::getAllFacilities();


    for(int i=0; i< facilities.size();i++)
    {
        QString facilName = DataStorage::getFacilityName(facilities.at(i));
       ui->comboBox_facilities->addItem(facilName);
    }

}

AddBed::~AddBed()
{
    delete ui;
}


void AddBed::clickedOK()

{


    int numBeds = ui->lineEditNumBeds->text().toInt();
    QString careType = ui->comboBox_careTypes->currentText();
    QString facilName = ui->comboBox_facilities->currentText();

    QString s;

    QMessageBox msgBox;

    if(careType == "Long Term Care")
        careType = "LTC";
    else if (careType == "Acute Care")
        careType = "AC";
    else
        careType = "CCC";



    //error checking
    int facilID = DataStorage::getFacilityID(facilName);
    QString facilType = DataStorage::getFacilityType(facilID);

    if((facilType == "Hospital")&&(careType == "LTC"))
    {
        QMessageBox msgBox2;
        msgBox2.setText("The selected facility is a hospital. You can only add 'acute care'' or 'complex continuing care' beds");
        msgBox2.exec();


    }
    else if((facilType == "Nursing Home")&&(careType != "LTC"))
    {
        QMessageBox msgBox3;
        msgBox3.setText("The selected facility is a nursing home. You can only add 'long term care' beds");
        msgBox3.exec();

    }
    else{
        msgBox.setText("You have requested to add " + s.setNum(numBeds) +" "+ careType + " care beds to " + facilName);

        msgBox.setInformativeText("Do you want to save and propogate this change?");
        msgBox.setStandardButtons( QMessageBox::Cancel | QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();

        if(ret == QMessageBox::Ok)
        {   //call addBed in the DatabaseWrapper with numBeds, careType and the facilityID

            DataStorage::addBeds(facilID,numBeds,careType);
            close(); //if user clicks Cancel, we do not close the addBeds form

        }
    }

}
