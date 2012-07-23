#ifndef MP_H
#define MP_H

#include "Com/ClientLoop.h"
#include "Model/Lst.h"

/**
   Model Pointer. Permits operations on models
*/
class MP {
public:
    struct NewObj { QString type; };

    MP( ClientLoop *c, Model *m, QString p );
    MP( ClientLoop *c, Model *m );
    MP( Model *m = 0 );

    void flush(); ///< send modified data to ClientLoop

    void reassign( MP mp ) { if ( mp.c ) c = mp.c; m = mp.m; }

    MP operator[]( const char *path ) const { return operator[]( QString( path ) ); }
    MP operator[]( QString path ) const; ///< returns a sub-model
    MP operator[]( int index ) const; ///< returns a sub-model

    MP &operator=( const MP &val ) {
        if ( val.m ) {
            if ( p.size() and m ) {
                m->add_attr( p, val.m );
                if ( c )
                    c->signal_change( m );
                m = val.m;
                p.clear();
            } else if ( m and m->_set( val.m ) and c )
                c->signal_change( m );
        }
        return *this;
    }

    template<class T>
    MP &operator=( const T &val ) {
        if ( p.size() and m ) {
            Model *o = m;
            m = conv( val );
            o->add_attr( p, m );
            if ( c )
                c->signal_change( o );
            p.clear();
        } else if ( m and m->_set( val ) and c )
            c->signal_change( m );
        return *this;
    }

    template<class T>
    MP &operator<<( const T &val ) {
        if ( p.size() and m ) {
            Model *o = m;
            m = new Lst;
            o->add_attr( p, m );
            if ( c )
                c->signal_change( m );
            p.clear();
        }
        if ( m ) {
            m->push( conv( val ) );
            if ( c )
                c->signal_change( m );
        }
        return *this;
    }

    operator int    () const;
    operator quint64() const;
    operator double () const;
    operator QString() const;

    Model *model() const { return m; }
    QString type() const { return m ? m->type() : QString(); }
    int size() const { return m ? m->size() : 0; }
    void clear() { if ( m ) { if ( m->clear() and c ) c->signal_change( m ); } }
    bool ok() const { return m and not p.size(); }

    quint64 date_last_change() const;
    bool changed_from_ext() const;

    bool has_been_modified() const;
    bool has_been_directly_modified() const;

    static MP new_obj( QString type = "Model" );

    static MP new_lst();
    static MP new_lst( QString type ); ///< Lst with alternate type

    static MP new_typed_array_qint32();

private:
    friend QDebug operator<<( QDebug dbg, const MP &c );
    static Model *conv( const MP &mp );
    static Model *conv( quint64 val );
    static Model *conv( quint32 val );
    static Model *conv( qint64 val );
    static Model *conv( qint32 val );
    static Model *conv( double val );
    static Model *conv( QString st );

    ClientLoop *c;
    QString p;
    Model *m;
};


#endif // MP_H
