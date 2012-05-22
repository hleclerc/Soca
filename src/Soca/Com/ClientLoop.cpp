#include "../Model/ModelWithAttrAndName.h"
#include "../Model/Directory.h"
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
    connect( tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()) );

    tcpSocket->connectToHost( address, port );
    out_signaled = false;
}

void ClientLoop::load( QString addr, QObject *receiver, const char *member ) {
    int n = n_callback_model();

    Callback &lc = model_callbacks[ n ];
    lc.receiver = receiver;
    lc.member = member;

    out << 'L' << n << addr;
    out_sig();
}

Model *ClientLoop::load_async( QString addr ) {
    model_rep = 0;
    load( addr, this, SLOT(model_slot(Model*)) );

    //
    QEventLoop qe; qevent_loop = &qe;
    qevent_loop->exec();
    return model_rep;
}

void ClientLoop::reg_type_for_callback( QString type, QObject *receiver, const char *member ) {
    int n = n_callback_quint64();

    Callback &lc = _callbacks[ n ];
    lc.receiver = receiver;
    lc.member = member;

    out << 'R' << n << type;
    out_sig();
}

void ClientLoop::model_slot( Model *m ) {
    model_rep = m;
    qevent_loop->exit();
}

void ClientLoop::rep_update_PI64( qint64 m, qint64 info ) {
    if ( Model *p = db->model( m ) )
        p->_set( info );
}

void ClientLoop::rep_update_6432( qint64 m, qint64 man, qint32 exp ) {
    if ( Model *p = db->model( m ) )
        p->_set( man, exp );
}

void ClientLoop::rep_update_6432( qint64 m, quint8 pi8 ) {
    if ( Model *p = db->model( m ) )
        p->_set( pi8 );
}

void ClientLoop::rep_update_PI32( qint64 m, qint32 info ) {
    if ( Model *p = db->model( m ) )
        p->_set( info, model_stack, string_stack );
}

void ClientLoop::rep_update_cstr( qint64 m, const char *type_str, int type_len ) {
    if ( Model *p = db->model( m ) )
        p->_set( type_str, type_len );
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

        quint64_callbacks.remove( n_callback );
    }
}

void ClientLoop::rep_creation( qint64 m, const char *type_str, int type_len ) {
    QString s = QString::fromUtf8( type_str, type_len );
    // qDebug() << s;

    Model *r = 0;
    if ( s == "Lst" ) r = new Lst;
    else if ( s == "Directory" ) r = new Directory;
    else if ( s == "Path" ) r = new Path;
    else if ( s == "Ptr" ) r = new Ptr;
    else if ( s == "Str" ) r = new Str;
    else if ( s == "Val" ) r = new Val;
    else r = new ModelWithAttrAndName( s );

    r->_server_id = m;
    db->model_map[ m ] = r;
}

void ClientLoop::rep_load( qint64 m, int n_callback ) {
    if ( model_callbacks.contains( n_callback ) ) {
        Callback &lc = model_callbacks[ n_callback ];

        connect( this, SIGNAL(_load(Model *)), lc.receiver, lc.member );
        emit _load( db->model( m ) );
        disconnect( this, SIGNAL(_load(Model *)), lc.receiver, lc.member );

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
    QByteArray tmp = tcpSocket->readAll();
    parse( tmp.data(), tmp.data() + tmp.size() );
}

void ClientLoop::send_data() {
    out << 'E';

    tcpSocket->write( out.data() );
    out_signaled = false;
    out.clear();
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
