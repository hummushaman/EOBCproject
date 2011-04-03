#include "reportdisplay.h"
#include "ui_reportdisplay.h"
#include "qdebug.h"
#include <qline.h>
#include <QPixmap>
#include "qpixmap.h"
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QGraphicsTextItem>

ReportDisplay::ReportDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReportDisplay)
{
    ui->setupUi(this);
}

ReportDisplay::~ReportDisplay()
{
    delete ui;
}

void ReportDisplay::showReport(QVector< QVector<double> >graph, QString startDate, QString endDate,QVector<QString>names){
    ui->from->setText(startDate);
    ui->to->setText(endDate);

    QGraphicsScene *contents = new QGraphicsScene( ui->graphicsView );
    QPen pen;

    double maxy=0;
    for (int i=0;i<graph.size();i++)
        for (int j=0;j<graph[i].size();j++){
            if (graph[i][j]>maxy)maxy=graph[i][j];

    }

    double width=800;
    double height=300;
    double days=graph[0].size()+1;
    double xinterval=width/days;
    double yinterval=height/(maxy+1);
    double prevx=0;
    double prevy=0;
    double nextx;
    double nexty;
    QColor col;
    QFont font;
    QStringList colorNames=QColor::colorNames();
    QString nl="";

    for (int i=0;i<graph.size();i++){
        pen.setColor(colorNames[i+20]);
        pen.setWidth(3);

        QVector<double>plot=graph[i];
        for (int j=0;j<plot.size();j++){
            if (j==0){
                prevx=0;
                prevy=plot[j];
                contents->addText(nl.append(names[i]).append(" - ").append(colorNames[i+20]),font);
                nl.append("\n\n");
                //contents->addLine(0,j,10,j,pen);
                //QGraphicsTextItem label = contents->itemAt(0,0);
            }
            else{
                nextx=prevx+xinterval;
                nexty=plot[j];
                contents->addLine(prevx,maxy*yinterval-prevy*yinterval,nextx,maxy*yinterval-nexty*yinterval,pen);
                prevx=nextx;
                prevy=nexty;
            }
        }
    }

    ui->graphicsView->setScene(contents);
    ui->graphicsView->show();

}

void ReportDisplay::showBarReport(QVector<double>graph, QString startDate, QString endDate,QVector<QString>names){
    ui->from->setText(startDate);
    ui->to->setText(endDate);

    QGraphicsScene *contents = new QGraphicsScene( ui->graphicsView );
    QPen pen;

    double maxy=0;
    for (int i=0;i<graph.size();i++)if (graph[i]>maxy)maxy=graph[i];
    double width=800;
    double height=300;
    double days=graph.size()+1;
    double xinterval=width/days;
    double yinterval=height/(maxy+1);

    double x=0;

    QColor col;
    QFont font;
    QStringList colorNames=QColor::colorNames();
    QString nl="";

    for (int i=0;i<graph.size();i++){
        pen.setColor(colorNames[i+20]);
        pen.setWidth(xinterval-1);
        contents->addText(nl.append(names[i]).append(" - ").append(colorNames[i+20]),font);
        nl.append("\n\n");
        x+=xinterval;
        double top=graph[i];
        contents->addLine(x,maxy*yinterval,x,maxy*yinterval-top*yinterval,pen);
    }

    ui->graphicsView->setScene(contents);
    ui->graphicsView->show();

}
