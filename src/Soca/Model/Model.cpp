#include "Model.h"

Model::Model() {
    _server_id = 0;
}

void Model::add_attr( QString key, Model *m ) {
}

int Model::attr_index( QString key ) const {
    return -1;
}

Model *Model::attr( QString key ) const {
    return 0;
}

bool Model::_set( int info, QVector<Model *> &model_stack, QVector<QString> &string_stack ) {
    return false;
}

bool Model::_set( const char *str, int len ) {
    return false;
}

bool Model::_set( qint64, qint32 ) {
    return false;
}

bool Model::_set( qint64 a ) {
    return false;
}

QDebug operator<<( QDebug dbg, const Model *c ) {
    if ( c )
        c->write_str( dbg );
    else
        dbg << "(NULL)";
    return dbg.space();
}
