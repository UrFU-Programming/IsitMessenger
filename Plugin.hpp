#ifndef IPLUGIN_HPP
#define IPLUGIN_HPP
#include <QBitArray>
#include <QString>
#include "MainWindow.hpp"
class QWidget;
class Plugin
{
public:
    Plugin(MainWindow *w);

    virtual QString signature() const = 0;
    virtual void addMessage(int from, QByteArray data) = 0;
    virtual void sendMessage() = 0 ;
    QWidget *widget() { return nullptr; }
protected:
    MainWindow *m_save;
};
#endif // IPLUGIN_HPP
