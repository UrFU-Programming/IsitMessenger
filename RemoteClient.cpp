#include "RemoteClient.hpp"

#include <QTcpSocket>

RemoteClient::RemoteClient(QTcpSocket *socket, QObject *parent) :
    QObject(parent),
    m_socket(socket)
{
    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(onReadyRead()));
}

void RemoteClient::sendMessage(QString message)
{
    m_socket->write("m:");
    m_socket->write(message.toUtf8());
}

void RemoteClient::setNickname(QString nickname)
{
    m_pendingNickname = nickname;
}

void RemoteClient::sendParticipants(const QList<int> &ids, const QStringList &names)
{

}

void RemoteClient::onReadyRead()
{
    QString message = m_socket->readAll();

    if(message.startsWith("m:")){
        emit messageReceived(message.mid(2));
    } else if (message.startsWith("setNickname:")) {
        QString nick = message.mid(12);
        setNickname(nick);
        sendMessage("nickNameStatus:1");
    } else if (message.startsWith("getParticipants()")){
        emit wantParticipants();
    }
}

QString RemoteClient::nickName()
{
    return m_pendingNickname;
}
