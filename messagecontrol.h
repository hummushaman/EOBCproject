#ifndef MESSAGECONTROL_H
#define MESSAGECONTROL_H

#include <QObject>
#include<QtNetwork/QUdpSocket>
#include<string>
#include<iostream>
//#include <stdio>
//#include <stdlib>

using namespace std;

class MessageControl : public QObject
{
    Q_OBJECT
public:
    explicit MessageControl(QObject *parent = 0);

    static void sendMessage(QString message, int facilID);
    static void sendMessageToAll(QString message);

private slots:
    //void readPendingDatagrams();

private:
    static QUdpSocket *serverSocket;
    static quint16 port;

    static QMap<int, QString> facilities;

};

#endif // MESSAGECONTROL_H


