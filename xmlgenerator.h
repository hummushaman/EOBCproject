#ifndef XMLGENERATOR_H
#define XMLGENERATOR_H

 #include <QString>
#include <QtXml/qdom.h>
#include <datastorage.h>
#include <qvector.h>

class xmlgenerator
{
public:
    xmlgenerator();
    static QString patientOperationXML(QString operation, QString healthCard,int facilNum, int areaNum, bool remote, QString dateAdded, QString dateAdmitted, QString first, QString last, int reqCare, int occCare); //facilNum = -1 means we are dealing with a waiting list
    static QString rebuild();
    static QString rebuildResponse();
    static QString addBeds(int facilNum, int areaNum, int ac, int ccc, int ltc, bool remote);
    static QString addFacility(int facilNum, int areaNum,int xcoor, int ycoor, int ac, int ccc, int ltc, QString name, bool remote,QString type);
};

#endif // XMLGENERATOR_H
