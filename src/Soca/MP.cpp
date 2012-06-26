#include "Model/ModelWithAttrAndName.h"
#include "Model/LstWithType.h"
#include "Model/TypedArray.h"
#include "Model/Val.h"
#include "Model/Str.h"

#include <QtCore/QStringList>
#include "Com/ClientLoop.h"
#include "MP.h"


MP::MP( ClientLoop *c, Model *m, QString p ) : c( c ), m( m ), p( p ) {
}

MP::MP( ClientLoop *c, Model *m ) : c( c ), m( m ) {
}

MP::MP( Model *m ) : c( 0 ), m( m ) {
}

MP::operator int() const {
    return m and not p.size() ? m->operator int() : 0;
}

MP::operator quint64() const {
    return m and not p.size() ? m->operator quint64() : 0;
}

MP::operator double() const {
    return m and not p.size() ? m->operator double() : 0;
}

MP::operator QString() const {
    return m and not p.size() ? m->operator QString() : 0;
}

MP MP::operator[]( QString path ) const {
    Model *res = m;
    QStringList l = path.split( '.' );
    for( int i = 0; res and i < l.size(); ++i ) {
        QStringList m = l[ i ].split( '[' );
        for( int j = 0; res and j < m.size(); ++j ) {
            QString n = m[ j ];
            if ( j ) {
                n.replace( ']', ' ' );
                n = n.trimmed();
            }
            Model *tmp = res->attr( n );
            if ( tmp == 0 and n.indexOf( '.' ) < 0 and n.indexOf( '/' ) < 0 )
                return MP( c, res, n );
            res = tmp;
        }
    }
    return MP( c, res );
}

MP MP::operator[]( int index ) const {
    return MP( c, m and not p.size() ? m->attr( index ) : 0 );
}

quint64 MP::date_last_change() const {
    return m ? m->_date_last_change : 0;
}

bool MP::changed_from_ext() const {
    return m ? m->_changed_from_ext : false;
}

bool MP::has_been_modified() const {
    return m and not p.size() ? m->has_been_modified( c->db->cur_date ) : false;
}

bool MP::has_been_directly_modified() const {
    return m and not p.size() ? m->has_been_directly_modified( c->db->cur_date ) : false;
}

MP MP::new_obj( QString type ) {
    return MP( 0, new ModelWithAttrAndName( type ) );
}

MP MP::new_lst( QString type ) {
    return MP( 0, new LstWithType( type ) );
}

MP MP::new_lst() {
    return MP( 0, new Lst );
}

MP MP::new_typed_array_qint32() {
    return MP( 0, new TypedArray<qint32> );
}

QDebug operator<<( QDebug dbg, const MP &c ) {
    return dbg << c.m;
}

Model *MP::conv( const MP &mp ) {
    return mp.p.size() ? 0 : mp.m;
}

Model *MP::conv( quint64 val ) {
    return new Val( val, 0 );
}

Model *MP::conv( quint32 val ) {
    return new Val( val, 0 );
}

Model *MP::conv( qint64 val ) {
    return new Val( val, 0 );
}

Model *MP::conv( qint32 val ) {
    return new Val( val, 0 );
}

Model *MP::conv( double val ) {
    return new Val( val );
}

Model *MP::conv( QString st ) {
    return new Str( st );
}
