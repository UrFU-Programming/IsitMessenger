#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class ServerDiscovery;
class Server;
class LocalClient;

class QListWidgetItem;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

     void connectToServer();

public slots:
    void addContact(QString name);
    void addMessage(QString name, QString text);
    void addServer(QString address, quint16 port);
    void addServerToDiscovery(quint16 port);


private slots:
    void createServer();

    void participantsOnReceived(const QList<int> &ids, const QStringList &names);

    void onTunneledMessageReceived(int idFrom, const QByteArray &message);

    void onServerMessageReceived(QString from, QString message);

    void on_serverListConnectButton_clicked();

    void on_serverListList_itemDoubleClicked(QListWidgetItem *item);

    void on_serverListList_itemClicked(QListWidgetItem *item);

    void on_serverListRefreshButton_clicked();

    void sendMessage();

    void onClientConnected();

    void on_contacts_customContextMenuRequested(const QPoint &pos);

    void sendFile();

private:
    Ui::MainWindow *ui;
    ServerDiscovery *m_serverDiscovery;
    Server *m_server;
    LocalClient *m_client;
};

#endif // MAINWINDOW_HPP
