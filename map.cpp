/********
  CLASS NAME: Map
  PURPOSE: Requests information from the data storage classes and uses it to display a map of the LHIN to the user. Allows the user to hide or show facilities and areas.
  TRACEABILITY: This class traces back to the MapControl from Deliverable 2

  CREATED BY: Nisrin Abou-Seido
  LAST MODIFIED: March 20, 2011

***********/
#include "map.h"
#include "ui_map.h"
#include <qgraphicsview.h>
#include <qpixmap.h>
#include <QPixmap>
#include <patient.h>
#include <datastorage.h>


Map::Map(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);

    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));
    connect(ui->viewOccRates,SIGNAL(toggled(bool)),this,SLOT(updateMap()));

    updateMap();


}
Map::~Map()
{
    delete ui;
}

void Map::clickedOK()
{

    close();

}

void Map::updateMap(){
    QGraphicsScene *contents = new QGraphicsScene( ui->mapview );
    QPen pen;
    QBrush brush;
    QFont font;
    QPixmap mapImage("/home/4user4/filitche/eobc4/map.svg");        //"/home/4user4/filitche/eobc4/map.svg"

    double wldim=15;
    double acdim=0.33*wldim;
    double cccdim=0.66*wldim;
    double ltcdim=0.5*wldim;

    //NOTE THAT THIS ADDRESS IS LOCAL TO FILITCHE


    contents->addPixmap(mapImage);


    //NOTE THAT YOU MIGHT NEED TO GET A SCALE FOR THE MAP


    QList<QListWidgetItem*>areas=ui->listWidget->selectedItems();
    float largestList=0;
    QVector<int>areaIDs;
    QVector<double>wlSizes;
    for (int i=0;i<areas.size();i++){
        QString name=areas[i]->text();
        QVector<Patient*>patients=DataStorage::getWaitingListPatients(DataStorage::getAreaID(name));
        areaIDs.append(DataStorage::getAreaID(name));
        wlSizes.append(patients.size());
        if (patients.size()>largestList)largestList=patients.size();
        //SO, WE ARE LOOKING AT RELATIVE WAIT LIST SIZES
    }

    QString nl="";




    //PROBLEM: if we want a waiting list size for an area but have no facilities from that area then we won't get it displayed!





    QList<QListWidgetItem*>facilities=ui->listWidget_2->selectedItems();
    for (int i=0;i<facilities.size();i++){
        int facilNum=DataStorage::getFacilityID(facilities[i]->text());
        int area=DataStorage::getAreaForFacility(facilNum);

        double ac=0;
        double ccc=0;
        double ltc=0;
        int areaIndex=areaIDs.indexOf(area);
        int wl=wlSizes[areaIndex];

        QString facilType=DataStorage::getFacilityType(facilNum);

        if (facilType=="Hospital"){
            ac=((double)DataStorage::getNumACBedsOccupied(facilNum))/((double)DataStorage::getTotalACBeds(facilNum));
            ccc=((double)DataStorage::getNumCCCBedsOccupied(facilNum))/((double)DataStorage::getTotalCCCBeds(facilNum));
        }
        else{
            ltc=((double)DataStorage::getNumLTCBedsOccupied(facilNum))/((double)DataStorage::getTotalLTCBeds(facilNum));
        }

        QString datum=nl.append(facilities[i]->text()+" AC:"+ac+" CCC:"+" LTC:"+ltc+" WL:"+wl);
        contents->addText(datum,font);


        double x = DataStorage::getFacilityX(facilNum);
        double y = DataStorage::getFacilityY(facilNum);
        if (ui->viewWLsizes->isChecked()){
            if (areaIDs.contains(DataStorage::getAreaForFacility(facilNum)))
            {
                //print WL circle
                double factor=wlSizes[areaIndex]/largestList;
                pen.setColor("red");
                pen.setColor(pen.color().darker(100+200*factor));
                contents->addEllipse(x,y,wldim,wldim,pen,brush);
            }
        }


        if (ui->viewOccRates->isChecked()){
            if (facilType=="Hospital"){
                pen.setColor("green");
                pen.setColor(pen.color().darker(100+200*ccc));
                contents->addEllipse(x,y,cccdim,cccdim,pen,brush);

                pen.setColor("blue");
                pen.setColor(pen.color().darker(100+200*ac));
                contents->addEllipse(x,y,acdim,acdim,pen,brush);

            }
            else{
                pen.setColor("yellow");
                pen.setColor(pen.color().darker(100+200*ltc));
                contents->addEllipse(x,y,ltcdim,ltcdim,pen,brush);
            }
        }

        nl.append("\n\n");
    }

    ui->mapview->setScene(contents);
    ui->mapview->show();
}
