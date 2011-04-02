#ifndef INPATIENT_H
#define INPATIENT_H
#include <patient.h>
#include <qstring.h>

class InPatient : public Patient
{

private:
    QString reqCare;
    QString occCare;
    QString dateAdmitted;
    QString currentFacility;


public:
    InPatient(QString aHCN,QString aFirstName,QString aLastName,QString rCare,QString oCare, QString dAdmitted, QString currentFacility);
    QString getDateAdmitted();
    QString getRequiredCare();
    QString getOccupiedCare();
};

#endif // INPATIENT_H
