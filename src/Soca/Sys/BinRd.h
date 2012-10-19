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


#ifndef BINRD_H
#define BINRD_H

/**
Simple binary reader
*/
class BinRd {
public:
    BinRd( const char *data, int size );

    template<class T>
    BinRd &operator>>( T &val ) {
        if ( _size >= sizeof( T ) ) {
            val = *reinterpret_cast<const T *>( _data );
            _data += sizeof( T );
            _size -= sizeof( T );
        }
        return *this;
    }

protected:
    const char *_data;
    int _size;
};

#endif // BINRD_H
