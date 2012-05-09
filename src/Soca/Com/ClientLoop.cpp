#include "ClientLoop.h"

ClientLoop::ClientLoop( const QHostAddress &address, quint16 port ) {
    tcpSocket = new QTcpSocket( this );
    connect( tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()) );

    tcpSocket->connectToHost( address, port );
    tcpSocket->write( "pouetox" );
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
