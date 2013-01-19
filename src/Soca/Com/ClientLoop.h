/*
 Copyright 2012 Structure Computation  www.structure-computation.com
 Copyright 2012 Hugo Leclerc

 This file is part of Soca.

 Soca is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Soca is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with Soca. If not, see <http://www.gnu.org/licenses/>.
*/


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
    virtual ~ClientLoop();

    bool connected() const;

    int load( QString addr, QObject *receiver, const char *member ); ///< ask for model (or sub-model) at addr and call slot with the corresponding local copy (Model *)
    int load_ptr( quint64 ptr, QObject *receiver, const char *member ); ///<

    Model *load_async( QString addr ); ///< load a model, waiting for the answer if not already present in memory
    Model *load_ptr_async( quint64 ptr ); ///<

    void reg_type_for_callback( QString type, QObject *receiver, const char *member ); ///< permit to get an event if an object of type $type is created on the server
    void reg_model( Model *m, QObject *receiver, const char *member ); ///< call receiver->member if m is modified

    void flush_out(); ///< send data

    Model *signal_change( Model *m ) { return db->signal_change( m ); }

    void operator<<( const BinOut &data );


    bool has_something_to_send() const;

    Database *db;

private slots:
    void readyRead();
    void aboutToClose();
    void readChannelFinished();

    void send_data();

signals:
    void disconnected();
    void _load( Model *, int n_callback ); ///< dummy signal
    void _model( Model * ); ///< dummy signal
    void _type( quint64 ); ///< dummy signal

private:
    struct Callback {
        QObject *receiver;
        const char *member;
    };

    // parse
    void rep_tmp_id_to_real( qint64 old_ptr, qint64 new_ptr ); ///<
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
    BinOut out; ///< tmp buffer (to be sent to tcpSocket)
    QTcpSocket *tcpSocket;
    QMap<int,Callback> model_callbacks;
    QMap<int,Callback> quint64_callbacks;

    QVector<Model *> model_stack;
    QVector<QString> string_stack;

    bool out_signaled;
};

#endif // CLIENTLOOP_H
