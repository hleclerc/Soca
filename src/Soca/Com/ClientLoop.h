#ifndef CLIENTLOOP_H
#define CLIENTLOOP_H

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QEventLoop>
#include <QtCore/QString>
#include <QtCore/QMap>

#include <iostream>

#include "../Database/Database.h"
#include "../Model/Model.h"
#include "../Sys/BinOut.h"

/**
*/
class ClientLoop : public QObject {
    Q_OBJECT
public:
    struct Functor {
        virtual void operator()( quint64 ) {}
    };

    ClientLoop( Database *db, const QHostAddress &address, quint16 port );

    int load( QString addr, QObject *receiver, const char *member ); ///< ask for model (or sub-model) at addr and call slot with the corresponding local copy (Model *)
    int load_ptr( quint64 ptr, QObject *receiver, const char *member ); ///<

    Model *load_async( QString addr ); ///< load a model, waiting for the answer if not already present in memory
    Model *load_ptr_async( quint64 ptr ); ///<

    ///
    void reg_type_for_callback( QString type, QObject *receiver, const char *member );

private slots:
    void readyRead();
    void aboutToClose();
    void readChannelFinished();

    void send_data();

signals:
    void _load( Model *, int n_callback ); ///< dummy signal
    void _type( quint64 ); ///< dummy signal

private:
    struct Callback {
        QObject *receiver;
        const char *member;
    };

    // parse
    void rep_update_PI32( qint64 m, qint32 info ); ///<
    void rep_update_PI64( qint64 m, qint64 info ); ///<
    void rep_update_PI8 ( qint64 m, quint8 info ); ///<
    void rep_update_6432( qint64 m, qint64 man, qint32 exp ); ///<
    void rep_update_cstr( qint64 m, const char *type_str, int type_len ); ///<
    void rep_push_string( const char *str, int len ); ///<
    void rep_push_model( qint64 m ); ///<
    void rep_reg_type( qint64 m, int n_callback ); ///< when a new registered type has been created
    void rep_creation( qint64 m, const char *type_str, int type_len );
    void rep_load( qint64 m, int n_callback );
    void rep_end();

    #define SIPE_CHARP char *
    #define SIPE_CLASS
    #include "ClientLoop_parser.h"

    // helpers
    int n_callback_model() const; ///< find a new callback id
    int n_callback_quint64() const; ///< find a new callback id
    void out_sig(); ///< signal that there is something to send

    //
    Database *db;

    BinOut out; ///< tmp buffer (to be sent to tcpSocket)
    QTcpSocket *tcpSocket;
    QMap<int,Callback> model_callbacks;
    QMap<int,Callback> quint64_callbacks;

    QVector<Model *> model_stack;
    QVector<QString> string_stack;

    bool out_signaled;
};

#endif // CLIENTLOOP_H
