#include "ServerDiscovery.hpp"

#include <QDebug>
#include <QUdpSocket>
#include <QNetworkInterface>

static const quint16 s_udpPort = 29031;
static const QByteArray s_header = "IsitMessenger";

ServerDiscovery::ServerDiscovery(QObject *parent) :
    QObject(parent)
{
    m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(QHostAddress::Any, s_udpPort, QAbstractSocket::ShareAddress|QAbstractSocket::ReuseAddressHint);

    connect(m_udpSocket, SIGNAL(readyRead()),
            this, SLOT(onUdpMessageReceived()));

}

void ServerDiscovery::addServer(quint16 port)
{
     m_port = port;
     announceServer();
}

void ServerDiscovery::onUdpMessageReceived()
{
    qDebug() << Q_FUNC_INFO;
    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(m_udpSocket->pendingDatagramSize());
        QHostAddress address;
        m_udpSocket->readDatagram(buffer.data(), buffer.size(), &address);
        if (buffer == s_header+":?"){
            qDebug() << Q_FUNC_INFO << "Server requested by client" << address.toString();
            announceServer();
        } else {
            QList<QByteArray> lBuff = buffer.split(':');
            quint16 port = lBuff[1].toUInt();
            qDebug() << Q_FUNC_INFO << "Server found at" << address.toString() << ":" << port;
            emit serverFound(address.toString(),port);
        }
    }
}

void ServerDiscovery::announceServer()
{
    for (QNetworkInterface iface : QNetworkInterface::allInterfaces()){
        for (QNetworkAddressEntry entry : iface.addressEntries()) {
            QString datagram = s_header + ":" + QString::number(m_port);
            m_udpSocket->writeDatagram(datagram.toLatin1(), entry.broadcast(), s_udpPort);
        }
    }
}

void ServerDiscovery::discoveryServer()
{
    for (QNetworkInterface iface : QNetworkInterface::allInterfaces()){
        for (QNetworkAddressEntry entry : iface.addressEntries()) {
            QString datagram = s_header + ":?";
            m_udpSocket->writeDatagram(datagram.toLatin1(), entry.broadcast(), s_udpPort);
        }
    }
}
