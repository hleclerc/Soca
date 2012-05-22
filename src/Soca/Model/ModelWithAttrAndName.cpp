#include "ModelWithAttrAndName.h"

ModelWithAttrAndName::ModelWithAttrAndName( QString type ) : _type( type ) {
}

QString ModelWithAttrAndName::type() const {
    return _type;
}
