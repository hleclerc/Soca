#ifndef MP_H
#define MP_H

#include "Model/Model.h"
class ClientLoop;

/**
   Model Pointer. Permits operations on models
*/
class MP {
public:
    struct NewObj { QString type; };

    MP( ClientLoop *c, Model *m );

    MP operator[]( const char *path ) const { return operator[]( QString( path ) ); }
    MP operator[]( QString path ) const; ///< returns a sub-model
    MP operator[]( int index ) const; ///< returns a sub-model

    MP operator=( qint64 val );

    operator int    () const;
    operator quint64() const;
    operator double () const;

    Model *model() const { return m; }
    QString type() const { return m ? m->type() : QString(); }
    int size() const { return m ? m->size() : 0; }
    bool ok() const { return m and not p.size(); }

    bool has_been_modified() const;
    bool has_been_directly_modified() const;

    static MP new_obj( QString type );

    static MP new_lst();
    static MP new_lst( QString type ); ///< Lst with alternate type

private:
    friend QDebug operator<<( QDebug dbg, const MP &c );

    ClientLoop *c;
    QString p;
    Model *m;
};


#endif // MP_H
