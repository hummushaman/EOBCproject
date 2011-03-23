/********
  CLASS NAME: Map
  PURPOSE: Requests information from the data storage classes and uses it to display a map of the LHIN to the user. Allows the user to hide or show facilities and areas.
  TRACEABILITY: This class traces back to the MapControl from Deliverable 2

  CREATED BY: Nisrin Abou-Seido
  LAST MODIFIED: March 20, 2011

***********/
#include "map.h"
#include "ui_map.h"




Map::Map(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);

    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));

}
Map::~Map()
{
    delete ui;
}

void Map::clickedOK()
{

    close();

}
