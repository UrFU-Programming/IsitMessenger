#include "Server.hpp"
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

#include "RemoteClient.hpp"

Server::Server(QObject *parent) :
    QObject(parent),
    m_server(new QTcpServer(this))
{
}

void Server::startServer(quint16 port)
{
    bool started = m_server->listen(QHostAddress::Any, port);

    connect(m_server, SIGNAL(newConnection()),
            this, SLOT(onClientConnected()));

    if (started) {
        emit serverStarted(m_server->serverPort());
        qDebug() << Q_FUNC_INFO << "Server started on port :" << m_server->serverPort();
    }
}

void Server::sendMessage(QString message)
{
    for (RemoteClient *client : m_clients) {
        client->sendMessage(message);
    }
}

void Server::onClientMessageReceived(QString message)
{
    RemoteClient *client = qobject_cast<RemoteClient*>(sender());

    sendMessage(message);

    emit messageReceived(client->nickName(), message);
}

void Server::onClientConnected()
{
    QTcpSocket *clientSocket = m_server->nextPendingConnection();

    RemoteClient *client = new RemoteClient(clientSocket, this);

    m_clients << client;

    client->setNickname(clientSocket->peerAddress().toString());

    for (RemoteClient *client : m_clients) {
        client->sendMessage("client connect" + clientSocket->peerAddress().toString());
    }

    connect(client,SIGNAL(messageReceived(QString)),
            this,SLOT(onClientMessageReceived(QString)));
    connect(client,SIGNAL(wantParticipants()),
            this, SLOT(sendParticipants()));
}

void Server::sendParticipants()
{
    RemoteClient *client = qobject_cast<RemoteClient*>(sender());
    int id = 0;
    QList<int> ids;
    QStringList names;
    for (RemoteClient *client : m_clients) {
        ids.append(id);
        names.append(client->nickName());
        id ++;
    }
    client->sendParticipants(ids, names);
}

void Server::onTunneledMessageReceived(int idTo, const QByteArray &message)
{
    RemoteClient *clientFrom = qobject_cast<RemoteClient*>(sender());
    m_clients[idTo]->sendTunneledMessage(m_clients.indexOf(clientFrom), message);
}
