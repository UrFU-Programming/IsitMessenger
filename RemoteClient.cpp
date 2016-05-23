#include "RemoteClient.hpp"

#include <QTcpSocket>

#include <QDataStream>

RemoteClient::RemoteClient(QTcpSocket *socket, QObject *parent) :
    QObject(parent),
    m_socket(socket)
{
    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(onReadyRead()));
}

void RemoteClient::sendMessage(QString message)
{
    sendPackage("m:" + message.toUtf8());
}

void RemoteClient::setNickname(QString nickname)
{
    m_pendingNickname = nickname;
}

void RemoteClient::sendParticipants(const QList<int> &ids, const QStringList &names)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << ids.size();

    for (int i = 0; i < ids.size(); ++i){
        stream << ids[i] << names[i];
    }

    sendPackage("Participants:" + data);
}

void RemoteClient::sendTunneledMessage(int idFrom, const QByteArray &message)
{
    sendPackage("Tunnel:" + QString::number(idFrom).toUtf8() + ":" + message);
}

void RemoteClient::onReadyRead()
{
    if (m_size == 0) {
        if (m_socket->bytesAvailable() < 4) {
            return;
        }
        QByteArray sizeBytes = m_socket->read(4);
        m_size = *(quint32 *)(sizeBytes.constData());
    }

    if (m_socket->bytesAvailable() < m_size){
        return;
    }

    QByteArray message = m_socket->read(m_size);

    m_size = 0;

    if(message.startsWith("m:")){
        emit messageReceived(message.mid(2));
    } else if (message.startsWith("setNickname:")) {
        QString nick = message.mid(12);
        setNickname(nick);
        sendMessage("nickNameStatus:1");
    } else if (message.startsWith("getParticipants()")){
        emit wantParticipants();
    }

    if(message.startsWith("Tunnel:")){

        QList<QByteArray> splitMessage = message.split(':');
        emit tunneledMessageReceived(splitMessage[1].toInt(),splitMessage[2]);
    }

    if (m_socket->bytesAvailable() > 4){
        onReadyRead();
    }

}

void RemoteClient::sendPackage(const QByteArray &package)
{
    quint32 size = package.size();
    m_socket->write((char*)&size, sizeof(size));
    m_socket->write(package);
}

QString RemoteClient::nickName()
{
    return m_pendingNickname;
}
