#ifndef GENERATEREPORT_H
#define GENERATEREPORT_H

#include <QMainWindow>

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

};

#endif // GENERATEREPORT_H
