#include "welcome.h"
#include "ui_welcome.h"

Welcome::Welcome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Welcome)
{
    ui->setupUi(this);
    this->isEnabled();

    connect(ui->actionAdd_beds, SIGNAL(triggered()),this,SLOT(openAddBeds()));
    connect(ui->actionAssign_bed, SIGNAL(triggered()),this,SLOT(openAssignBed()));
    connect(ui->actionRemove_patient_from_bed, SIGNAL(triggered()),this,SLOT(openRemovePatient()));

    connect(ui->actionAdd_patient, SIGNAL(triggered()),this,SLOT(openAddPatientToWL()));
    connect(ui->actionRemove_patient, SIGNAL(triggered()),this,SLOT(openRemovePatientFromWL()));

    connect(ui->actionAdd_facility, SIGNAL(triggered()),this,SLOT(openAddFacility()));
    connect(ui->actionAdd_user, SIGNAL(triggered()),this,SLOT(openAddUser()));

    connect(ui->actionView_facility_information, SIGNAL(triggered()),this,SLOT(openViewFacility()));
    connect(ui->actionView_waiting_list, SIGNAL(triggered()),this,SLOT(openViewWaitingList()));

    connect(ui->actionViewMap, SIGNAL(triggered()),this,SLOT(openViewMap()));
    connect(ui->actionGenerate_report,SIGNAL(triggered()),this,SLOT(openGenerateReport()));

}

Welcome::~Welcome()
{
    delete ui;
}

void Welcome::openViewMap()
{
    Map* aWindow = new Map();
    aWindow->show();
}

void Welcome::openAddBeds()
{

    AddBed* aWindow = new AddBed();
    aWindow->show();
    //close();
}

void Welcome::openAssignBed()
{

    AssignBed* aWindow = new AssignBed();
    aWindow->show();
    //close();
}
void Welcome::openRemovePatient()
{

    RemovePatient* aWindow = new RemovePatient();
    aWindow->show();
    //close();
}

void Welcome::openAddPatientToWL()
{
    AddPatientToWaitingList* aWindow = new AddPatientToWaitingList();
    aWindow->show();
   // close();
}


void Welcome::openRemovePatientFromWL()
{
    RemovePatientFromWaitingList* aWindow = new RemovePatientFromWaitingList();
    aWindow->show();
    //close();
}

void Welcome::openAddFacility()
{

    AddFacility* aWindow = new AddFacility();
    aWindow->show();
    //close();
}

void Welcome::openAddUser()
{

    AddUser* aWindow = new AddUser();
    aWindow->show();
    //close();
}

void Welcome::openViewFacility()
{

    ViewFacility* aWindow = new ViewFacility();
    aWindow->show();
    //close();
}
void Welcome::openViewWaitingList()
{

    ViewWaitingList* aWindow = new ViewWaitingList();
    aWindow->show();
    //close();
}
void Welcome::openGenerateReport()
{

    GenerateReport* aWindow = new GenerateReport();
    aWindow->show();
}



