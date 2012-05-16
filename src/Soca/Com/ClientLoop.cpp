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

void ClientLoop::rep_p_z() {
    qDebug() << "REP P_Z ";
    stack << 0;
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
