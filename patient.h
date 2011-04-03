#ifndef PATIENT_H
#define PATIENT_H

#include <QObject>

class Patient
{
public:
    Patient(QString HCN,QString firstname,QString lastname,QString dateAdded, QString requiredCare);

    QString getHCN();
    QString getFirstname();
    QString getLastname();
    QString getDateAdded();
    QString getRequiredCare();

private:
    QString HCN;
    QString firstname;
    QString lastname;
    QString dateAdded;
    QString requiredCare;
};


#endif // PATIENT_H
