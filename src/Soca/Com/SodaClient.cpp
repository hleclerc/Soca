/*
 Copyright 2012 Structure Computation  www.structure-computation.com
 Copyright 2012 Hugo Leclerc

 This file is part of Soca.

 Soca is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Soca is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with Soca. If not, see <http://www.gnu.org/licenses/>.
*/


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

    qevent_loop = 0;
    database = new Database;
    client_loop = new ClientLoop( database, address, port );

    connect( client_loop, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::QueuedConnection );
}

SodaClient::~SodaClient() {
    database->flush();
    delete client_loop;
    delete database;
    if ( --_nb_inst == 0 ) {
        delete qcore_application;
        qcore_application = 0;
    }
}

void SodaClient::reg_type( QString type, bool auto_reg_model ) {
    if ( auto_reg_model )
        client_loop->reg_type_for_callback( type, this, SLOT(reg_type_callback_auto_reg(quint64)) );
    else
        client_loop->reg_type_for_callback( type, this, SLOT(reg_type_callback(quint64)) );
}

void SodaClient::reg_model( const MP &mp ) {
    if ( Model *m = mp.model() )
        client_loop->reg_model( m, this, SLOT(change_callback(Model*)) );
}

MP SodaClient::load_ptr( quint64 ptr ) {
    return _wait_load( client_loop->load_ptr( ptr, this, SLOT(load_callback(Model*,int)) ) );
}

MP SodaClient::load( QString path ) {
    return _wait_load( client_loop->load( path, this, SLOT(load_callback(Model*,int)) ) );
}

bool SodaClient::has_something_to_send() const {
    return client_loop->has_something_to_send();
}

SodaClient::Event SodaClient::event() {
    while ( true ) {
        if ( pending_events.size() ) {
            Event res = pending_events.front();
            pending_events.pop_front();
            return res;
        }
        _wait();
    }
}

bool SodaClient::connected() const {
    return client_loop->connected();
}

void SodaClient::_wait() {
    QEventLoop qe;
    qevent_loop = &qe;
    qevent_loop->exec();
}

void SodaClient::_exit() {
    if ( qevent_loop ) {
        qevent_loop->exit();
        qevent_loop = 0;
    }
}


MP SodaClient::_wait_load( int n ) {
    while ( true ) {
        _wait();
        for( int i = pending_events.size() - 1; i >= 0; --i ) {
            if ( pending_events[ i ].event_type == Event::Load and pending_events[ i ].n_callback == n ) {
                Model *res = pending_events[ i ].model;
                pending_events.remove( i );
                return MP( client_loop, res );
            }
        }
    }
}

void SodaClient::reg_type_callback_auto_reg( quint64 ptr ) {
    client_loop->load_ptr( ptr, this, SLOT(load_for_reg_callback(Model*,int)) );
}

void SodaClient::reg_type_callback( quint64 ptr ) {
    Event event;
    event.client_loop = client_loop;
    event.event_type = Event::RegType;
    event.n_callback = 0;
    event.ptr = ptr;
    pending_events << event;

    _exit();
}

void SodaClient::change_callback( Model *m ) {
    Event event;
    event.client_loop = client_loop;
    event.event_type = Event::Change;
    event.model = m;
    pending_events << event;

    _exit();
}

void SodaClient::load_callback( Model *m, int n ) {
    Event event;
    event.client_loop = client_loop;
    event.event_type = Event::Load;
    event.n_callback = n;
    event.model = m;
    pending_events << event;

    _exit();
}

void SodaClient::load_for_reg_callback( Model *m, int n ) {
    if ( m )
        client_loop->reg_model( m, this, SLOT(change_callback(Model*)) );
}

void SodaClient::disconnected() {
    Event event;
    event.client_loop = client_loop;
    event.event_type = Event::Disconnection;
    pending_events << event;

    _exit();
}

