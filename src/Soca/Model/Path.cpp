#include "Path.h"

Path::Path() {
}

QString Path::type() const {
    return "Path";
}

void Path::write_str( QDebug dbg ) const {
    dbg << "/...";
}
