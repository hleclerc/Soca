#include "Updater.h"

bool has_something_to_compute_else_than( Model *m, Model *a ) {
    if ( m->_op_id == Model::_cur_op_id )
        return false;
    m->_op_id = Model::_cur_op_id;

    if ( m == a )
        return false;

    for( int i = 0; i < m->size(); ++i ) {
        if ( m->key( i ) == "_can_be_computed" and m->attr( i ) and m->attr( i )->operator int() % 2 )
            return true;
        if ( has_something_to_compute_else_than( m->attr( i ), a ) )
            return true;
    }
    return false;
}

void Updater::exec( const MP &mp ) {
    // nothing to compute ?
    ++Model::_cur_op_id;
    int cbc = mp[ "_can_be_computed" ];
    if ( cbc % 2 and has_something_to_compute_else_than( mp.model(), mp[ "_can_be_computed" ].model() ) )
        return;

    //
    if ( cbc == 1 ) {
        mp[ "_can_be_computed" ] = 0;
        run( mp );
    } else if ( cbc == 3 ) {
        mp[ "_can_be_computed" ] = 2;
        run( mp );
    }
}
