/********
  CLASS NAME: AddBed
  PURPOSE: To display a form for the user to add beds to a facility. Then it will collect the data from the gui and pass it to the data storage classes
  TRACEABILITY: This class traces back to the AddBedsControl class from Deliverable 2

  CREATED BY: Nisrin Abou-Seido

***********/

#include "addbed.h"
#include "ui_addbed.h"


using namespace std;

AddBed::AddBed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddBed)
{
    ui->setupUi(this);
    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));



    if(DataStorage::currentUserType == "FACILITY")
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

AddBed::~AddBed()
{
    delete ui;
}


void AddBed::clickedOK()

{
    int numBeds = ui->spinBox_numBeds->value();

    QString careType = ui->comboBox_careTypes->currentText();
    QString facilName = ui->comboBox_facilities->currentText();


    QMessageBox msgBox;


    if(careType == "Long Term Care")
        careType = "LTC";
    else if (careType == "Acute Care")
        careType = "AC";
    else
        careType = "CCC";


    //error checking
    bool noErrors = true;

    int facilID = DataStorage::getFacilityID(facilName);
    if(facilID == -1)
    {
        msgBox.setText("Selected facility is not valid");
        msgBox.exec();
        noErrors = false;
    }

    QString facilType = DataStorage::getFacilityType(facilID);

    qDebug() << facilType;
    qDebug() << careType;

    if((facilType == "Hospital")&&(careType == "LTC"))
    {
        QMessageBox msgBox2;
        msgBox2.setText("The selected facility is a hospital. You can only add 'acute care'' or 'complex continuing care' beds");
        msgBox2.exec();
        noErrors = false;


    }
    else if((facilType == "Nursing Home")&&(careType != "LTC"))
    {
        QMessageBox msgBox3;
        msgBox3.setText("The selected facility is a nursing home. You can only add 'long term care' beds");
        msgBox3.exec();
        noErrors = false;

    }
    else{
        if(noErrors)
        {
            msgBox.setText("You have requested to add " + QString::number(numBeds) +" "+ careType + " care beds to " + facilName);

            msgBox.setInformativeText("Do you want to save and propogate this change?");
            msgBox.setStandardButtons( QMessageBox::Cancel | QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            int ret = msgBox.exec();

            if(ret == QMessageBox::Ok)
            {   //call addBed in the DatabaseWrapper with numBeds, careType and the facilityID

                DataStorage::addBeds(facilID,numBeds,careType);


                MessageControl::sendMessageToAll("added some beds to some facility");  /*******testing to see if it is possible to send messages!!!!*****************/

                close(); //if user clicks Cancel, we do not close the addBeds form

            }
        }
    }

}
