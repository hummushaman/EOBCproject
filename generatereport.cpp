#include "generatereport.h"
#include "ui_generatereport.h"



using namespace std;

GenerateReport::GenerateReport(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GenerateReport)
{
    ui->setupUi(this);

   // hide frames until user checks box

    ui->frame_careMismatch->setVisible(false);
    ui->frame_occupancyRate->setVisible(false);
    ui->frame_waitingListSize->setVisible(false);
    ui->frame_waitTimes->setVisible(false);


    connect(ui->checkBox_careMismatch, SIGNAL(stateChanged(int)), this, SLOT(careMismatchBoxClicked()));

    connect(ui->checkBox_waitTimes, SIGNAL(stateChanged(int)), this, SLOT(waitTimesBoxClicked()));
    connect(ui->checkBox_occupancyRate, SIGNAL(stateChanged(int)), this, SLOT(occupancyRateBoxClicked()));
    connect(ui->checkBox_waitingListSize, SIGNAL(stateChanged(int)), this, SLOT(waitingListSizeBoxClicked()));

    //connect okbutton to slot
    connect(ui->OKButton, SIGNAL(clicked()), this, SLOT(GenerateReportButtonClicked()));
}


void GenerateReport::GenerateReportButtonClicked()
{
    //get the information from the GUI about which buttons are checked in order to determine what graphs the user wants to see


    //request data from the data storage objects ( ie Area,Facility)


    //generate the graphs using QT tools


    //display the graphs in a new window.



    //close the generate Report form
    close();

}



GenerateReport::~GenerateReport()
{
    delete ui;
}

void GenerateReport::waitTimesBoxClicked()
{

    if(ui->frame_waitTimes->isVisible())
        ui->frame_waitTimes->hide();
    else
        ui->frame_waitTimes->show();

}

void GenerateReport::careMismatchBoxClicked()
{
    if(ui->frame_careMismatch->isVisible())
        ui->frame_careMismatch->hide();
    else
        ui->frame_careMismatch->show();
}

void GenerateReport::occupancyRateBoxClicked()
{

    if(ui->frame_occupancyRate->isVisible())
        ui->frame_occupancyRate->hide();
    else
        ui->frame_occupancyRate->show();
}

void GenerateReport::waitingListSizeBoxClicked()
{
    if(ui->frame_waitingListSize->isVisible())
        ui->frame_waitingListSize->hide();
    else
        ui->frame_waitingListSize->show();
}
