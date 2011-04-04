#ifndef INPATIENT_H
#define INPATIENT_H
#include "patient.h"
class Inpatient : public Patient
{
public:
    Inpatient();
    Inpatient(QString aHCN,QString aFirstName,QString aLastName,QString aRequiredCare,QString aCurrentCare,QString aDateAdmitted,int cf);
    QString getDateAdmitted();
    QString getCurrentCare();
    int getCurrentFacility();
private:
    QString currentCare;
    QString dateAdmitted;
    int currentFacility;

};

#endif // INPATIENT_H
