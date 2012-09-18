#include "ModelWithAttr.h"
#include "../Sys/BinOut.h"
#include <QtCore/QVector>
#include <QtCore/QDebug>

ModelWithAttr::ModelWithAttr() {
}

void ModelWithAttr::write_usr( BinOut &nut, BinOut &uut, Database *db ) {
    for( int i = 0; i < _data.size(); ++i )
        _data[ i ].val->write_nsr( nut, uut, db );
    for( int i = 0; i < _data.size(); ++i ) {
        uut << 'P' << _data[ i ].val->_server_id;
        uut << 'p' << _data[ i ].key;
    }
    uut << 'U' << get_server_id( db ) << quint32( _data.size() );
}

void ModelWithAttr::add_attr( QString key, Model *m ) {
    m->add_parent( this );

    for( int i = 0; i < _data.size(); ++i ) {
        if ( _data[ i ].key == key ) {
            _data[ i ].val = m;
            return;
        }
    }

    Attr attr;
    attr.key = key;
    attr.val = m;
    _data << attr;
}

Model *ModelWithAttr::attr( QString key ) const {
    for( int i = 0; i < _data.size(); ++i )
        if ( _data[ i ].key == key )
            return _data[ i ].val;
    return 0;
}

Model *ModelWithAttr::attr( int index ) const {
    return index < _data.size() ? _data[ index ].val : 0;
}

QString ModelWithAttr::key( int index ) const {
    return index < _data.size() ? _data[ index ].key : 0;
}

int ModelWithAttr::size() const {
    return _data.size();
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
            _data[ j ].val->rem_parent( this );
            _data[ j ].val = model_stack[ os + i ];
            _data[ j ].val->add_parent( this );
            used[ j ] = true;
        } else {
            res = true;
            Attr attr;
            attr.key = key;
            attr.val = model_stack[ os + i ];
            // qDebug() << key << attr.val;
            if ( attr.val ) {
                attr.val->add_parent( this );
                _data << attr;
                used << true;
            }
        }
    }

    // remove unused
    for( int i = 0; i < used.size(); ++i ) {
        if ( not used[ i ] ) {
            _data[ i ].val->rem_parent( this );
            _data.remove( i );
            used.remove( i );
            res = true;
            --i;
        }
    }

    model_stack.resize( om );
    string_stack.resize( os );
    return res;
}

