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
        // qDebug() << "yop";
        return;
    }

    //
    if ( cbc == 1 ) {
        mp[ "_can_be_computed" ] = 0;
        clear_error_list( mp );
        run( mp );
    } else if ( cbc == 3 ) {
        mp[ "_can_be_computed" ] = 2;
        clear_error_list( mp );
        run( mp );
    }
}

void Updater::clear_error_list( const MP &mp ) {
    mp[ "_messages" ].clear();
}

void Updater::add_error( const MP &mp, ErrorType type, QString title ) {
    MP msg = MP::new_obj( "Model" );
    msg[ "provenance" ] = "server";
    msg[ "title" ] = title;
    switch ( type ) {
      case ET_Info: msg[ "type" ] = "msg_info"; break;
      case ET_Error: msg[ "type" ] = "msg_error"; break;
    }

    mp[ "_messages" ] << msg;
}
