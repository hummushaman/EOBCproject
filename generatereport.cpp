#include "generatereport.h"
#include "ui_generatereport.h"

//#include "report.ui"

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
    connect(ui->occratebox, SIGNAL(stateChanged(int)), this, SLOT(occupancyRateBoxClicked()));
    connect(ui->checkBox_waitingListSize, SIGNAL(stateChanged(int)), this, SLOT(waitingListSizeBoxClicked()));

    //connect okbutton to slot
    connect(ui->OKButton, SIGNAL(clicked()), this, SLOT(GenerateReportButtonClicked()));
}


void GenerateReport::GenerateReportButtonClicked(){
    generateNoTimeReport();
}

void GenerateReport::generateNoTimeReport(){
    if (ui->occratebox->isChecked())generateNoTimeOccRateReport();
    if (ui->checkBox_waitTimes->isChecked())generateNoTimeWaitTimesReport();
    if (ui->checkBox_waitingListSize->isChecked())generateNoTimeWaitingListSizeReport();
    if (ui->checkBox_careMismatch->isChecked())generateNoTimeCareMismatchReport();
}

void GenerateReport::generateNoTimeWaitTimesReport(){
    QVector<double>theGraph;
    QVector<QString>labels;
    QList<QListWidgetItem*>contents=ui->listWidget_2->selectedItems();
    for (int i=0;i<contents.size();i++){
        QString name=contents[i]->text();
        double total=0;

        QDateTime current = QDateTime::currentDateTime();
        QString today = current.toString("yyyy-MM-ddThh:mm:ss");

        QVector<Patient>patients=DataStorage::getWaitingListPatients(DataStorage::getAreaID(name));
        for (int j=0;j<patients.size();j++){

            QString stringDateAdded=DataStorage::getPatientDateAdded(patients[i].getHCN(),DataStorage::getAreaID(name));
            QDateTime dateAdded=QDateTime::fromString(stringDateAdded,"yyyy-MM-ddThh:mm:ss");

            if (dateAdded.isValid())total+=dateAdded.daysTo(current);

        }

        theGraph.append(total);
        labels.append(name);
    }

    QDateTime date = QDateTime::currentDateTime();
    QString dateTime = date.toString("yyyy-MM-ddThh:mm:ss");

    if (theGraph.size()>0){
        ReportDisplay* win=new ReportDisplay();
        win->showBarReport(theGraph,dateTime,"Wait Times Report",labels);
        win->show();
    }
}

void GenerateReport::generateNoTimeWaitingListSizeReport(){
    QVector<double>theGraph;
    QVector<QString>labels;
    QList<QListWidgetItem*>contents=ui->listWidget_3->selectedItems();
    for (int i=0;i<contents.size();i++){
        QString name=contents[i]->text();
        double total=0;
        QVector<Patient>patients=DataStorage::getWaitingListPatients(DataStorage::getAreaID(name));
        theGraph.append(patients.size());
        labels.append(name);
    }

    QDateTime date = QDateTime::currentDateTime();
    QString dateTime = date.toString("yyyy-MM-ddThh:mm:ss");

    if (theGraph.size()>0){
        ReportDisplay* win=new ReportDisplay();
        win->showBarReport(theGraph,dateTime,"Wait List Sizes Report",labels);
        win->show();
    }
}

void GenerateReport::generateNoTimeCareMismatchReport(){
    QVector<double>theGraph;
    QVector<QString>labels;
    QList<QListWidgetItem*>contents=ui->listWidget_4->selectedItems();
    for (int i=0;i<contents.size();i++){
        QString name=contents[i]->text();
        double total=0;
        //so, the list here should be full of facilities, not areas
        QVector<Inpatient>patients=DataStorage::getPatientsAtFacility(DataStorage::getFacilityID(contents[i]->text()));
        for (int j=0;j<patients.size();j++){
            if (ui->misltcac->isChecked()){
                if ((patients[i].getRequiredCare()=="LTC")&&(patients[i].getCurrentCare()=="AC"))total+=1;
            }
            if (ui->misltcccc->isChecked()){
                if ((patients[i].getRequiredCare()=="LTC")&&(patients[i].getCurrentCare()=="CCC"))total+=1;
            }
        }

        theGraph.append(total);
        labels.append(name);
    }

    QDateTime date = QDateTime::currentDateTime();
    QString dateTime = date.toString("yyyy-MM-ddThh:mm:ss");

    if (theGraph.size()>0){
        ReportDisplay* win=new ReportDisplay();
        win->showBarReport(theGraph,dateTime,"Mismatches Report",labels);
        win->show();
    }
}

void GenerateReport::generateNoTimeOccRateReport(){
 QVector<double>theGraph;
 QVector<int>allFacilities=DataStorage::getAllFacilities();
 QVector<QString>labels;

    if (ui->caretypebox->isChecked()){
        if (ui->acbox->isChecked()){
            double total=0;
            for (int i=0;i<allFacilities.size();i++)total+=DataStorage::getTotalACBeds(allFacilities[i]);
            theGraph.append(total);
            labels.append("Acute Care");
        }
        if (ui->cccbox->isChecked()){
            double total=0;
            for (int i=0;i<allFacilities.size();i++)total+=DataStorage::getTotalCCCBeds(allFacilities[i]);
            theGraph.append(total);
            labels.append("Complex Continuous Care");
        }
        if (ui->ltcbox->isChecked()){
            double total=0;
            for (int i=0;i<allFacilities.size();i++)total+=DataStorage::getTotalLTCBeds(allFacilities[i]);
            theGraph.append(total);
            labels.append("Long Term Care");
        }

    }
    if (ui->faciltypebox->isChecked()){
        if (ui->hospbox->isChecked()){
            double total=0;
            for (int i=0;i<allFacilities.size();i++){
                if (DataStorage::getFacilityType(allFacilities[i])=="Hospital"){
                    total+=DataStorage::getTotalACBeds(allFacilities[i]);
                    total+=DataStorage::getTotalCCCBeds(allFacilities[i]);
                }
            }
            theGraph.append(total);
            labels.append("Hospital");
        }
        if (ui->nursbox->isChecked()){
            double total=0;
            for (int i=0;i<allFacilities.size();i++){
                if (DataStorage::getFacilityType(allFacilities[i])!="Hospital"){
                    total+=DataStorage::getTotalLTCBeds(allFacilities[i]);
                }
            }
            theGraph.append(total);
            labels.append("Nursing Home");
        }
    }
    if (ui->selectfacilbox->isChecked()){
        QList<QListWidgetItem*>contents=ui->facillist->selectedItems();
        for (int i=0;i<contents.size();i++){
            double total=0;
            QString name=contents[i]->text();
            int id=DataStorage::getFacilityID(name);
            total+=DataStorage::getTotalACBeds(id);
            total+=DataStorage::getTotalCCCBeds(id);
            total+=DataStorage::getTotalLTCBeds(id);
            theGraph.append(total);
            labels.append(name);
        }

    }

    QDateTime date = QDateTime::currentDateTime();
    QString dateTime = date.toString("yyyy-MM-ddThh:mm:ss");

    if (theGraph.size()>0){
        ReportDisplay* win=new ReportDisplay();
        win->showBarReport(theGraph,dateTime,"Occupation Rates Report",labels);
        win->show();
    }
}

void GenerateReport::generateFakeReports(){
    QVector<QString>names;
    names.append("Facility #1");
    names.append("Facility #2");
    names.append("Facility #3");
    names.append("Facility #4");
    names.append("Facility #5");
    names.append("Facility #6");
    names.append("Facility #7");
    names.append("Facility #8");
    names.append("Facility #9");
    names.append("Facility #10");
    QVector<double> a;
    QVector<double> b;
    QVector<double> c;
    QVector<double> d;
    for (int i=0;i<10;i++){
        a.append(i);
        b.append(10-i);
        c.append(i/2+2);
        d.append(i/4+5);
    }

    QVector< QVector<double> >sampDat;
    sampDat.append(a);
    sampDat.append(b);
    sampDat.append(c);
    sampDat.append(d);

    sampDat[0]=a;
    sampDat[1]=b;

    QString sDate="April 1, 2011";
    QString eDate="April 6, 2011";
    ReportDisplay* window = new ReportDisplay();
    window->showReport(sampDat,sDate,eDate,names);
    window->show();

    ReportDisplay* win=new ReportDisplay();
    win->showBarReport(a,sDate,eDate,names);
    win->show();

    close();
}

void GenerateReport::generateOccRateReport(){

    QDate startDate=ui->startdate->date();
    QDate endDate=ui->enddate->date();          //is this how its done?



    QString startDateString=startDate.toString();
    QString endDateString=endDate.toString();


    //NEED CODE HERE FOR THE CORRECT CONVERSION OF QDATE TO QSTRING!!! !!!


    int duration = startDate.daysTo(endDate);

    QVector<QVector<double> >theGraph;
    QVector<int>allFacilities=DataStorage::getAllFacilities();


    if (ui->caretypebox->isChecked()){
        QVector<int>selection;
        QVector<double>plot;
        QVector<QString>dates;
        //selection.clear();
        if (ui->acbox->isChecked()){
            for (int i=0;i<allFacilities.size();i++){
                if (DataStorage::getTotalACBeds(allFacilities[i])>0)selection.append(allFacilities[i]);
            }

            QVector<QVector<OccupancyRateEntry> >occRates;
            for (int i=0;i<selection.size();i++){
                occRates.append(DataStorage::getOccupancyRateEntries(startDateString,endDateString,"AC",selection[i]));
            }

            for (int i=0;i<occRates.size();i++){
                QVector<OccupancyRateEntry>occRate=occRates[i];
                //convert dates
                //sort occRate by date
                //for each member of occRate:
                //  if the date has not been added to dates
                //      figure out how many dates are between the last date on the list and the date given,
                //      copy the previous occRate value for all of the values in between
                //      add the date to dates and add the member's occrate value to plot, also go to the next value count
                //  else
                //      add the occrate's value to plot (without growing plot) and increment value count at j
                for (int j=0;j<occRate.size();j++){

                }
            }

        }
        if (ui->cccbox->isChecked()){

        }
        if (ui->ltcbox->isChecked()){

        }

    }
    if (ui->faciltypebox->isChecked()){
        if (ui->hospbox->isChecked()){

        }
        if (ui->nursbox->isChecked()){

        }
    }
    if (ui->selectfacilbox->isChecked()){

    }


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
