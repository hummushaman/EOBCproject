#include "patient.h"

Patient::Patient()
{

}

Patient::Patient(QString aHCN, QString aFirstname, QString aLastname)
{
    HCN = aHCN;
    firstname = aFirstname;
    lastname = aLastname;

}

QString Patient::getHCN()
{
    return HCN;
}

QString Patient::getFirstname()
{
    return firstname;
}

QString Patient::getLastname()
{
    return lastname;
}

QString Patient::getDateAdded()
{

}

