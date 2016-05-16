#ifndef SERVER_HPP
#define SERVER_HPP

#include <QObject>
#include <QVector>

class QTcpServer;
class RemoteClient;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

signals:
    void serverStarted(quint16 port);
    void messageReceived(QString client, QString message);

public slots:
    void startServer(quint16 port);
    void sendMessage(QString message);
    void sendParticipants();

protected slots:
    void onClientMessageReceived(QString message);
    void onClientConnected();
private:
    QTcpServer *m_server;

    QVector<RemoteClient*> m_clients;
};

#endif // SERVER_HPP
