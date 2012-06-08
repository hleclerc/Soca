#include "Model/ModelWithAttrAndName.h"
#include "Model/LstWithType.h"
#include "Model/Val.h"

#include <QtCore/QStringList>
#include "Com/ClientLoop.h"
#include "MP.h"


MP::MP( ClientLoop *c, Model *m ) : c( c ), m( m ) {
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
            res = res->attr( n );
        }
    }
    return MP( c, res );
}

MP MP::operator[]( int index ) const {
    return MP( c, m and not p.size() ? m->attr( index ) : 0 );
}

MP MP::operator=( qint64 val ) {
    if ( p.size() and m ) {
        Model *o = m;
        m = new Val( val ); //c->factory
        o->add_attr( p, m );
        return *this;
    }
    if ( m and m->_set( val ) )
        c->signal_change( m );
    return *this;
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

QDebug operator<<( QDebug dbg, const MP &c ) {
    return dbg << c.m;
}
