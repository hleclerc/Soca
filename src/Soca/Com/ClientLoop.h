#ifndef CLIENTLOOP_H
#define CLIENTLOOP_H

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>
#include <QString>
#include <QMap>

#include "../Model/Model.h"

/**
*/
class ClientLoop : public QObject {
    Q_OBJECT
public:
    ClientLoop( const QHostAddress &address, quint16 port );

    /// ask for model (or sub-model) at addr and call slot with the corresponding local copy (Model *)
    void load( QString addr, QObject *receiver, const char *slot );

private slots:
    void readyRead();

private:
    struct LoadCallback {
        QObject *receiver;
        const char *slot;
    };

    /// find a new callback id
    int n_callback() const;

    QTcpSocket *tcpSocket;
    QMap<int,LoadCallback> load_callbacks;
};

#endif // CLIENTLOOP_H
