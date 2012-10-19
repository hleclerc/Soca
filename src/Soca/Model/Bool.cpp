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
#include "Bool.h"

Bool::Bool( bool val ) : _data( val ) {
}

void Bool::write_usr ( BinOut &nut, BinOut &uut, Database *db ) {
    uut << 'Y' << get_server_id( db ) << (unsigned char)_data;
}

void Bool::write_str( QDebug dbg ) const {
    dbg.nospace() << ( _data ? "true" : "false" );
}

QString Bool::type() const {
    return "Bool";
}

bool Bool::_set( qint64 a ) {
    bool res = _data != a;
    _data = a;
    return res;
}

Bool::operator int      () const { return _data; }
Bool::operator quint64  () const { return _data; }
Bool::operator double   () const { return _data; }
