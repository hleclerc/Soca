#include <Soca/Com/ClientLoop.h>
#include <QCoreApplication>

int main( int argc, char **argv ) {
    QCoreApplication app( argc, argv );
    ClientLoop loop( QHostAddress::Any, 8890 );
    return app.exec();
}
