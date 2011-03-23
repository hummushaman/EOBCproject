#ifndef REMOVEPATIENTFROMWAITINGLIST_H
#define REMOVEPATIENTFROMWAITINGLIST_H

#include <QMainWindow>

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
    void clickedOK();

private:
    Ui::RemovePatientFromWaitingList *ui;
};

#endif // REMOVEPATIENTFROMWAITINGLIST_H
