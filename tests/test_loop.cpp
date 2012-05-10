#include <QCoreApplication>
#include "MyApp.h"


int main( int argc, char **argv ) {
    QCoreApplication app( argc, argv );
    MyApp my_app;

    ClientLoop loop( QHostAddress::Any, 8890 );
    loop.load( "/toto", &my_app, SLOT(onload(Model *)) );

    return app.exec();
}
