#ifndef LOCALCLIENT_HPP
#define LOCALCLIENT_HPP

#include <QObject>

class QTcpSocket;

class LocalClient : public QObject
{
    Q_OBJECT
public:
    explicit LocalClient(QObject *parent = 0);

signals:
    void connected();
    void messageReceived(QString client, QString message);
    void participantsReceived(const QList<int> &ids, const QStringList &names);
    void tunneledMessageReceived(int idFrom, const QByteArray &message);

public slots:
    void connectToServer(QString address, quint16 port);
    void sendMessage(QString message);
    void setNickname(QString nickname);
    void getParticipants();
    void sendTunneledMessage(int idTo, const QByteArray &message);

protected slots:
    void onReadyRead();
    void onConnected();
    void sendPackage(const QByteArray &package);

protected:
    QTcpSocket *m_socket;
    QString m_pendingNickname;
    QString m_nickname;
    quint32 m_size;
};

#endif // LOCALCLIENT_HPP
