#include "ClientLoop.h"
#include <QDataStream>
#include <QTimer>

ClientLoop::ClientLoop( const QHostAddress &address, quint16 port ) {
    tcpSocket = new QTcpSocket( this );
    connect( tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()) );

    tcpSocket->connectToHost( address, port );
}

void ClientLoop::load( QString addr, QObject *receiver, const char *slot ) {
    int n = n_callback();

    LoadCallback &lc = load_callbacks[ n ];
    lc.receiver = receiver;
    lc.slot = slot;

    //    QDataStream qd( tcpSocket );
    //    qd << 'L';
    //    qd << n;
    //    qd << addr.toAscii();
    QTimer::singleShot( 0, receiver, slot );
}


void ClientLoop::readyRead() {
    //     QDataStream in( tcpSocket );
    //     in.setVersion(QDataStream::Qt_4_0);

    //     if (blockSize == 0) {
    //         if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
    //             return;

    //         in >> blockSize;
    //     }

    //     if (tcpSocket->bytesAvailable() < blockSize)
    //         return;

    //     QString nextFortune;
    //     in >> nextFortune;

    //     if (nextFortune == currentFortune) {
    //         QTimer::singleShot(0, this, SLOT(requestNewFortune()));
    //         return;
    //     }

    //     currentFortune = nextFortune;
    //     statusLabel->setText(currentFortune);
    //     getFortuneButton->setEnabled(true);
}

int ClientLoop::n_callback() const {
    while ( true ) {
        int res = qrand();
        if ( not load_callbacks.contains( res ) )
            return res;
    }
}
