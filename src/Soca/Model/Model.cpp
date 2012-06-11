#include "../Database/Database.h"
#include "../Sys/BinOut.h"
#include "Model.h"

Model::Model() {
    _server_id = 0;
}

void Model::bind( QObject *receiver, const char *member ) {
    Callback cb;
    cb.receiver = receiver;
    cb.member = member;
    _onchange_list << cb;
}

void Model::add_attr( QString key, Model *m ) {
}

void Model::push( Model *m ) {
}

int Model::attr_index( QString key ) const {
    return -1;
}

Model *Model::attr( QString key ) const {
    return 0;
}

Model *Model::attr( int index ) const {
    return 0;
}

int Model::size() const {
    return 0;
}

quint64 Model::get_server_id( Database *db ) const {
    if ( not _server_id )
        _server_id = db->new_tmp_server_id();
    return _server_id;
}

void Model::write_nsr( BinOut &nut, BinOut &uut, Database *db ) const {
    if ( not _server_id ) {
        write_usr( nut, uut, db );
        nut << 'N' << quint64( this ) << type();
    }
}


bool Model::_set( int info, QVector<Model *> &model_stack, QVector<QString> &string_stack ) {
    return false;
}

bool Model::_set( const char *str, int len ) {
    return false;
}

bool Model::_set( qint64, qint32 ) {
    return false;
}

bool Model::_set( Model *m ) {
    return false;
}

bool Model::_set( qint64 a ) {
    return false;
}

void Model::add_parent( Model *p ) {
    parents << p;
}

void Model::rem_parent( Model *p ) {
    int i = parents.indexOf( p );
    if ( i >= 0 )
        parents.remove( i );
}

QDebug operator<<( QDebug dbg, const Model *c ) {
    if ( c )
        c->write_str( dbg );
    else
        dbg << "(NULL)";
    return dbg.space();
}

