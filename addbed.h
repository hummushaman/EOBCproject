#ifndef ADDBED_H
#define ADDBED_H

#include <QMainWindow>


#include "eobcproject.h"

namespace Ui {
    class AddBed;
}

class AddBed : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddBed(QWidget *parent = 0);
    ~AddBed();
private slots:
    void clickedOK(); // user clicks on the ok button

private:
    Ui::AddBed *ui;
};

#endif // ADDBED_H
