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
    void rep_creation( qint64 m, const char *type_str, int type_len );
    void rep_load( qint64 m, int n_callback );
    void rep_p_z(); ///< push 0 on the stack
    void rep_end();

    #define SIPE_CHARP char *
    #define SIPE_CLASS
    #include "ClientLoop_parser.h"

    // helpers
    int n_callback() const; ///< find a new callback id
    void out_sig(); ///< signal that there is something to send

    //
    Database db;

    BinOut out; ///< tmp buffer (to be sent to tcpSocket)
    QTcpSocket *tcpSocket;
    QVector<Model *> stack;
    QMap<int,LoadCallback> load_callbacks;

    bool out_signaled;
};

#endif // CLIENTLOOP_H
