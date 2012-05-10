#ifndef CLIENTLOOP_H
#define CLIENTLOOP_H

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>
#include <QString>
#include <QMap>

#include "../Database/Database.h"
#include "../Model/Model.h"
#include "../Sys/BinOut.h"

/**
*/
class ClientLoop : public QObject {
    Q_OBJECT
public:
    ClientLoop( const QHostAddress &address, quint16 port );

    /// ask for model (or sub-model) at addr and call slot with the corresponding local copy (Model *)
    void load( QString addr, QObject *receiver, const char *member );

private slots:
    void readyRead();
    void send_data();

signals:
    void _load( Model *m ); ///< dummy signal

private:
    struct LoadCallback {
        QObject *receiver;
        const char *member;
    };

    // parse
    void rep_load( int n_callback, qint64 m );

    #define SIPE_CHARP char *
    #define SIPE_CLASS
    #include "ClientLoop_parser.h"

    // helpers
    int n_callback() const; ///< find a new callback id
    void out_sig(); ///< signal that there something to send

    //
    Database db;

    BinOut out; ///< tmp buffer (to be sent to tcpSocket)
    QTcpSocket *tcpSocket;
    QMap<int,LoadCallback> load_callbacks;

    bool out_signaled;
};

#endif // CLIENTLOOP_H
