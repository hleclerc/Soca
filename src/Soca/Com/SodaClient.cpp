#include <QtCore/QCoreApplication>
#include "SodaClient.h"
#include "ClientLoop.h"

int SodaClient::_nb_inst = 0;
static QCoreApplication *qcore_application = 0;

SodaClient::SodaClient( const QHostAddress &address, quint16 port ) {
    if ( not _nb_inst++ ) {
        int argc = 0;
        char *argv[] = {};
        qcore_application = new QCoreApplication( argc, argv );
    }

    database = new Database;
    client_loop = new ClientLoop( database, address, port );
}

SodaClient::~SodaClient() {
    delete client_loop;
    delete database;
    if ( --_nb_inst == 0 ) {
        delete qcore_application;
        qcore_application = 0;
    }
}

void SodaClient::reg_type( QString type ) {
    client_loop->reg_type_for_callback( type, this, SLOT(reg_type_callback(quint64)) );
}

Model *SodaClient::load_ptr( quint64 ptr ) {
    int n = client_loop->load_ptr( ptr, this, SLOT(load_callback(Model*,int)) );
    while ( true ) {
        wait();
        for( int i = pending_events.size() - 1; i >= 0; --i ) {
            if ( pending_events[ i ].event_type == Event::Load and pending_events[ i ].n_callback == n ) {
                Model *res = pending_events[ i ].model;
                pending_events.remove( i );
                return res;
            }
        }
    }
}

Model *SodaClient::load( QString path ) {
    return 0;
}

SodaClient::Event SodaClient::event() {
    while ( true ) {
        if ( pending_events.size() ) {
            Event res = pending_events.front();
            pending_events.pop_front();
            return res;
        }
        wait();
    }
}

void SodaClient::wait() {
    QEventLoop qe;
    qevent_loop = &qe;
    qevent_loop->exec();
}

void SodaClient::reg_type_callback( quint64 ptr ) {
    Event event;
    event.event_type = Event::RegType;
    event.n_callback = 0;
    event.ptr = ptr;
    pending_events << event;

    qevent_loop->exit();
}

void SodaClient::load_callback( Model *m, int n ) {
    Event event;
    event.event_type = Event::Load;
    event.n_callback = n;
    event.model = m;
    pending_events << event;

    qevent_loop->exit();
}
