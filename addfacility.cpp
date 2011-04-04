/********
  CLASS NAME: AddFacility
  PURPOSE: To display a form for the system administrator to add a facility to the LHIN. Then it will collect the data from the gui and pass it to the data storage classes
  TRACEABILITY: This class traces back to the AddFacilityControl from Deliverable 2

  CREATED BY: Nisrin Abou-Seido
  LAST MODIFIED: March 20, 2011

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

    bool x_ok, y_ok;

    float x  = ui->lineEdit_x->text().toFloat(&x_ok);
    float y =  ui->lineEdit_x->text().toFloat(&y_ok);

    QString areaname = ui->comboBox_areas->currentText();

    QString facilType = ui->comboBox_facilTypes->currentText();

    int areaid = DataStorage::getAreaID(areaname);

    if(y_ok && x_ok)
    {
        DataStorage::addFacility(name,x,y,areaid,facilID,facilType);
        close();
    }
    else
    {
        msgbox.setText("Please enter valid coordinates");
        msgbox.exec();
    }
}
