#include <Soca/Com/ClientLoop.h>
#include <QCoreApplication>

class MyApp : public QObject {
    Q_OBJECT
public:

private slots:
    void onload( Model *m ) {
    }
};

int main( int argc, char **argv ) {
    QCoreApplication app( argc, argv );
    ClientLoop loop( QHostAddress::Any, 8890 );
    MyApp my_app;
    loop.load( "/toto", &my_app, SLOT( onload(Model *) ) );
    return app.exec();
}
