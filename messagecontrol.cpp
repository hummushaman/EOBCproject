#include "messagecontrol.h"

#include "eobcproject.h"


MessageControl::MessageControl(QObject *parent) :
    QObject(parent)
{
    QSettings settings("JNFconfig");
    serverSocket = new QUdpSocket();
    port = settings.value("port").toInt();

    //bind to the port in order to receive messages from others on this port
    if(!serverSocket->bind(QHostAddress(DataStorage::myFacilityIPaddress), port, QUdpSocket::ShareAddress))
    {
        //ui->label->setText(tr("bind failed"));
    }
    else
    {
        //ui->label->setText(tr("made it to binding"));
        if(connect(serverSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams())))
        {
            //ui->label->setText(tr("connected"));
        }
        else{
            //ui->label->setText(tr("not connected"));
        }
    }
}

void MessageControl::readPendingDatagrams()
{
    //ui->label->setText(tr("received data"));

    QHostAddress* anAddress;

    while (serverSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(serverSocket->pendingDatagramSize());


        serverSocket->readDatagram(datagram.data(), datagram.size(), anAddress); //OKAY?
        //ui->receive->setText(tr("Received datagram: \"%1\"").arg(datagram.data()));
    }

    //get the ipaddress of the facility who sent the message
    QString senderIP = anAddress->toString();

    QSettings settings("JNFconfig");
    settings.beginWriteArray("facilities");

    settings.setValue("3", senderIP);

    //check whether this ipaddress is in the config file. if not, add it.

}


void MessageControl::sendMessage(QString message, int facilityID) //this is a static method
{
    QSettings settings("JNFconfig");
    QUdpSocket* serverSocket = new QUdpSocket();
    int port = settings.value("port").toInt();

    int errorCode = serverSocket->writeDatagram(message.toLatin1(), QHostAddress("134.117.27.75"), port);


}

void MessageControl::sendMessageToAll(QString message)
{

    //read configuration file and create list of current facilities

    QSettings settings("JNFconfig");

    QUdpSocket* serverSocket = new QUdpSocket();
    int port = settings.value("port").toInt();

    //the following code reads the IP address given the facilityID.

    settings.beginReadArray("facilities");
    QString s1 = settings.value("1").toString();
    QString s2 = settings.value("2").toString();
    settings.endArray();

    static QMap<int, QString> facilities;

    if(s1 != "") facilities.insert(1,s1);
    if(s2 != "") facilities.insert(2,s2);


    //send the message to all the facilities that are in the "facilities" map.
    for(int i= 0; i> facilities.size();i++)
    {
        int errorCode = serverSocket->writeDatagram(message.toLatin1(),QHostAddress(facilities.value(i)),port);
    }

}
