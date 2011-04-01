#include "inpatient.h"

InPatient::InPatient(QString aHCN,QString aFirstName,QString aLastName,QString rCare,QString oCare,QString dAdmitted,QString cf)
{
    HCN = aHCN;
    firstname = aFirstName;
    lastname = aLastName;
    occCare=oCare;
    reqCare=rCare;
    dateAdmitted=dAdmitted;
    currentFacility=cf;
}

QString InPatient::getDateAdmitted(){

}

QString InPatient::getRequiredCare(){

}

QString InPatient::getOccupiedCare(){

}


