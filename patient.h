#ifndef PATIENT_H
#define PATIENT_H

#include <QObject>

class Patient
{
public:
    Patient(QString HCN,QString firstname,QString lastname);
    Patient();
    QString getHCN();
    QString getFirstname();
    QString getLastname();
    QString getDateAdded();



protected:
    QString HCN;
    QString firstname;
    QString lastname;
    QString dateAdded;



};

#endif // PATIENT_H
