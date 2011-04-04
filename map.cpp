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


    // QGraphicsScene scene;

    // scene.setSceneRect( -100.0, -100.0, 200.0, 200.0 );

     //QGraphicsEllipseItem *item = new QGraphicsEllipseItem( 0, &scene );
     //item->setRect( -50.0, -50.0, 100.0, 100.0 );

     //QGraphicsView view( &scene);
     //view.setRenderHints( QPainter::Antialiasing );
     //view.show();


     //QString fileName = "/home/4user1/naseido/map.svg";
     //QGraphicsScene scene;
     //QGraphicsView view(&scene);
     //QGraphicsPixmapItem item(QPixmap(filename));
     //scene.addItem(&item);
     //view.show();
}
Map::~Map()
{
    delete ui;
}

void Map::clickedOK()
{

    close();

}
