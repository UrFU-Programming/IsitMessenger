#ifndef SERVERDISCOVERY_HPP
#define SERVERDISCOVERY_HPP

#include <QObject>

class ServerDiscovery : public QObject
{
    Q_OBJECT
public:
    explicit ServerDiscovery(QObject *parent = 0);

signals:

public slots:
    void addServer(quint port);
};

#endif // SERVERDISCOVERY_HPP
