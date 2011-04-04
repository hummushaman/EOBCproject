#ifndef MAP_H
#define MAP_H

#include <QMainWindow>

#include<QGraphicsView>
#include<QGraphicsEllipseItem>
#include<QGraphicsScene>
#include<QGraphicsPixmapItem>
#include<QPixmap>


namespace Ui {
    class Map;
}

class Map : public QMainWindow
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = 0);
    ~Map();

private slots:
    void clickedOK();

private:
    Ui::Map *ui;
};

#endif // MAP_H
