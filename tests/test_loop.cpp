#include <QCoreApplication>
#include "MyApp.h"


int main( int argc, char **argv ) {
    QCoreApplication app( argc, argv );
    MyApp my_app;

    Database db;
    ClientLoop loop( &db, QHostAddress::Any, 8890 );
    loop.load( "/", &my_app, SLOT(onload(Model *)) );

    return app.exec();
}
