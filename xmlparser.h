#ifndef XMLPARSER_H
#define XMLPARSER_H
#include <QFile>

#include <QtXml/qdom.h>
#include <datastorage.h>
#include <messagecontrol.h>
#include <xmlgenerator.h>
//#include <QtXml/QDomDocument>

using namespace std;

class XMLParser
{
    QDomDocument original;
    QString ip;
    int returnId;

public:
    //QString dateFormat;
    XMLParser();
    int parseMessage(QString message, QString ip);
    int startParsing(QDomElement element);
    int parseFacilityOrWaitingList(QDomElement ForW,bool remote, int area, QString operation);
    int parseFacility(QDomElement ForW,bool remote, int area, QString operation);
    int parseWaitingList(QDomElement ForW,bool remote, int area, QString operation);
    int facilityOperation(QDomElement facility,QString operation, int area);
    int parsePlacePatient(QDomElement patient, int facilNum);
    int parseEjectPatient(QDomElement patient, int facilNum);
    int parseWaitingListOperation(QDomElement waitingList, int area, QString operation);
    int parseAddPatientToWL(QDomElement patient, int area);
    int parseRemovePatientFromWL(QDomElement patient, int area);
    int parseAddNewFacility(QDomElement facility, int facilNum,int area);
    int parseAddBeds(QDomElement facility, int facilNum);
};

#endif // XMLPARSER_H
