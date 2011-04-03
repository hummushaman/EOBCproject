#ifndef GENERATEREPORT_H
#define GENERATEREPORT_H

#include <QMainWindow>
#include <datastorage.h>
#include <qvector.h>
#include <QVector>
#include <qgraphicsscene.h>

//#include "ui_reportdisplay.h"
#include "reportdisplay.h"

namespace Ui {
    class GenerateReport;
}

class GenerateReport : public QMainWindow
{
    Q_OBJECT

public:
    explicit GenerateReport(QWidget *parent = 0);
    ~GenerateReport();



private:
    Ui::GenerateReport *ui;

private slots:
    void waitTimesBoxClicked();
    void careMismatchBoxClicked();
    void occupancyRateBoxClicked();
    void waitingListSizeBoxClicked();

    void GenerateReportButtonClicked();

    void generateOccRateReport();
    void generateFakeReports();
    void generateNoTimeReport();
    void generateNoTimeOccRateReport();

    void generateNoTimeWaitTimesReport();
    void generateNoTimeWaitingListSizeReport();
    void generateNoTimeCareMismatchReport();

};

#endif // GENERATEREPORT_H
