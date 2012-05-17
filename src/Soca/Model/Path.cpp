#include "Path.h"

Path::Path() {
}

void Path::write_str( QDebug dbg ) const {
    dbg << "/...";
}
