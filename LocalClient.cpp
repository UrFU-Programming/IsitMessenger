#include "LocalClient.hpp"

#include <QTcpSocket>
#include <QDebug>

LocalClient::LocalClient(QObject *parent) :
    QObject(parent),
    m_socket(new QTcpSocket(this))
{
    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(onReadyRead()));

    connect(m_socket, SIGNAL(connected()),this, SIGNAL(connected()));
}

void LocalClient::connectToServer(QString address, quint16 port)
{
    m_socket->connectToHost(address, port);
}

void LocalClient::sendMessage(QString message)
{
    m_socket->write("m:");
    m_socket->write(message.toUtf8());
}

void LocalClient::setNickname(QString nickname)
{
    m_socket->write("setNickname:" + nickname.toUtf8());
    m_pendingNickname = nickname;
}

void LocalClient::getParticipants()
{

}

void LocalClient::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    if (data.startsWith("m:")){
        emit messageReceived("123", data.mid(2, -1));
    }
    if(data.startsWith("NicknameStatus:0")){

    }
    if(data.startsWith("NicknameStatus:1")){
        m_nickname = m_pendingNickname;
    }
}
