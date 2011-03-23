#include "viewfacility.h"
#include "ui_viewfacility.h"

ViewFacility::ViewFacility(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewFacility)
{
    ui->setupUi(this);
}

ViewFacility::~ViewFacility()
{
    delete ui;
}


