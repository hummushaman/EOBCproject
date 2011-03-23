#ifndef FACILITY_H
#define FACILITY_H

#include<QString>


class facility
{
private:
    int id;
    QString name;
    QString type;

public:
        facility(int anID, QString aName, QString aType);
        int getID();
        QString getName();
        QString getType();

};

#endif // FACILITY_H
