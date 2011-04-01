#ifndef RECEIVEMESSAGE_H
#define RECEIVEMESSAGE_H

#include <QObject>
#include<QtNetwork/QUdpSocket>
#include<string>
#include<iostream>
//#include <stdio>
//#include <stdlib>


#include"eobcproject.h"


class ReceiveMessage : public QObject
{
    Q_OBJECT
public:
    explicit ReceiveMessage(QObject *parent = 0);

private slots:
    static void readPendingDatagrams();

private:
    QUdpSocket *serverSocket;
    quint16 port;

};

#endif // RECEIVEMESSAGE_H


