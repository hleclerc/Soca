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
#include "Str.h"

Str::Str( QString data ) : _data( data ) {
}

Str::Str() {
}

void Str::write_usr ( BinOut &nut, BinOut &uut, Database *db ) {
    uut << 'W' << get_server_id( db ) << _data;
}

void Str::write_str( QDebug dbg ) const {
    dbg.nospace() << _data;
}

Str::operator QString  () const {
    return _data;
}

QString Str::type() const {
    return "Str";
}

bool Str::_set( const char *str, int len ) {
    QString tmp = QString::fromUtf8( str, len );
    bool res = _data != tmp;
    _data = tmp;
    return res;
}
