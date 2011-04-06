#include "removepatient.h"
#include "ui_removepatient.h"

//#include "datastorage.h"





RemovePatient::RemovePatient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemovePatient)
{
    ui->setupUi(this);
    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));

    connect(ui->DisplayButton_2,SIGNAL(clicked()),this,SLOT(displayPatients()));




    if(DataStorage::currentUserType== "FACILITY")
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

RemovePatient::~RemovePatient()
{
    delete ui;
}

void RemovePatient::displayPatients()
{
    ui->listWidget_patients->clear();
    QString facilname = ui->comboBox_facilities->currentText();

    int facilID = DataStorage::getFacilityID(facilname);
    QVector<Inpatient> patients = DataStorage::getPatientsAtFacility(facilID);

    for(int i;i<patients.size();i++)
    {
        ui->listWidget_patients->addItem(patients[i].getHCN());
    }

}

void RemovePatient::clickedOK()
{
    //get data from the GUI
    QString patientHCN;
    QMessageBox msgBox;

    if(ui->listWidget_patients->currentItem() == 0)
    {
        msgBox.setText("Must select a patient. If list is empty, please select another facility.");
        msgBox.exec();
    }
    else
    {
        patientHCN = ui->listWidget_patients->currentItem()->text();

        //check that the user is sure this is what they want to do.
        QString firstname = DataStorage::getPatientFirstName(patientHCN);
        QString lastname = DataStorage::getPatientLastName(patientHCN);

        QString facilname = ui->comboBox_facilities->currentText();

        msgBox.setText("You have requested to *remove* the following patient from the facility \" " +facilname+ "\":\n\nHealth Card Number: " + patientHCN +"\nFirst Name: "+ firstname + "\nLast Name: " + lastname);

        msgBox.setInformativeText("Do you want to save and propogate this change?");
        msgBox.setStandardButtons( QMessageBox::Cancel | QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();

        int facilid = DataStorage::getFacilityID(facilname);
        int areaid = DataStorage::getAreaForFacility(facilid);

        QDateTime date = QDateTime::currentDateTime();
        QString dateremoved = date.toString("yyyy-MM-ddThh:mm:ss");

        if(ret == QMessageBox::Ok)
        {   //call removePatientFromBed from datastorage class

            DataStorage::removePatientFromBed(facilid, patientHCN, dateremoved);

            bool remote = true;
            if(facilid == DataStorage::myFacilityID)
                remote = false;

            QString operation = "Remove";
            //call XMLGenerator
            QString message = xmlgenerator::patientOperationXML(operation,patientHCN,facilid, areaid, remote, "", "", "", "", -1, -1);


            if(remote == false)
                MessageControl::sendMessage(message,facilid); //send message to the facility to whom we are adding a patient
            else
                MessageControl::sendMessageToAll(message);//notify other facils that we are assigning patient to a bed at *this* facility
            close(); //if user clicks Cancel, we do *not* close the form

        }
    }

}
