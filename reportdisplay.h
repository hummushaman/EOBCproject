#ifndef REPORTDISPLAY_H
#define REPORTDISPLAY_H

#include <QMainWindow>
#include <qvector.h>
#include <QVector>
#include <qgraphicsscene.h>
#include <QDate>

namespace Ui {
    class ReportDisplay;
}

class ReportDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReportDisplay(QWidget *parent = 0);
    ~ReportDisplay();
    void showReport(QVector< QVector<double> >graph, QString startDate, QString endDate,QVector<QString>names);
    void showBarReport(QVector<double>graph, QString startDate, QString endDate,QVector<QString>names);



private:
    Ui::ReportDisplay *ui;
};

#endif // REPORTDISPLAY_H
