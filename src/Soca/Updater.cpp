#include "Updater.h"

bool has_something_to_compute_else_than( Model *m, Model *a ) {
    if ( m == 0 or m->_op_id == Model::_cur_op_id )
        return false;
    m->_op_id = Model::_cur_op_id;

    for( int i = 0; i < m->size(); ++i ) {
        Model *t = m->attr( i );
        if ( m->key( i ) == "_can_be_computed" and t and t != a and t->operator int() % 2 )
            return true;
        if ( has_something_to_compute_else_than( t, a ) )
            return true;
    }
    return false;
}

void Updater::exec( const MP &mp ) {
    // nothing to compute ?
    int cbc = mp[ "_can_be_computed" ];
    if ( cbc % 2 == 0 )
        return;

    // waiting for another computation ?
    ++Model::_cur_op_id;
    if ( has_something_to_compute_else_than( mp.model(), mp[ "_can_be_computed" ].model() ) ) {
        qDebug() << "yop";
        return;
    }

    //
    if ( cbc == 1 ) {
        mp[ "_can_be_computed" ] = 0;
        run( mp );
    } else if ( cbc == 3 ) {
        mp[ "_can_be_computed" ] = 2;
        run( mp );
    }
}
