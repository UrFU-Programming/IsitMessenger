#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "Server.hpp"
#include "ServerDiscovery.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->createServer, SIGNAL(clicked(bool)),
            this, SLOT(createServer()));

    m_serverDiscovery = new ServerDiscovery(this);
    m_server = new Server(this);

    connect(m_server, SIGNAL(messageReceived(QString,QString)),
            this, SLOT(addMessage(QString,QString)));
    connect(m_serverDiscovery,SIGNAL(serverFound(QString,quint16)),
            this, SLOT(addServer(QString,quint16)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addContact(QString name)
{
    for(int i=0;i<ui->contacts->count();i++){
        QListWidgetItem *item = ui->contacts->item(i);
        if(item->text() == name){
            return;
        }
    }
    ui->contacts->addItem(name);
}

void MainWindow::addMessage(QString name, QString text)
{
    ui->messages->append(name+":"+text+"\n");
}
void MainWindow::addServer(QString address, quint16 port)
{
    QString text = address+":"+QString::number(port);
    for(int i=0;i<ui->serverListList->count();i++){
        QListWidgetItem *item = ui->serverListList->item(i);
        if(item->text() == text){
            return;
        }
    }
    ui->serverListList->addItem(text);
}
void MainWindow::createServer()
{

}

