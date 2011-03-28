#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

#include "welcome.h"
#include "ui_welcome.h"

namespace Ui {
    class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void checkLogin();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
