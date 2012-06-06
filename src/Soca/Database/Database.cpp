#include "../Com/ClientLoop.h"
#include "../Sys/BinOut.h"
#include "Database.h"

#include <QtCore/QTimer>

#pragma lib_name QtCore

Database::Database() {
    reg_changes = true;
    end_round_timer = false;
    prev_tmp_server_id = 0;
}

void Database::end_round() {
    end_round_timer = false;

    BinOut nut, uut;
    foreach( Model *m, changed_models ) {
        // have something to send to the server ?
        if ( not m->_changed_from_ext )
            m->write_usr( nut, uut, this );

        // registered callback(s) ?
        foreach( Model::Callback lc, m->_onchange_list ) {
            connect( this, SIGNAL(_model_sig(Model*)), lc.receiver, lc.member );
            emit _model_sig( m );
            disconnect( this, SIGNAL(_model_sig(Model*)), lc.receiver, lc.member );
        }
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
    m->_changed_from_ext = from_ext;
    if ( m->_server_id and reg_changes ) {
        changed_models.insert( m );
        if ( not end_round_timer ) {
            end_round_timer = true;
            QTimer::singleShot( 0, this, SLOT(end_round()) );
        }
    }
}

quint64 Database::new_tmp_server_id() {
    while ( not ( ++prev_tmp_server_id % 4 ) );
    return prev_tmp_server_id;
}
