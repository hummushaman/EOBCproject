/********
  CLASS NAME: AddPatientToWaitingList
  PURPOSE: To display a form for the user to add a patient to waiting list. Then it will collect the data from the gui and pass it to the data storage classes
  TRACEABILITY: This class traces back to the AddPatientToWaitingListControl class from Deliverable 2

  CREATED BY: Nisrin Abou-Seido

***********/

#include "addpatienttowaitinglist.h"
#include "ui_addpatienttowaitinglist.h"




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

    /*
    QVector<int> facilities = DataStorage::getAllFacilities();
    for(int i=0; i< facilities.size();i++)
     {
            QString facilName = DataStorage::getFacilityName(facilities.at(i));
            ui->comboBox_facilities->addItem(facilName);
     }*/

}

AddPatientToWaitingList::~AddPatientToWaitingList()
{
    delete ui;
}

void AddPatientToWaitingList::clickedOK()
{
    //get data from the GUI
    QMessageBox errormsg;
    bool needMoreInfo = false;

    QString areaName = ui->comboBox_areas->currentText();
    QString patientType = ui->comboBox_patientType->currentText();
    QString HCN = ui->lineEdit_hcn->text();

    if((areaName == "")||(patientType == "")||(HCN == ""))
    {
        errormsg.setText("Please fill out all fields.");
        errormsg.exec();
        needMoreInfo = true;
    }

    QString firstname;
    QString lastname;
    int currFacility;
    QString dateAdmitted;

    if(patientType == "Outpatient")
    {

        firstname = ui->lineEdit_firstname->text();
        lastname = ui->lineEdit_lastname->text();
        if((firstname == "") || (lastname == ""))
        {
            errormsg.setText("Please enter both a first name and a last name");
            errormsg.exec();
            needMoreInfo = true;

        }

    }
    else //get info from datastorage
    {
        //check that the patient exists

        firstname = DataStorage::getPatientFirstName(HCN);

        if(firstname == "")
        {
            errormsg.setText("This inpatient does not exist. Please enter another health care number or select 'Outpatient' as the patient type");
            errormsg.exec();
            needMoreInfo = true;

        }
        else
        {

        lastname = DataStorage::getPatientLastName(HCN);
        currFacility = DataStorage::getCurrentFacilityForPatient(HCN);
        dateAdmitted = DataStorage::getPatientDateAdmitted(HCN);
        }
    }


    //get todays date
    QDateTime datetime = QDateTime::currentDateTime();
    QString dateAdded = datetime.toString("yyyy-MM-ddThh:mm:ss");


    int areaid = DataStorage::getAreaID(areaName);

    //check that patient is not already on the waiting list
    QVector<Patient> patients = DataStorage::getWaitingListPatients(areaid);
    bool patientExists = false;
    for(int i=0;i<patients.size(); i++)
    {
        if(patients[i].getHCN()== HCN)
        {
            QMessageBox msgbox;
            msgbox.setText("This patient is already on the waiting list for this area. Please select a different area.");
            msgbox.exec();
            patientExists = true;

        }


    }

    if (!patientExists && !needMoreInfo)
    {
        QMessageBox msgBox;
        msgBox.setInformativeText("You have requested to add this patient to the waiting list of area " + areaName + ".\nDo you want to save and propogate this change?");
        msgBox.setStandardButtons( QMessageBox::Cancel | QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();

        if(ret == QMessageBox::Ok)
        {

                //saving in temporary database and sending the message to other facilities

                bool remote = true;
                if(currFacility == DataStorage::myFacilityID)
                    remote = false;

                 QString operation = "Add";

                if(patientType == "Inpatient")
                {
                    //add an inpatient to the waiting list in temp database.
                     //DataStorage::addPatientToWaitingList(HCN,areaid,dateAdded);



                    //send the message to other facilities
                     QString message = xmlgenerator::patientOperationXML(operation, HCN, currFacility, areaid, remote, dateAdded, dateAdmitted, firstname, lastname, DataStorage::getCareType("LTC"), DataStorage::getCareType("LTC"));

                     if(remote == false)// this
                         MessageControl::sendMessage(message,currFacility);
                     else
                         MessageControl::sendMessageToAll(message);
                }
                else
                {

                    //DataStorage::addPatientToWaitingList(HCN,firstname,lastname,areaid,dateAdded);



                    //what do we do if we are the main facility for this area?
                    //what if we're not? who do we pass the message to?
                    // the patients current facility or the waiting list we are adding them to?

                    if((areaid == DataStorage::myArea()) && (DataStorage::isMainFacility() ))
                        QString message = xmlgenerator::patientOperationXML(operation,HCN, currFacility, areaid, 0, dateAdded, dateAdmitted, firstname, lastname, DataStorage::getCareType("LTC"), DataStorage::getCareType("LTC"));
                    else
                        QString message = xmlgenerator::patientOperationXML(operation,HCN, currFacility, areaid, 1, dateAdded, dateAdmitted, firstname, lastname, DataStorage::getCareType("LTC"), DataStorage::getCareType("LTC"));

                    MessageControl::sendMessageToAll(message);

                }

            close();

        }
    }
    //QMessageBox msgbox2;
    //msgbox2.setText("todays date and time: "+ datetime);
    //msgbox2.exec();




}
