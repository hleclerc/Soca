#include "ModelWithAttr.h"
#include <QVector>
#include <QDebug>

ModelWithAttr::ModelWithAttr() {
}

Model *ModelWithAttr::attr( QString key ) const {
    for( int i = 0; i < _data.size(); ++i )
        if ( _data[ i ].key == key )
            return _data[ i ].val;
    return 0;
}

int ModelWithAttr::attr_index( QString key ) const {
    for( int i = 0; i < _data.size(); ++i )
        if ( _data[ i ].key == key )
            return i;
    return -1;
}

void ModelWithAttr::write_str( QDebug dbg ) const {
    dbg.nospace() << "{";
    for( int i = 0; i < _data.size(); ++i )
        _data[ i ].val->write_str( dbg.nospace() << ( i ? ", " : "" ) << _data[ i ].key << ":" );
    dbg.nospace() << "}";
}

bool ModelWithAttr::_set( int size, QVector<Model *> &model_stack, QVector<QString> &string_stack ) {
    int os = string_stack.size() - size;
    int om = model_stack.size() - size;
    bool res = size != _data.size();

    // add or modify
    QVector<bool> used( _data.size(), 0 );
    for( int i = 0; i < size; ++i ) {
        QString key = string_stack[ os + i ];
        int j = attr_index( key );
        if ( j >= 0 ) {
            res |= _data[ j ].val != model_stack[ os + i ];
            _data[ j ].val = model_stack[ os + i ];
            used[ j ] = 1;
        } else {
            res = true;
            Attr attr;
            attr.key = key;
            attr.val = model_stack[ os + i ];
            _data << attr;
        }
    }

    // remove unused
    for( int i = 0; i < used.size(); ++i ) {
        if ( not used[ i ] ) {
            _data.remove( i );
            used.remove( i );
            res = true;
            --i;
        }
    }

    model_stack.resize( om );
    string_stack.resize( os );
    // qDebug() << "-> " << _data;
    return res;
}

