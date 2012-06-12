#include "Path.h"

Path::Path() {
}

void Path::write_usr ( BinOut &nut, BinOut &uut, Database *db ) {
}

QString Path::type() const {
    return "Path";
}

void Path::write_str( QDebug dbg ) const {
    dbg << "/...";
}
