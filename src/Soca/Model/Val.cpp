#include "../Sys/BinOut.h"
#include "Val.h"
#include <cmath>

Val::Val( qint64 man, qint32 exp ) : man( man ), exp( exp ) {
}

Val::Val( double val ) {
    //double frexp( val, exp2 );
    if ( val ) {
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
    return man * std::pow( 10.0, exp );
}
