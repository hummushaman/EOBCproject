#include "inpatient.h"
Inpatient::Inpatient(){}
Inpatient::Inpatient(QString aHCN,QString aFirstName,QString aLastName,QString aRequiredCare,QString aCurrentCare,QString aDateAdmitted,int cf)
    :Patient(aHCN, aFirstName, aLastName, aRequiredCare)
{
    currentCare= aCurrentCare;
    dateAdmitted=aDateAdmitted;
    currentFacility=cf;
}

QString Inpatient::getDateAdmitted()
{
    return dateAdmitted;
}

QString Inpatient::getCurrentCare()
{
    return currentCare;
}

int Inpatient::getCurrentFacility()
{
    return currentFacility;
}

