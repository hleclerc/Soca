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


#ifndef BINOUT_H
#define BINOUT_H

#ifdef METIL_COMP_DIRECTIVE
#pragma inc_path /usr/include/qt4
#endif // METIL_COMP_DIRECTIVE
#include <QtCore/QByteArray>
#include <QtCore/QString>

/**
*/
class BinOut {
public:
    BinOut &operator<<( const BinOut &out ) {
        _data.append( out._data );
        return *this;
    }

    BinOut &operator<<( const QString &str ) {
        QByteArray tmp = str.toAscii();
        *this << int( tmp.size() );
        _data.append( tmp );
        return *this;
    }

    template<class T>
    BinOut &operator<<( const T &v ) {
        _data.append( reinterpret_cast<const char *>( &v ), sizeof( T ) );
        return *this;
    }

    BinOut &write( const char *ptr, int len ) {
        _data.append( ptr, len );
        return *this;
    }

    void clear() { _data.clear(); }
    int size() const { return _data.size(); }

    const QByteArray &data() const { return _data; }

private:
    QByteArray _data;
};

#endif // BINOUT_H
