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


#include "../Model/ModelWithAttrAndName.h"
#include "../Model/TypedArray.h"
#include "../Model/Directory.h"
#include "../Model/Bool.h"
#include "../Model/Path.h"
#include "../Model/Str.h"
#include "../Model/Ptr.h"
#include "../Model/Val.h"
#include "ClientLoop.h"
#include <QtCore/QTimer>

#ifdef METIL_COMP_DIRECTIVE
#pragma lib_name QtNetwork
#endif //METIL_COMP_DIRECTIVE

ClientLoop::ClientLoop( Database *db, const QHostAddress &address, quint16 port ) : db( db ) {
    tcpSocket = new QTcpSocket( this );
    connect( tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::QueuedConnection );
    connect( tcpSocket, SIGNAL(aboutToClose()), this, SLOT(aboutToClose()), Qt::QueuedConnection );
    connect( tcpSocket, SIGNAL(readChannelFinished()), this, SLOT(readChannelFinished()), Qt::QueuedConnection );

    tcpSocket->connectToHost( address, port );
    tcpSocket->waitForConnected( 1000 );
    out_signaled = false;

    db->clients.insert( this );
}

ClientLoop::~ClientLoop() {
    db->clients.remove( this );
}

int ClientLoop::load( QString addr, QObject *receiver, const char *member ) {
    int n = n_callback_model();

    Callback &lc = model_callbacks[ n ];
    lc.receiver = receiver;
    lc.member = member;

    out << 'L' << n << addr;
    out_sig();

    return n;
}

int ClientLoop::load_ptr( quint64 ptr, QObject *receiver, const char *member ) {
    int n = n_callback_model();

    Callback &lc = model_callbacks[ n ];
    lc.receiver = receiver;
    lc.member = member;

    out << 'l' << n << ptr;
    out_sig();

    return n;
}

bool ClientLoop::connected() const {
    return tcpSocket->state() == tcpSocket->ConnectedState;
}

void ClientLoop::operator<<( const BinOut &data ) {
    out << data;
    out_sig();
}

void ClientLoop::reg_type_for_callback( QString type, QObject *receiver, const char *member ) {
    int n = n_callback_quint64();

    Callback &lc = quint64_callbacks[ n ];
    lc.receiver = receiver;
    lc.member = member;

    out << 'R' << n << type;
    out_sig();
}

void ClientLoop::reg_model( Model *m, QObject *receiver, const char *member ) {
    m->bind( receiver, member );
    db->signal_change( m, true );
    //    connect( this, SIGNAL(_model(Model*)), receiver, member );
    //    emit _model( m );
    //    disconnect( this, SIGNAL(_model(Model*)), receiver, member );
}

void ClientLoop::flush_out() {
    send_data();
}

void ClientLoop::rep_update_PI64( qint64 m, qint64 info ) {
    if ( Model *p = db->model( m ) )
        if ( p->_set( info ) )
            db->signal_change( p, true );
}

void ClientLoop::rep_update_6432( qint64 m, qint64 man, qint32 exp ) {
    if ( Model *p = db->model( m ) )
        if ( p->_set( man, exp ) )
            db->signal_change( p, true );
}

void ClientLoop::rep_tmp_id_to_real( qint64 old_ptr, qint64 new_ptr ) {
    db->tmp_id_to_real( old_ptr, new_ptr );
}

void ClientLoop::rep_update_PI32( qint64 m, qint32 info ) {
    if ( Model *p = db->model( m ) )
        if ( p->_set( info, model_stack, string_stack ) )
            db->signal_change( p, true );
}

void ClientLoop::rep_update_PI8( qint64 m, quint8 info ) {
    if ( Model *p = db->model( m ) )
        if ( p->_set( info ) )
            db->signal_change( p, true );
}

void ClientLoop::rep_update_cstr( qint64 m, const char *type_str, int type_len ) {
    if ( Model *p = db->model( m ) )
        if ( p->_set( type_str, type_len ) )
            db->signal_change( p, true );
}

void ClientLoop::rep_push_model( qint64 m ) {
    model_stack << db->model( m );
}

void ClientLoop::rep_push_string( const char *str, int len ) {
    string_stack << QString::fromUtf8( str, len );
}

void ClientLoop::rep_reg_type( qint64 m, int n_callback ) {
    if ( quint64_callbacks.contains( n_callback ) ) {
        Callback &lc = quint64_callbacks[ n_callback ];

        connect( this, SIGNAL(_type(quint64)), lc.receiver, lc.member );
        emit _type( m );
        disconnect( this, SIGNAL(_type(quint64)), lc.receiver, lc.member );
    }
}

void ClientLoop::rep_creation( qint64 m, const char *type_str, int type_len ) {
    QString s = QString::fromUtf8( type_str, type_len );

    Model *r = 0;
    if ( s == "Lst" ) r = new Lst;
    else if ( s == "TypedArray_Float64" ) r = new TypedArray<double>;
    else if ( s == "TypedArray_Int32" ) r = new TypedArray<qint32>;
    else if ( s == "Directory" ) r = new Directory;
    else if ( s == "Bool" ) r = new Bool;
    else if ( s == "Path" ) r = new Path;
    else if ( s == "Ptr" ) r = new Ptr;
    else if ( s == "Str" ) r = new Str;
    else if ( s == "Val" ) r = new Val;
    else r = new ModelWithAttrAndName( s );

    r->_server_id = m;
    db->model_map[ m ] = r;
    db->signal_change( r, true );
}

void ClientLoop::rep_load( qint64 m, int n_callback ) {
    if ( model_callbacks.contains( n_callback ) ) {
        Callback &lc = model_callbacks[ n_callback ];

        connect( this, SIGNAL(_load(Model *,int)), lc.receiver, lc.member );
        emit _load( db->model( m ), n_callback );
        disconnect( this, SIGNAL(_load(Model *,int)), lc.receiver, lc.member );

        model_callbacks.remove( n_callback );
    }
}

void ClientLoop::rep_end() {
}

void ClientLoop::out_sig() {
    if ( not out_signaled ) {
        out_signaled = true;
        QTimer::singleShot( 0, this, SLOT(send_data()) );
    }
}

void ClientLoop::readyRead() {
    while ( true ) {
        char buffer[ 2048 ];
        qint64 ruff = tcpSocket->read( buffer, 2048 );
        if ( not ruff )
            break;
        parse( buffer, buffer + ruff );
    }
}

void ClientLoop::aboutToClose() {
    qDebug() << "About To close";
}

void ClientLoop::readChannelFinished() {
    qDebug() << "readChannelFinished";
    emit disconnected();
}

void ClientLoop::send_data() {
    if ( out.size() ) {
        out << 'E';
        //qDebug() << "#####################on passe la dedans !###########################";
        tcpSocket->write( out.data() );
        out_signaled = false;
        out.clear();
    }
}

int ClientLoop::n_callback_model() const {
    while ( true ) {
        int res = qrand();
        if ( not model_callbacks.contains( res ) )
            return res;
    }
}

int ClientLoop::n_callback_quint64() const {
    while ( true ) {
        int res = qrand();
        if ( not quint64_callbacks.contains( res ) )
            return res;
    }
}
