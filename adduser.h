#ifndef ADDUSER_H
#define ADDUSER_H

#include <QMainWindow>
#include "eobcproject.h"

namespace Ui {
    class AddUser;
}

class AddUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = 0);
    ~AddUser();

private slots:
    void clickedOK();

private:
    Ui::AddUser *ui;
};

#endif // ADDUSER_H
