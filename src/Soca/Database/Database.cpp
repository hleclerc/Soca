#include "../Com/ClientLoop.h"
#include "../Sys/BinOut.h"
#include "Database.h"

#include <QtCore/QTimer>

#pragma lib_name QtCore

Database::Database() {
    cur_date = 0;
    reg_changes = true;
    end_round_timer = false;
    prev_tmp_server_id = 0;
}

void Database::_call_onchange_rec( Model *m ) {
    if ( m->_date_last_change < cur_date ) {
        _call_onchange_loc( m, 0 );
        foreach( Model *p, m->parents )
            _call_onchange_rec( p );
    }
}

void Database::_call_onchange_loc( Model *m, int add ) {
    m->_date_last_change = cur_date + add;

    foreach( Model::Callback lc, m->_onchange_list ) {
        connect( this, SIGNAL(_model_sig(Model*)), lc.receiver, lc.member );
        emit _model_sig( m );
        disconnect( this, SIGNAL(_model_sig(Model*)), lc.receiver, lc.member );
    }
}

void Database::end_round() {
    end_round_timer = false;
    cur_date += 2;

    BinOut nut, uut;
    foreach( Model *m, changed_models ) {
        // have something to send to the server ?
        if ( not m->_changed_from_ext )
            m->write_usr( nut, uut, this );

        // registered callback(s) ?
        _call_onchange_loc( m, 1 );
        foreach( Model *p, m->parents )
            _call_onchange_rec( p );
    }

    // send data
    if ( nut.size() or uut.size() ) {
        nut << uut;
        foreach( ClientLoop *c, clients )
            *c << nut;
    }

    changed_models.clear();
}

Model *Database::model( qint64 m ) const {
    QMap<qint64,Model *>::const_iterator iter = model_map.find( m );
    if ( iter != model_map.end() )
        return iter.value();
    return 0;
}

Model *Database::signal_change( Model *m, bool from_ext ) {
    m->_date_last_change = cur_date + 3;
    m->_changed_from_ext = from_ext;
    changed_models.insert( m );

    if ( not end_round_timer ) {
        end_round_timer = true;
        QTimer::singleShot( 0, this, SLOT(end_round()) );
    }
}

quint64 Database::new_tmp_server_id( Model *m ) {
    while ( not ( ++prev_tmp_server_id % 4 ) );
    model_map[ prev_tmp_server_id ] = m;
    return prev_tmp_server_id;
}

void Database::flush() {
    BinOut nut, uut;
    foreach( Model *m, changed_models ) {
        if ( not m->_changed_from_ext )
            m->write_usr( nut, uut, this );
        m->_changed_from_ext = true;
    }

    // send data
    if ( nut.size() or uut.size() ) {
        nut << uut;
        foreach( ClientLoop *c, clients ) {
            *c << nut;
            c->flush_out();
        }
    }
}

void Database::tmp_id_to_real( qint64 old_ptr, qint64 new_ptr ) {
    if ( old_ptr % 4 ) {
        QMap<qint64,Model *>::iterator iter = model_map.find( old_ptr );
        if ( iter != model_map.end() ) {
            model_map.erase( iter );
            model_map[ new_ptr ] = iter.value();
        }
    }
}
