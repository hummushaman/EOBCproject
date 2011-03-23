#include "viewwaitinglist.h"
#include "ui_viewwaitinglist.h"

ViewWaitingList::ViewWaitingList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewWaitingList)
{
    ui->setupUi(this);
}

ViewWaitingList::~ViewWaitingList()
{
    delete ui;
}

