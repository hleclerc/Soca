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


#ifndef TYPEDARRAY_H
#define TYPEDARRAY_H

#include "../Sys/BinOut.h"
#include "../Sys/BinRd.h"
#include "../Sys/S.h"
#include "Model.h"

/**
*/
template<class T>
class TypedArray : public Model {
public:
    typedef int I;

    TypedArray( const QVector<I> &size = QVector<I>() ) : _size( size ), _data( nb_items() ) {
    }

    const T &operator[]( int index ) const { return _data[ index ]; }
    T &operator[]( int index ) { return _data[ index ]; }

    virtual int size() const { return nb_items(); }
    virtual int size( int index ) const { return _size[ index ]; }

    virtual void write_usr( BinOut &nut, BinOut &uut, Database *db ) {
        int ts = sizeof( int ) * ( 1 + _size.size() ) + sizeof( T ) * nb_items();
        uut << 'W' << get_server_id( db ) << ts;

        uut << (int)_size.size();
        for( int i = 0; i < _size.size(); ++i )
            uut << _size[ i ];

        for( int i = 0; i < nb_items(); ++i )
            uut << _data[ i ];
    }

    virtual void write_str( QDebug dbg ) const {
        dbg.nospace() << '[' << _size << ']' << _data;
    }

    virtual QString type() const {
        return _type( S<T>() );
    }

    virtual bool _set( const char *str, int len ) {
        BinRd rd( str, len );
        int n;
        rd >> n;
        _size.resize( n );
        for( int i = 0; i < n; ++i )
            rd >> _size[ i ];

        _data.resize( nb_items() );
        for( int i = 0; i < nb_items(); ++i )
            rd >> _data[ i ];
    }

    int nb_items() const {
        return nb_items( _size );
    }

    static int nb_items( const QVector<I> &size ) {
        if ( not size.size() )
            return 0;
        int res = size[ 0 ];
        for( int i = 1; i < size.size(); ++i )
            res *= size[ i ];
        return res;
    }

    static QString _type( S<double> ) { return "TypedArray_Float64"; }
    static QString _type( S<qint32> ) { return "TypedArray_Int32"; }

    QVector<I> _size;
    QVector<T> _data;
};

#endif // TYPEDARRAY_H
