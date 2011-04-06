/********
***********/

#include "removepatientfromwaitinglist.h"
#include "ui_removepatientfromwaitinglist.h"




RemovePatientFromWaitingList::RemovePatientFromWaitingList(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::RemovePatientFromWaitingList)
{
    ui->setupUi(this);
    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));

    connect(ui->DisplayButton,SIGNAL(clicked()),this,SLOT(displayPatients()));


    //populate area combo box
    QVector<int> areas = DataStorage::getAllAreas();

    qDebug() << "Vector size is: " << areas.size();
    for(int i=0; i< areas.size();i++)
    {
        qDebug() << "Area is: " << areas[i];
        QString areaname = DataStorage::getAreaName(areas[i]);
        ui->comboBox_areas->addItem(areaname);

    }
}

RemovePatientFromWaitingList::~RemovePatientFromWaitingList()
{
    delete ui;
}

void RemovePatientFromWaitingList::displayPatients()
{

    ui->listWidget_patients->clear();

    QString areaname = ui->comboBox_areas->currentText();

    int areaID = DataStorage::getAreaID(areaname);

    QVector<Patient> patients = DataStorage::getWaitingListPatients(areaID);

    for(int i;i<patients.size();i++)
    {
        ui->listWidget_patients->addItem(patients[i].getHCN());



        //attempt to add patients to the list as objects *is not working*


        /*if( patients[i])
        {
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setFlags( newItem->flags() | Qt::ItemIsUserCheckable );
            newItem->setCheckState(Qt::Unchecked);

            newItem->setText( patients[i]->getFirstname() + " " + patients[i]->getLastname() );


            newItem->setData( Qt::UserRole, patients[i] );
            ui->listWidget_patients->insertItem( ui->listWidget_patients->count(), newItem);
        }*/
    }
    // QObject * obj = qvariant_cast<QObject *>(item->data(Qt::UserRole));
    // from QObject* to myClass*
    //myClass * lmyClass = qobject_cast<myClass *>(obj);


}

void RemovePatientFromWaitingList::clickedOK()
{
    //get data from the GUI
    QString patientHCN;
    QMessageBox msgBox;


    if(ui->listWidget_patients->currentItem() == 0)
    {
        msgBox.setText("Must select a patient. If list is empty, please select another area.");
        msgBox.exec();
    }
    else
    {
        patientHCN = ui->listWidget_patients->currentItem()->text();

        QString firstname = DataStorage::getPatientFirstName(patientHCN);
        QString lastname = DataStorage::getPatientLastName(patientHCN);

        QString areaname = ui->comboBox_areas->currentText();

        msgBox.setText("You have requested to *remove* the following patient from the waiting list for " +areaname+ ":\n\nHealth Card Number: " + patientHCN +"\nFirst Name: "+ firstname + "\nLast Name: " + lastname);

        msgBox.setInformativeText("Do you want to save and propogate this change?");
        msgBox.setStandardButtons( QMessageBox::Cancel | QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();

        int areaid = DataStorage::getAreaID(areaname);

        QDateTime date = QDateTime::currentDateTime();
        QString dateRemoved = date.toString("yyyy-MM-ddThh:mm:ss");

        if(ret == QMessageBox::Ok)
        {   //call removePatientFromWaitingList from datastorage class

            //DataStorage::removePatientFromWaitingList(areaid, patientHCN, dateRemoved);

            //saving in temporary database and sending the message to other facilities

           // bool remote = true;
            //if(currFacility == DataStorage::myFacilityID)
            //    remote = false;

             QString operation = "Remove";

            //remove a paitient frm the waiting list in temp database.
               //DataStorage::addPatientToWaitingList(HCN,areaid,dateAdded);
/*
               QString message;
               if((areaid == DataStorage::myArea()) && (DataStorage::isMainFacility() ))
               essage = xmlgenerator::patientOperationXML(operation,HCN, currFacility, areaid, 0, dateAdded, dateAdmitted, firstname, lastname, DataStorage::getCareType("LTC"), DataStorage::getCareType("LTC"));
                else
                    message = xmlgenerator::patientOperationXML(operation,HCN, currFacility, areaid, 1, dateAdded, dateAdmitted, firstname, lastname, DataStorage::getCareType("LTC"), DataStorage::getCareType("LTC"));

                MessageControl::sendMessageToAll(message);
*/

            close();

        }
    }

}
