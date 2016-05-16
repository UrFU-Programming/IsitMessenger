#ifndef REMOTECLIENT_HPP
#define REMOTECLIENT_HPP

#include <QObject>

class QTcpSocket;

class RemoteClient : public QObject
{
    Q_OBJECT
public:
    explicit RemoteClient(QTcpSocket *socket, QObject *parent = 0);
    QString nickName();

signals:
    void messageReceived(QString message);
    void wantParticipants();

public slots:
    void sendMessage(QString message);
    void setNickname(QString nickname);
    void sendParticipants(const QList<int> &ids, const QStringList &names);

protected slots:
    void onReadyRead();

protected:
    QTcpSocket *m_socket;
    QString m_pendingNickname;
};

#endif // REMOTECLIENT_HPP
