#include <QtCore/QStringList>
#include "Com/ClientLoop.h"
#include "Model/Val.h"
#include "MP.h"

MP::MP( ClientLoop *c, Model *m ) : c( c ), m( m ) {
}

MP MP::operator[]( QString path ) {
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
            qDebug() << n << n.replace( ']', ' ' );
            res = res->attr( n );
        }
    }
    return MP( c, res );
}

MP MP::operator=( qint64 val ) {
    if ( p.size() and m ) {
        Model *o = m;
        m = new Val( val ); //c->factory
        o->add_attr( p, m );
        return *this;
    }
    if ( m )

    return this;
}

QDebug operator<<( QDebug dbg, const MP &c ) {
    return dbg << c.m;
}
