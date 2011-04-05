/*Name:MessageControl
  Purpose: Send and receive UDP datagrams through a socket

      Traces to subsystem: NotifyAllFacilities
*/

#include "messagecontrol.h"


MessageControl::MessageControl(QObject *parent) :
    QObject(parent)
{
    QSettings settings("JNFconfig");
    udpSocket = new QUdpSocket();
    port = settings.value("port").toInt();

    QMessageBox msgbox;

    //bind to the port in order to receive messages from others on this port
    if(!udpSocket->bind(QHostAddress(DataStorage::myFacilityIPaddress), port, QUdpSocket::ShareAddress))
    {
        msgbox.setText("bind failed");
        msgbox.exec();
    }
    else
    {
        //ui->label->setText(tr("made it to binding"));
        if(connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams())))
        {
            msgbox.setText("connected");
            msgbox.exec();
        }
        else{
            msgbox.setText("not connected");
            msgbox.exec();
        }
    }
}

void MessageControl::readPendingDatagrams()
{
    QMessageBox msgbox;
    msgbox.setText("received a datagram");
    msgbox.exec();

    QHostAddress* anAddress;
    QString theMessage;

    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());


        int errorcode = udpSocket->readDatagram(datagram.data(), datagram.size(), anAddress);
        if(errorcode)

        theMessage = datagram.data();

        msgbox.setText(theMessage);
        msgbox.exec();
        //ui->receive->setText(tr("Received datagram: \"%1\"").arg(datagram.data()));
    }

    //get the ipaddress of the facility who sent the message
    QString senderIP = anAddress->toString();

    //QSettings settings("JNFconfig");
    //settings.beginWriteArray("facilities");

    //settings.setValue("3", senderIP);

    //parse the message and get the id of the facility who sent the message
    //XMLParser xmlparser = new XMLParser();
    int facilID = 0;
    //facilID= xmlparser.parseMessage(theMessage,senderIP);

    if(facilID != -1)// -1 is returned when the message is not a rebuild message
    {
        //check whether this id is in the config file. if it isnt, add it.

        QSettings settings("JNFconfig");
        settings.beginWriteArray("facilities");

        if(!settings.contains(QString::number(facilID)))
        {
            settings.setValue(QString::number(facilID),senderIP);
        }
    }

}

void MessageControl::assignIPtoFacility(QString ipaddress, int facilID)
{
    QSettings settings("JNFconfig");
    settings.beginWriteArray("facilities");

    if(!settings.contains(QString::number(facilID)))
    {
        settings.setValue(QString::number(facilID),ipaddress);
    }
}

void MessageControl::sendMessage(QString message, int facilityID) //this is a static method
{
    QSettings settings("JNFconfig");
    QUdpSocket* udpSocket = new QUdpSocket();
    QString recipientIP;
    QMessageBox msgbox;

    int port = settings.value("port").toInt();

    if(!settings.contains(QString::number(facilityID)))
    {
        msgbox.setText("Cannot send a message to an offline facility");
        msgbox.exec();
    }
    else
    {
        recipientIP = settings.value(QString::number(facilityID)).toString();
    }

    //need to get the ipaddress of facility
    int errorCode = udpSocket->writeDatagram(message.toLatin1(), QHostAddress(recipientIP), port);

}

void MessageControl::sendMessageToAll(QString message)
{

    //read configuration file and create list of current facilities

    QSettings settings("JNFconfig");

    QUdpSocket* sendSocket = new QUdpSocket();
    int port = settings.value("port").toInt();
    qDebug() <<"port"<<port;

    //the following code reads the IP address given the facilityID.

    settings.beginReadArray("lamdas");
    static QMap<int, QString> servers;

    qDebug() <<"lamdas******:";
    for(int i=1; i<=12;i++)
    {

        QString anIP = settings.value(QString::number(i)).toString();
        qDebug() << anIP<<"\n";
        servers.insert(i,anIP);
    }

    settings.endArray();

    /*
    QString s1 = settings.value("1").toString();
    QString s2 = settings.value("2").toString();
    QString s3 = settings.value("3").toString();
    QString s4 = settings.value("4").toString();
    QString s5 = settings.value("5").toString();
    QString s6 = settings.value("6").toString();
    QString s7 = settings.value("7").toString();
    QString s8 = settings.value("8").toString();
    QString s9 = settings.value("9").toString();
    QString s10 = settings.value("10").toString();
    QString s11 = settings.value("11").toString();
    QString s12 = settings.value("12").toString();*/

    //send the message to all the facilities that are in the "facilities" map.
    for(int i= 0; i < servers.size();i++)
    {
        int errorCode = sendSocket->writeDatagram(message.toLatin1(),QHostAddress(servers.value(i)),port);
        if(errorCode == -1)
            qDebug() <<"sending message was unsuccessful";
        else
            qDebug() <<"message was sent";
    }

}
