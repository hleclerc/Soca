#include "Ptr.h"

Ptr::Ptr() : _data( 0 ) {
}

void Ptr::write_str( QDebug dbg ) const {
    dbg.nospace() << _data;
}

QString Ptr::type() const {
    return "Ptr";
}

bool Ptr::_set( qint64 a ) {
    bool res = _data != a;
    _data = a;
    return res;
}
