/********
***********/

#include "addfacility.h"
#include "ui_addfacility.h"

AddFacility::AddFacility(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::AddFacility)
{
    ui->setupUi(this);
    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));

    //populate area combo box
    QVector<int> areas = DataStorage::getAllAreas();

    for(int i=0; i< areas.size();i++)
    {
        qDebug() << "Area is: " << areas[i];
        QString areaname = DataStorage::getAreaName(areas[i]);
        ui->comboBox_areas->addItem(areaname);
    }
}

AddFacility::~AddFacility()
{
    delete ui;
}

void AddFacility::clickedOK()
{
    QMessageBox msgbox;

    //gets the information from the GUI and sends a request to the datastorage
    QString name = ui->lineEdit_name->text();

    int facilID = ui->spinBox_ID->text().toInt();

    bool facilityExists = DataStorage::facilityExists(facilID);
    bool facilityNameExists = DataStorage::facilityNameExists(name);
    qDebug() << "Facility name exists: " << facilityNameExists;

    bool x_ok, y_ok;

    int x  = ui->lineEdit_x->text().toInt(&x_ok);
    int y =  ui->lineEdit_y->text().toInt(&y_ok);
    bool facilityExistsAtCoordinates = DataStorage::facilityExistsAtCoordinates(x,y);
    qDebug() << "Facility exists at coordinates: " << facilityExistsAtCoordinates;

    qDebug()<<"x"<< QString::number(x);
    qDebug()<<"y"<< QString::number(y);

    QString areaname = ui->comboBox_areas->currentText();

    QString facilType = ui->comboBox_facilTypes->currentText();

    int areaid = DataStorage::getAreaID(areaname);

    if(!facilityExists && !facilityNameExists && !facilityExistsAtCoordinates)
    {
        if(y_ok && x_ok)
        {
            //DataStorage::addFacility(name,x,y,areaid,facilID,facilType);

            int areaID = DataStorage::getAreaForFacility(facilID);

            int numAC =  0;
            int numCCC = 0;
            int numLTC = 0;

            bool remote = true;
            if(facilID == DataStorage::getMyFacilityID())
                remote = false;

            QString message = xmlgenerator::addFacility(facilID,areaID,x,y,numAC,numCCC, numLTC,name,remote,facilType);
            if(remote == false)
            {
                MessageControl::sendMessage(message,DataStorage::myFacilityID);
                MessageControl::sendMessageToAll(message);
            }


            else
                MessageControl::sendMessage(message,facilID);

            close();
        }

        else
        {

            msgbox.setText("Please enter valid coordinates.");
            msgbox.exec();
        }
    }
    else
    {
        if (facilityNameExists)
        {
            msgbox.setText("Facility name is in use. Please choose another name.");
            msgbox.exec();
        }
        else if (facilityExistsAtCoordinates)
        {
            msgbox.setText("Facility exists at the coordinate: (" + QString::number(x) + "," + QString::number(y) + "). Please enter in another set of coordinates.");
            msgbox.exec();
        }else{
            msgbox.setText("Facility ID is already in use. Please choose another id.");
            msgbox.exec();
        }
    }
}
