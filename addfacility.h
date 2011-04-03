#ifndef ADDFACILITY_H
#define ADDFACILITY_H

#include <QMainWindow>
#include "eobcproject.h"

namespace Ui {
    class AddFacility;
}

class AddFacility : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddFacility(QWidget *parent = 0);
    ~AddFacility();

private slots:
    void clickedOK();

private:
    Ui::AddFacility *ui;
};

#endif // ADDFACILITY_H
