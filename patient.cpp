#include "patient.h"

Patient::Patient(QString aHCN, QString aFirstname, QString aLastname, QString aDateAdded, QString aRequiredCare)
{
    HCN = aHCN;
    firstname = aFirstname;
    lastname = aLastname;
    dateAdded = aDateAdded;
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

QString Patient::getDateAdded()
{
    return dateAdded;
}
