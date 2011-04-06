/********
***********/

#include "adduser.h"
#include "ui_adduser.h"

AddUser::AddUser(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::AddUser)
{
    ui->setupUi(this);
    connect(ui->OKButton,SIGNAL(clicked()),this,SLOT(clickedOK()));


}

AddUser::~AddUser()
{
    delete ui;
}

void AddUser::clickedOK()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    QString usertype = ui->comboBox_types->currentText();

    if((username == "") || (password == "") || (usertype == ""))
    {
        QMessageBox msgbox;
        msgbox.setText("Please fill out all fields");
        msgbox.exec();
    }
    else
    {
        //bool exists = DataStorage::isLoginValid(username,password);

        bool exists = DataStorage::isUsernameInUse(username, password);
        if(!exists)
        {
            DataStorage::addUser(username,password,usertype);
            close();
        }
        else
        {
            QMessageBox msgbox;
            msgbox.setText("Username is in use. Please enter in a different username");
            msgbox.exec();
        }
    }
}
