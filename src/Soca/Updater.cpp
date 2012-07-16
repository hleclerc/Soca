#include "Updater.h"

bool has_something_to_compute_else_than( Model *m, Model *a ) {
    if ( m == 0 or m->_op_id == Model::_cur_op_id )
        return false;
    m->_op_id = Model::_cur_op_id;

    quint64 req = 0, rep = 0;
    for( int i = 0; i < m->size(); ++i ) {
        if ( Model *t = m->attr( i ) ) {
            if ( m->key( i ) == "_computation_req_date" )
                req = t->operator quint64();
            else if ( m->key( i ) == "_computation_rep_date" )
                rep = t->operator quint64();
            else if ( has_something_to_compute_else_than( t, a ) )
                return true;
        }

    }

    return req > rep and m != a;
}

void Updater::exec( const MP &mp ) {
    // nothing to compute ?
    quint64 req = mp[ "_computation_req_date" ];
    quint64 rep = mp[ "_computation_rep_date" ];
    if ( req <= rep )
        return;

    quint64 cm = mp[ "_computation_mode" ];
    quint64 cs = mp[ "_computation_state" ];
    if ( cm == false && cs == false )
        return;

    // waiting for another computation ?
    ++Model::_cur_op_id;
    if ( has_something_to_compute_else_than( mp.model(), mp.model() ) ) {
        qDebug() << "something to compute !";
        return;
    }

    //
    clear_error_list( mp );
    qDebug() << "run" << type();

    //sdl::set( "toto", "1" );
    // QHttp
    //system( "wget ..." );

    run( mp );

    //sdl::set( "done", "1" );

    mp[ "_computation_rep_date" ] = req;
    if ( cm == false and cs == true )
        mp[ "_computation_state" ] = false;
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
