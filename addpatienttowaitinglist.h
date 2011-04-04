#ifndef ADDPATIENTTOWAITINGLIST_H
#define ADDPATIENTTOWAITINGLIST_H

#include <QMainWindow>

//#include "datastorage.h"
//#include <QMessageBox>

#include "eobcproject.h"

namespace Ui {
    class AddPatientToWaitingList;
}

class AddPatientToWaitingList : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddPatientToWaitingList(QWidget *parent = 0);
    ~AddPatientToWaitingList();

private slots:
    void clickedOK();

private:
    Ui::AddPatientToWaitingList *ui;
};

#endif // ADDPATIENTTOWAITINGLIST_H
