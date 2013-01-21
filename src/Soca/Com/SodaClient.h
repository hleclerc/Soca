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


#ifndef SODACLIENT_H
#define SODACLIENT_H

#ifdef METIL_COMP_DIRECTIVE
#pragma inc_path /usr/include/qt4
#endif // METIL_COMP_DIRECTIVE

#include "../MP.h"

#include <QtNetwork/QHostAddress>
#include <QtCore/QVector>

/**

*/
class SodaClient : public QObject {
    Q_OBJECT
public:
    struct Event {
        enum { RegType, Load, Disconnection, Change };

        bool disconnection() const { return event_type == Disconnection; }
        bool reg_type() const { return event_type == RegType; }
        bool change() const { return event_type == Change; }
        bool load() const { return event_type == Load; }

        MP mp() { return MP( client_loop, model ); }
        operator bool() const { return event_type != Disconnection; }

        //
        class ClientLoop *client_loop;
        int event_type;
        int n_callback;
        union {
            Model *model;
            quint64 ptr; ///< if RegType
        };
    };

    SodaClient( const QHostAddress &address, quint16 port );
    ~SodaClient();

    void  reg_type( QString type, bool auto_reg_model = true ); ///< permit to get an event if an object of type $type is created on the server
    void  reg_model( const MP &mp ); ///< if changed, model will generate an Change event
    MP    load_ptr( quint64 ptr ); ///< asynchronous load
    MP    load( QString path ); ///< asynchronous load
    Event event(); ///< wait for an event

    bool   connected() const;
    bool   has_something_to_send() const;

    void _wait();
private slots:
    void reg_type_callback_auto_reg( quint64 ptr ); ///< called if an object of a registered type is created on the server
    void reg_type_callback( quint64 ptr ); ///< called if an object of a registered type is created on the server
    void change_callback( Model *m ); ///<
    void load_for_reg_callback( Model *m, int n ); ///<
    void load_callback( Model *m, int n ); ///<
    void disconnected(); ///<

private:
    void _exit(); ///< exit from qevent_loop
    MP   _wait_load( int n ); ///< asynchronous load

    class ClientLoop *client_loop;
    class QEventLoop *qevent_loop;
    class Database *database;
    static int _nb_inst;

    QVector<Event> pending_events;
};

#endif // SODACLIENT_H
