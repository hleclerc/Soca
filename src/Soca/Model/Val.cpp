#include "../Sys/BinOut.h"
#include "Val.h"

Val::Val( qint64 man, qint32 exp ) : man( man ), exp( exp ) {
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

void Val::write_usr( BinOut &nut, BinOut &uut, Database *db ) const {
    uut << 'X' << get_server_id( db ) << man << exp;
}
