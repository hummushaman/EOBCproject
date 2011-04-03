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
}

AddFacility::~AddFacility()
{
    delete ui;
}

void AddFacility::clickedOK()
{
    //gets the information from the GUI and sends a request to the datastorage
    QString name = ui->lineEdit_name->text();

    float x = ui->lineEdit_x->text().toFloat();
    float y = ui->lineEdit_x->text().toFloat();




    close();

}
