#include "../Sys/BinOut.h"
#include <QtCore/QDebug>
#include "Lst.h"

Lst::Lst() {
}

void Lst::write_usr( BinOut &nut, BinOut &uut, Database *db ) {
    for( int i = 0; i < _data.size(); ++i )
        _data[ i ]->write_nsr( nut, uut, db );
    for( int i = 0; i < _data.size(); ++i )
        uut << 'P' << _data[ i ]->_server_id;
    uut << 'U' << _server_id << quint32( _data.size() );
}

void Lst::write_str( QDebug dbg ) const {
    dbg.nospace() << "[";
    for( int i = 0; i < _data.size(); ++i )
        _data[ i ]->write_str( dbg.nospace() << ( i ? ", " : "" ) );
    dbg.nospace() << "]";
}

void Lst::push( Model *m ) {
    if ( m )
        _data << m;
}

int Lst::attr_index( QString key ) const {
    bool ok;
    int res = key.toInt( &ok );
    return ok ? res : -1;
}

Model *Lst::attr( QString key ) const {
    int index = attr_index( key );
    return index >= 0 and index < _data.size() ? _data[ index ] : 0;
}

Model *Lst::attr( int index ) const {
    return index >= 0 and index < _data.size() ? _data[ index ] : 0;
}

int Lst::size() const {
    return _data.size();
}

QString Lst::type() const {
    return "Lst";
}

void Lst::clear() {
    _data.clear();
}

bool Lst::_set( int size, QVector<Model *> &model_stack, QVector<QString> & ) {
    int o = model_stack.size() - size;
    QVector<Model *> nata; nata.resize( size );
    for( int i = 0; i < size; ++i ) {
        if ( not model_stack[ o + i ] ) {
            model_stack.resize( o );
            return false;
        }
        nata[ i ] = model_stack[ o + i ];
    }

    model_stack.resize( o );
    if ( _data == nata )
        return false;

    for( int i = 0; i < _data.size(); ++i )
        _data[ i ]->rem_parent( this );

    _data = nata;
    for( int i = 0; i < _data.size(); ++i )
        _data[ i ]->add_parent( this );

    return true;
}
