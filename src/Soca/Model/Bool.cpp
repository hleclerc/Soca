#include "../Sys/BinOut.h"
#include "Bool.h"

Bool::Bool( bool val ) : _data( val ) {
}

void Bool::write_usr ( BinOut &nut, BinOut &uut, Database *db ) const {
    uut << 'Y' << quint64( this ) << (unsigned char)_data;
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
