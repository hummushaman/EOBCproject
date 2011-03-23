#include "removepatient.h"
#include "ui_removepatient.h"

RemovePatient::RemovePatient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RemovePatient)
{
    ui->setupUi(this);
    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));
}

RemovePatient::~RemovePatient()
{
    delete ui;
}

void RemovePatient::clickedOK()
{
    close();

}
