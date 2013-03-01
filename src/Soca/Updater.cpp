/*
 Copyright 2012 Structure Computation  www.structure-computation.com
 Copyright 2012 Hugo Leclerc

 This file is part of Soca.

 Soca is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Soca is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with Soca. If not, see <http://www.gnu.org/licenses/>.
*/


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
        //mp[ "_computation_mode" ] = true;
//         sleep(1);
//         quint64 mp_server_id = mp.get_server_id();
//         mp = sc.load_ptr(mp_server_id);
        return;
    }

    //
    clear_error_list( mp );

    qDebug() << "run" << type();

    //sdl::set( "toto", "1" );
    // QHttp
    //system( "wget ..." );

    run( mp );

    mp[ "_computation_rep_date" ] = req;
    //         add_message( mp, ET_Info, "done" );
    if ( cm == false and cs == true )
        mp[ "_computation_state" ] = false;
    
    mp[ "_ready_state" ]        = false;
    mp[ "_computation_state" ]  = false;
    mp[ "_pending_state" ]      = false;
    mp[ "_processing_state" ]   = false;
    mp[ "_finish_state" ]       = true;
    mp[ "_stop_state" ]         = false;
    mp[ "_computation_mode" ] = false; 
    //mp.flush();
    //sdl::set( "done", "1" );
}

void Updater::clear_error_list( const MP &mp ) {
    mp[ "_messages" ].clear();
}

bool Updater::add_message( const MP &mp, ErrorType type, QString title ) {
    MP msg = MP::new_obj( "Model" );
    msg[ "provenance" ] = this->type();
    msg[ "title" ] = title;
    switch ( type ) {
      case ET_Success: msg[ "type" ] = "msg_success"; break;
      case ET_Info: msg[ "type" ] = "msg_info"; break;
      case ET_Error: msg[ "type" ] = "msg_error"; break;
    }

    mp[ "_messages" ] << msg;
    return false;
}
