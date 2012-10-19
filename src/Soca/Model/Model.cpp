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


#include "../Database/Database.h"
#include "../Sys/BinOut.h"
#include "Model.h"

quint64 Model::_cur_op_id = 0;

Model::Model() {
    _op_id = 0;
    _server_id = 0;
}

void Model::bind( QObject *receiver, const char *member ) {
    Callback cb;
    cb.receiver = receiver;
    cb.member = member;
    _onchange_list << cb;
}

void Model::add_attr( QString key, Model *m ) {
}

void Model::push( Model *m ) {
}

int Model::attr_index( QString key ) const {
    return -1;
}

Model *Model::attr( QString key ) const {
    return 0;
}

Model *Model::attr( int index ) const {
    return 0;
}

QString Model::key( int index ) const {
    return QString();
}

int Model::size() const {
    return 0;
}

quint64 Model::get_server_id( Database *db ) {
    if ( not _server_id )
        _server_id = db->new_tmp_server_id( this );
    return _server_id;
}

QString Model::underlying_type() const {
    return type();
}


void Model::write_nsr( BinOut &nut, BinOut &uut, Database *db ) {
    if ( not _server_id ) {
        if ( type() != underlying_type() )
            nut << 'n' << get_server_id( db ) << type() << underlying_type();
        else
            nut << 'N' << get_server_id( db ) << type();
        write_usr( nut, uut, db );
    }
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

bool Model::_set( QString a ) {
    return _set( a.toAscii().data(), a.size() );
}

bool Model::_set( Model *m ) {
    return false;
}

bool Model::_set( qint64 a ) {
    return false;
}

void Model::add_parent( Model *p ) {
    parents << p;
}

void Model::rem_parent( Model *p ) {
    int i = parents.indexOf( p );
    if ( i >= 0 )
        parents.remove( i );
}

QDebug operator<<( QDebug dbg, const Model *c ) {
    if ( c )
        c->write_str( dbg );
    else
        dbg << "(NULL)";
    return dbg.space();
}

