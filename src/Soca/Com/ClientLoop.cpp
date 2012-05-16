#include "../Model/Directory.h"
#include "ClientLoop.h"
#include <QTimer>

ClientLoop::ClientLoop( const QHostAddress &address, quint16 port ) {
    tcpSocket = new QTcpSocket( this );
    connect( tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()) );

    tcpSocket->connectToHost( address, port );
    out_signaled = false;
}

void ClientLoop::load( QString addr, QObject *receiver, const char *member ) {
    int n = n_callback();

    LoadCallback &lc = load_callbacks[ n ];
    lc.receiver = receiver;
    lc.member = member;

    out << 'L' << n << addr;
    out_sig();
}

void ClientLoop::rep_creation( qint64 m, const char *type_str, int type_len ) {
    std::string s( type_str, type_str + type_len );
    qDebug() << "CREA " << QLatin1String( s.c_str() ) << " " << m;

    Model *r = 0;
    if ( s == "Lst" ) r = new Lst;
    else if ( s == "Directory" ) r = new Directory;

    model_map[ m ] = r;
}

void ClientLoop::rep_update_ptr( qint64 m, qint64 info ) {
    if ( Model *p = model_map[ m ] )
        p->_set( info, model_stack, string_stack );
    qDebug() << "UPDATE " << m << " " << info;
}

void ClientLoop::rep_update_int( qint64 m, int info ) {
    if ( Model *p = model_map[ m ] )
        p->_set( info, model_stack, string_stack );
    qDebug() << "UPDATE " << m << " " << info;
}

void ClientLoop::rep_load( qint64 m, int n_callback ) {
    if ( load_callbacks.contains( n_callback ) ) {
        LoadCallback &lc = load_callbacks[ n_callback ];

        connect( this, SIGNAL(_load(Model *)), lc.receiver, lc.member );
        emit _load( db.model( m ) );
        disconnect( this, SIGNAL(_load(Model *)), lc.receiver, lc.member );

        load_callbacks.remove( n_callback );
    }
}

void ClientLoop::rep_push( qint64 m ) {
    qDebug() << "PUSH " << model_map[ m ];
    model_stack << ( model_map.contains( m ) ? model_map[ m ] : 0 );
}

void ClientLoop::rep_end() {
    qDebug() << "REP END ";
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

    qDebug() << "SENT " << out.data().size();

    tcpSocket->write( out.data() );
    out_signaled = false;
    out.clear();
}

int ClientLoop::n_callback() const {
    while ( true ) {
        int res = qrand();
        if ( not load_callbacks.contains( res ) )
            return res;
    }
}
