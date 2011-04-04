#include "patient.h"
Patient::Patient(){}
Patient::Patient(QString aHCN, QString aFirstname, QString aLastname, QString aRequiredCare)
{
    HCN = aHCN;
    firstname = aFirstname;
    lastname = aLastname;

    requiredCare=aRequiredCare;
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


QString Patient::getRequiredCare()
{
    return requiredCare;
}
