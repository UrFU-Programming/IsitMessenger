#include "LocalClient.hpp"

#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>

LocalClient::LocalClient(QObject *parent) :
    QObject(parent),
    m_socket(new QTcpSocket(this))
{
    m_size=0;

    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(onReadyRead()));

    connect(m_socket, SIGNAL(connected()),this, SLOT(onConnected()));
}

void LocalClient::connectToServer(QString address, quint16 port)
{
    m_socket->connectToHost(address, port);
}

void LocalClient::sendMessage(QString message)
{
    sendPackage("m:" + message.toUtf8());
}

void LocalClient::setNickname(QString nickname)
{
    sendPackage("setNickname:" + nickname.toUtf8());
    m_pendingNickname = nickname;
}

void LocalClient::getParticipants()
{
    sendPackage("getParticipants()");
}

void LocalClient::sendTunneledMessage(int idTo, const QByteArray &message)
{
    sendPackage("Tunnel:" + QString::number(idTo).toLocal8Bit() + ":" + message);
}

void LocalClient::onReadyRead()
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

    QByteArray data = m_socket->read(m_size);

    m_size = 0;

    if (data.startsWith("Tunnel:")){
        /**/       qDebug() << "tunnel message received";
        QList<QByteArray> dat = data.split(':');
        emit tunneledMessageReceived(dat[1].toInt(), dat[2]);
    }
    if (data.startsWith("m:")){
        emit messageReceived("123", data.mid(2, -1));
    }
    if(data.startsWith("NicknameStatus:0")){

    }
    if(data.startsWith("NicknameStatus:1")){
        m_nickname = m_pendingNickname;
    }
    if (data.startsWith("Participants:")){
        data = data.mid(13);
        QDataStream stream(data);
        QList <int> ids;
        QStringList names;
        int count = 0;
        stream >> count;
        for (int i = 0; i < count; ++i){
            int id;
            QString name;
            stream >> id >> name;
            ids.append(id);
            names.append(name);
        }
        emit participantsReceived(ids, names);
    }

    if (m_socket->bytesAvailable() > 4){
        onReadyRead();
    }
}

void LocalClient::onConnected()
{
    getParticipants();
    emit connected();
}

void LocalClient::sendPackage(const QByteArray &package)
{
    quint32 size = package.size();
    m_socket->write((char*)&size, sizeof(size));
    m_socket->write(package);
}
