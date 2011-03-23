/********
  CLASS NAME: AddPatientToWaitingList
  PURPOSE: To display a form for the user to add a patient to waiting list. Then it will collect the data from the gui and pass it to the data storage classes
  TRACEABILITY: This class traces back to the AddPatientToWaitingListControl class from Deliverable 2

  CREATED BY: Nisrin Abou-Seido
  LAST MODIFIED: March 20, 2011

***********/

#include "addpatienttowaitinglist.h"
#include "ui_addpatienttowaitinglist.h"

AddPatientToWaitingList::AddPatientToWaitingList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddPatientToWaitingList)
{
    ui->setupUi(this);
    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));
}

AddPatientToWaitingList::~AddPatientToWaitingList()
{
    delete ui;
}

void AddPatientToWaitingList::clickedOK()
{
    /*
    int numBeds = ui->lineEditNumBeds->text().toInt();
    QString careType = ui->comboBox_careTypes->currentText();
    QString facilName = ui->comboBox_facilities->currentText();

    QString s;

    QMessageBox msgBox;

    msgBox.setText("You have requested to add " + s.setNum(numBeds) +" "+ careType + " care beds to " + facilName);

    msgBox.setInformativeText("Do you want to save and propogate this change?");
    msgBox.setStandardButtons( QMessageBox::Cancel|QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    if(ret == QMessageBox::Ok)
    {   //call addBed in the DatabaseWrapper with numBeds, careType and the facilityID


        close(); //if user clicks Cancel, we do not close the addBeds form

    }
*/

    close();

}
