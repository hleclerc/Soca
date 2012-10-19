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
#include "Val.h"

#include <limits>
#include <cmath>

Val::Val( qint64 man, qint32 exp ) : man( man ), exp( exp ) {
}

Val::Val( double val ) {
    //double frexp( val, exp2 );
    if ( isnan( val ) ) {
        man = 0;
        exp = std::numeric_limits<qint32>::max();
    } else if ( val ) {
        exp = qint32( log10( fabs( val ) ) - 17 );
        man = round( val / pow( 10.0, exp ) );

        if ( abs( man * pow( 10.0, exp ) - val ) > 1e-6 ) {
            // qDebug() << man << exp << "should give" << val;
            exp = 0;
            man = 0;
        }
    } else {
        exp = 0;
        man = 0;
    }
}


void Val::write_str( QDebug dbg ) const {
    if ( exp )
        dbg.nospace() << man << "e" << exp;
    else
        dbg.nospace() << man;
}

QString Val::type() const {
    return "Val";
}

bool Val::_set( qint64 a, qint32 b ) {
    if ( a != man or b != exp ) {
        man = a;
        exp = b;
        return true;
    }
    return false;
}

bool Val::_set( qint64 a ) {
    if ( a != man or exp ) {
        man = a;
        exp = 0;
        return true;
    }
    return false;
}

void Val::write_usr( BinOut &nut, BinOut &uut, Database *db ) {
    uut << 'X' << get_server_id( db ) << man << exp;
}

Val::operator int() const {
    return exp ? int( operator double() ) : man;
}

Val::operator quint64() const {
    return exp ? int( operator double() ) : man;
}

Val::operator double() const {
    if ( exp == std::numeric_limits<qint32>::max() )
        return NAN;
    return man * std::pow( 10.0, exp );
}
