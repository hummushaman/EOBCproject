#ifndef PATIENT_H
#define PATIENT_H

#include <QObject>

class Patient
{
public:
    Patient(QString HCN,QString firstname,QString lastname);

    QString getHCN();
    QString getFirstname();
    QString getLastname();



private:
    QString HCN;
    QString firstname;
    QString lastname;


};

#endif // PATIENT_H
