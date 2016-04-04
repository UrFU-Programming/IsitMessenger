#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
class ServerDiscovery;
class Server;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addContact(QString name);
    void addMessage(QString name, QString text);

private slots:
    void createServer();

private:
    Ui::MainWindow *ui;
    ServerDiscovery *m_serverDiscovery;
    Server *m_server;
};

#endif // MAINWINDOW_HPP
