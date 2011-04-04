#ifndef REMOVEPATIENTFROMWAITINGLIST_H
#define REMOVEPATIENTFROMWAITINGLIST_H

#include <QMainWindow>

//#include"datastorage.h"


#include "eobcproject.h"
#include <QListWidgetItem>
#include <QMessageBox>

namespace Ui {
    class RemovePatientFromWaitingList;
}

class RemovePatientFromWaitingList : public QMainWindow
{
    Q_OBJECT

public:
    explicit RemovePatientFromWaitingList(QWidget *parent = 0);
    ~RemovePatientFromWaitingList();

private slots:
    void displayPatients();
    void clickedOK();

private:
    Ui::RemovePatientFromWaitingList *ui;
};

#endif // REMOVEPATIENTFROMWAITINGLIST_H
