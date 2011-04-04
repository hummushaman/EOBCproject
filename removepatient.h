#ifndef REMOVEPATIENT_H
#define REMOVEPATIENT_H

#include <QMainWindow>
#include "eobcproject.h"

namespace Ui {
    class RemovePatient;
}

class RemovePatient : public QMainWindow
{
    Q_OBJECT

public:
    explicit RemovePatient(QWidget *parent = 0);
    ~RemovePatient();

private slots:
    void clickedOK();
    void displayPatients();

private:
    Ui::RemovePatient *ui;
};

#endif // REMOVEPATIENT_H
