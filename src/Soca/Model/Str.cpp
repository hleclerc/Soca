#include "../Sys/BinOut.h"
#include "Str.h"

Str::Str() {
}

void Str::write_usr ( BinOut &nut, BinOut &uut, Database *db ) const {
    uut << 'W' << quint64( this ) << _data;
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
