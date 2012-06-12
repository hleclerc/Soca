#include "LstWithType.h"

LstWithType::LstWithType( QString type ) : _type( type ) {
}

QString LstWithType::underlying_type() const {
    return _type;
}
