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
#include <QPainter>
#include <Qt>


Map::Map(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);

    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));
    connect(ui->viewOccRates,SIGNAL(toggled(bool)),this,SLOT(updateMap()));
    connect(ui->viewWLsizes,SIGNAL(toggled(bool)),this,SLOT(updateMap()));
    connect(ui->listWidget,SIGNAL(toggled(bool)),this,SLOT(updateMap()));
    connect(ui->listWidget_2,SIGNAL(toggled(bool)),this,SLOT(updateMap()));
    updateLists();
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

void Map::updateLists(){
    QVector<int>facilities=DataStorage::getAllFacilities();
    for(int i=0; i< facilities.size();i++)ui->listWidget_2->addItem(DataStorage::getFacilityName(facilities[i]));
    QVector<int>areas=DataStorage::getAllAreas();
    for (int i=0;i<areas.size();i++)ui->listWidget->addItem(DataStorage::getAreaName(areas[i]));
}

void Map::updateMap(){
    QGraphicsScene *contents = new QGraphicsScene( ui->mapview );
    QPen pen;
    QBrush brush;

    brush.setStyle(Qt::SolidPattern);
    QFont font;
    QPainter painter;

    QSettings settings("JNFconfig"); // opens the configuration file. File should be located in: home/<userfolder>/<yourusername>/.config

    //get the map image path
    settings.beginGroup("map");
    QString mapPath =  settings.value("map_filepath").toString();
    qDebug() << "map path: "<<mapPath;

    settings.endGroup();

    QPixmap mapImage(mapPath);        //"/home/4user4/filitche/eobc5/map.svg"

    double wldim=25;
    double acdim=0.33*wldim;
    double cccdim=0.66*wldim;
    double ltcdim=0.5*wldim;


    contents->addPixmap(mapImage);



    double xinterval=contents->width()/1000;
    double yinterval=contents->height()/1000;


    //here, we find the various wl sizes
    QVector<int>allAreaIDs=DataStorage::getAllAreas();
    float largestList=0;
    QVector<double>wlSizes;
    for (int i=0;i<allAreaIDs.size();i++){
        QVector<Patient>patients=DataStorage::getWaitingListPatients(allAreaIDs[i]);
        wlSizes.append(patients.size());
        if (patients.size()>largestList)largestList=patients.size();
        //SO, WE ARE LOOKING AT RELATIVE WAIT LIST SIZES
    }

    //here, we take note of which areas are selected
    QList<QListWidgetItem*>selectedAreas=ui->listWidget->selectedItems();
    QVector<int>selectedAreaIDs;
    for (int i=0;i<selectedAreas.size();i++){
        QString name=selectedAreas[i]->text();
        selectedAreaIDs.append(DataStorage::getAreaID(name));
    }

    QString nl="";

    QList<QListWidgetItem*>sFacilities=ui->listWidget_2->selectedItems();
    QVector<int>selectedFacilities;
    for (int i=0;i<sFacilities.size();i++){
        selectedFacilities.append(DataStorage::getFacilityID(sFacilities[i]->text()));
    }

    QVector<int>allFacilities=DataStorage::getAllFacilities();
    for (int i=0;i<allFacilities.size();i++){
        if ((selectedFacilities.contains(allFacilities[i]))||(selectedAreaIDs.contains(DataStorage::getAreaForFacility(allFacilities[i])))){

            int facilNum=allFacilities[i];
            int area=DataStorage::getAreaForFacility(facilNum);
            double ac=0;
            double ccc=0;
            double ltc=0;
            int areaIndex=allAreaIDs.indexOf(area);
            int wl=wlSizes[areaIndex];
            QString facilType=DataStorage::getFacilityType(facilNum);

            if (facilType=="Hospital"){
                if (ac!=0)ac=((double)DataStorage::getNumACBedsOccupied(facilNum))/((double)DataStorage::getTotalACBeds(facilNum));
                if (ccc!=0)ccc=((double)DataStorage::getNumCCCBedsOccupied(facilNum))/((double)DataStorage::getTotalCCCBeds(facilNum));
            }
            else{
                if (ltc!=0)ltc=((double)DataStorage::getNumLTCBedsOccupied(facilNum))/((double)DataStorage::getTotalLTCBeds(facilNum));
            }


            QString datum=nl.append(DataStorage::getFacilityName(allFacilities[i])+" AC:"+QString::number(ac)+" CCC:"+QString::number(ccc)+" LTC:"+QString::number(ltc)+" WL:"+QString::number(wl));
            contents->addText(datum,font);



            double x = DataStorage::getFacilityX(facilNum);
            double y = DataStorage::getFacilityY(facilNum);
            x=x*xinterval;
            y=y*yinterval;

            /*
            QGraphicsTextItem item("hi");
            item.setParent(contents);
            item.setX(x*xinterval);
            item.setY(y*yinterval);
*/


            if (ui->viewWLsizes->isChecked()){
                    double factor=wlSizes[areaIndex]/largestList;
                    pen.setColor("red");
                    pen.setColor(pen.color().darker(100+200*factor));
                    brush.setColor(pen.color());
                    contents->addEllipse(x,y,wldim,wldim,pen,brush);

            }


            if (ui->viewOccRates->isChecked()){
                if (facilType=="Hospital"){
                    pen.setColor("green");
                    pen.setColor(pen.color().darker(100+200*ccc));
                    brush.setColor(pen.color());
                    contents->addEllipse(x+(wldim-cccdim)/2,y+(wldim-cccdim)/2,cccdim,cccdim,pen,brush);

                    pen.setColor("blue");
                    pen.setColor(pen.color().darker(100+200*ac));
                    brush.setColor(pen.color());
                    contents->addEllipse(x+(wldim-acdim)/2,y+(wldim-acdim)/2,acdim,acdim,pen,brush);

                }
                else{
                    pen.setColor("yellow");
                    pen.setColor(pen.color().darker(100+200*ltc));
                    brush.setColor(pen.color());
                    contents->addEllipse(x+(wldim-ltcdim)/2,y+(wldim-ltcdim)/2,ltcdim,ltcdim,pen,brush);
                }
            }

            nl.append("\n\n");

        }

    }

    ui->mapview->setScene(contents);
    ui->mapview->show();
}
