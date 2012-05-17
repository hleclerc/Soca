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
    void rep_update_PI32( qint64 m, qint32 info ); ///<
    void rep_update_PI64( qint64 m, qint64 info ); ///<
    void rep_update_cstr( qint64 m, const char *type_str, int type_len ); ///<
    void rep_push_string( const char *str, int len ); ///<
    void rep_push_model( qint64 m ); ///<
    void rep_creation( qint64 m, const char *type_str, int type_len );
    void rep_load( qint64 m, int n_callback );
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
    QMap<qint64,Model *> model_map;
    QMap<int,LoadCallback> load_callbacks;

    QVector<Model *> model_stack;
    QVector<QString> string_stack;

    bool out_signaled;
};

#endif // CLIENTLOOP_H
