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
#include "Path.h"

Path::Path( QString _data ) : _data( _data ) {
}

void Path::write_str( QDebug dbg ) const {
    // ModelWithAttr::write_str( dbg );
    dbg.nospace() << _data;
}

Path::operator QString() const {
    return _data;
}

QString Path::type() const {
    return "Path";
}

bool Path::_set( const char *str, int len ) {
    QString tmp = QString::fromUtf8( str, len );
    bool res = _data != tmp;
    _data = tmp;
    return res;
}

void Path::write_usr( BinOut &nut, BinOut &uut, Database *db ) {
    uut << 'W' << get_server_id( db ) << _data;
}
