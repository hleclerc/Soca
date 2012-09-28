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
