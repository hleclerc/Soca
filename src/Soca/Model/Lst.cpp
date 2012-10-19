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
    uut << 'U' << get_server_id( db ) << quint32( _data.size() );
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

bool Lst::clear() {
    if ( _data.size() ) {
        _data.clear();
        return true;
    }
    return false;
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
