#ifndef SODACLIENT_H
#define SODACLIENT_H

#ifdef METIL_COMP_DIRECTIVE
#pragma inc_path /usr/include/qt4
#endif // METIL_COMP_DIRECTIVE

#include "../Model/Model.h"

#include <QtNetwork/QHostAddress>
#include <QtCore/QVector>

/**

*/
class SodaClient : public QObject {
    Q_OBJECT
public:
    struct Event {
        enum { RegType, Load };

        bool reg_type() const { return event_type == RegType; }
        bool load() const { return event_type == Load; }

        //
        int event_type;
        int n_callback;
        union {
            Model *model;
            quint64 ptr; ///< if RegType
        };
    };

    SodaClient( const QHostAddress &address, quint16 port );
    ~SodaClient();

    void reg_type( QString type ); ///< permit to get an event if an object of type $type is created on the server
    Model *load_ptr( quint64 ptr ); ///< asynchronous load
    Model *load( QString path ); ///< asynchronous load
    Event event(); ///< wait for an event

private slots:
    void reg_type_callback( quint64 ptr ); ///< called if an object of a registered type is created on the server
    void load_callback( Model *m, int n ); ///<

private:
    void wait();

    class ClientLoop *client_loop;
    class QEventLoop *qevent_loop;
    class Database *database;
    static int _nb_inst;

    QVector<Event> pending_events;
};

#endif // SODACLIENT_H
