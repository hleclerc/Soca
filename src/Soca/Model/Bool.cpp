#include "Bool.h"

Bool::Bool( bool val ) : _data( val ) {
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
