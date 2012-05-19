#include <QtCore/QDebug>
#include "Lst.h"

Lst::Lst() {
}

void Lst::write_str( QDebug dbg ) const {
    dbg.nospace() << "[";
    for( int i = 0; i < _data.size(); ++i )
        _data[ i ]->write_str( dbg.nospace() << ( i ? ", " : "" ) );
    dbg.nospace() << "]";
}

bool Lst::_set( int size, QVector<Model *> &model_stack, QVector<QString> & ) {
    bool res = false;

    // already existing elements
    int o = model_stack.size() - size;
    for( int i = 0; i < _data.size(); ++i ) {
        if ( _data[ i ] != model_stack[ o + i ] ) {
            _data[ i ] = model_stack[ o + i ];
            res = true;
        }
    }

    // new ones
    for( int i = _data.size(); i < size; ++i )
        _data << model_stack[ o + i ];

    // trim
    if ( _data.size() != size ) {
        _data.resize( size );
        res = true;
    }

    model_stack.resize( model_stack.size() - size );
    return res;
}
