#ifndef SERVERDISCOVERY_HPP
#define SERVERDISCOVERY_HPP

#include <QObject>

class QUdpSocket;

class ServerDiscovery : public QObject
{
    Q_OBJECT
public:
    explicit ServerDiscovery(QObject *parent = 0);
    void discoveryServer();

signals:
    void serverFound(QString ip, quint16 port);

public slots:
    void addServer(quint16 port);

private slots:
    void onUdpMessageReceived();

    void announceServer();

private:
    QUdpSocket *m_udpSocket;
    quint16 m_port;
    bool m_haveServer;

};

#endif // SERVERDISCOVERY_HPP
