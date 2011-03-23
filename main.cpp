/********
  CLASS NAME: Main
  PURPOSE: Starts up the system. Displays the login form to the user.

  TRACEABILITY: This class traces back to..

  CREATED BY: Nisrin Abou-Seido
  LAST MODIFIED: March 20, 2011

***********/


#include <QtGui/QApplication>
#include "login.h"

#include <iostream>
#include <stdio.h>

#include<QGraphicsView>
#include<QGraphicsEllipseItem>
#include<QGraphicsScene>
#include<QGraphicsPixmapItem>
#include<QPixmap>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();


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



    std::cout << "Hello";

    return a.exec();
}
