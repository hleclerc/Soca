#include <QDebug>
#include "Lst.h"

Lst::Lst() {
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
    qDebug() << "-> " << _data;
    return res;
}
