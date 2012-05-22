#include "Str.h"

Str::Str() {
}

void Str::write_str( QDebug dbg ) const {
    dbg.nospace() << _data;
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
