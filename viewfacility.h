#ifndef VIEWFACILITY_H
#define VIEWFACILITY_H

#include <QMainWindow>
#include "eobcproject.h"

namespace Ui {
    class ViewFacility;
}

class ViewFacility : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewFacility(QWidget *parent = 0);
    ~ViewFacility();

private slots:
    void displayInformation();

private:
    Ui::ViewFacility *ui;
};

#endif // VIEWFACILITY_H
