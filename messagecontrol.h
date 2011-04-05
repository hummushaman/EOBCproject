#ifndef MESSAGECONTROL_H
#define MESSAGECONTROL_H

#include <QObject>
#include<QtNetwork/QUdpSocket>
#include<string>
#include<iostream>
//#include <stdio>
//#include <stdlib>

#include "eobcproject.h"

using namespace std;

class MessageControl : public QObject
{
    Q_OBJECT
public:
    explicit MessageControl(QObject *parent = 0);

    static void sendMessage(QString message, int facilID);
    static void sendMessageToAll(QString message);
    static void assignIPtoFacility(QString ipaddress, int facilID);

private slots:
    void readPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    quint16 port;


};

#endif // MESSAGECONTROL_H


