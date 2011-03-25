/*Class name: AssignBed
  Purpose: To display a form for the user to assign a patient to a bed. Then it will collect the data from the gui and pass it to the data storage classes
  Traceability: This class traces back to the AssignBedControl from Deliverable 2*/

/*Created by: Nisrin Abou-Seido
  Last modified: March 20, 2011*/


#include "assignbed.h"
#include "ui_assignbed.h"

AssignBed::AssignBed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssignBed)
{
    ui->setupUi(this);
    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));
}

AssignBed::~AssignBed()
{
    delete ui;
}

void AssignBed::clickedOK()
{
    //get data from the GUI


    //request from the data storage classes that a patient is assigned a bed

    //close the form window
    close();

}
