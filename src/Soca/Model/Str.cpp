#include "../Sys/BinOut.h"
#include "Str.h"

Str::Str( QString data ) : _data( data ) {
}

Str::Str() {
}

void Str::write_usr ( BinOut &nut, BinOut &uut, Database *db ) {
    uut << 'W' << _server_id << _data;
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
