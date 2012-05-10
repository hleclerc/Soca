#ifndef CLIENTLOOP_H
#define CLIENTLOOP_H

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

/**
*/
class ClientLoop : public QObject {
    Q_OBJECT
public:
    ClientLoop( const QHostAddress &address, quint16 port );


private slots:
    void readyRead();

private:
    QTcpSocket *tcpSocket;
};

#endif // CLIENTLOOP_H
