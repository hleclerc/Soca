#include "LstWithType.h"

LstWithType::LstWithType( QString type ) : _type( type ) {
}

QString LstWithType::type() const {
    return _type;
}
