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

#include <iostream>
#include <string>
using namespace std;

AddBed::AddBed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddBed)
{
    ui->setupUi(this);

    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));

}

AddBed::~AddBed()
{
    delete ui;
}


void AddBed::clickedOK()

{
    //added something to the the addBed class

    int numBeds = ui->lineEditNumBeds->text().toInt();
    QString careType = ui->comboBox_careTypes->currentText();
    QString facilName = ui->comboBox_facilities->currentText();

    QString s;

    QMessageBox msgBox;

    msgBox.setText("You have requested to add " + s.setNum(numBeds) +" "+ careType + " care beds to " + facilName);

    msgBox.setInformativeText("Do you want to save and propogate this change?");
    msgBox.setStandardButtons( QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    if(ret == QMessageBox::Ok)
    {   //call addBed in the DatabaseWrapper with numBeds, careType and the facilityID


        close(); //if user clicks Cancel, we do not close the addBeds form

    }
}
