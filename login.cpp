/********
  CLASS NAME: Login
  PURPOSE: Displays the form that system displays upon startup. The form requests login information from the user.
           If login information is valid ( check with data storage classes), the welcome window opens.

  TRACEABILITY: This class traces back to the LoginControl from Deliverable 2

  CREATED BY: Nisrin Abou-Seido
  LAST MODIFIED: March 20, 2011

***********/


#include "login.h"
#include "ui_login.h"


Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{

    ui->setupUi(this);

    //ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    connect(ui->loginOK,SIGNAL(clicked()),this,SLOT(checkLogin()));
}

Login::~Login()
{
    delete ui;
}

void Login::checkLogin()
{
    //****check username and password***

    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    bool isValid = DataStorage::isLoginValid(username, password);   //write part of the function to test this (get the configurated default user)

    if(isValid)
    {
        //get the user type
        DataStorage::currentUserType= DataStorage::getUserType(username);

        Welcome* welcome_window = new Welcome();
        close();
        welcome_window->show();



    }
    else
    {
        //return an error message and stay on the
        QMessageBox msgbox;
        msgbox.setText("This username/password combination does not exist.");
        msgbox.exec();
    }




    //disable certain "welcome" window options

    //if (usertype = facility staff)
    //they can only change information about this facility...


}
