#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>

#include "addbed.h"
#include "assignbed.h"
#include "removepatient.h"

#include "addpatienttowaitinglist.h"
#include "removepatientfromwaitinglist.h"

#include "addfacility.h"
#include "adduser.h"

#include "viewfacility.h"
#include "viewwaitinglist.h"

#include "map.h"
#include "generatereport.h"

namespace Ui {
    class Welcome;
}

class Welcome : public QMainWindow
{
    Q_OBJECT

public:
    explicit Welcome(QWidget *parent = 0);
    ~Welcome();

private slots:
    void openAddBeds();

    void openAssignBed();
    void openRemovePatient();

    void openAddPatientToWL();
    void openRemovePatientFromWL();

    void openAddFacility();
    void openAddUser();

    void openViewFacility();
    void openViewWaitingList();
    void openViewMap();

    void openGenerateReport();

private:
    Ui::Welcome *ui;
};

#endif // WELCOME_H
