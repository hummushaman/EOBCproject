#ifndef PATIENT_H
#define PATIENT_H

#include <QObject>

class Patient
{
public:
    Patient();
    Patient(QString HCN,QString firstname,QString lastname, QString requiredCare);

    QString getHCN();
    QString getFirstname();
    QString getLastname();

    QString getRequiredCare();

private:
    QString HCN;
    QString firstname;
    QString lastname;
    QString requiredCare;
};


#endif // PATIENT_H

