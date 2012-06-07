#ifndef MP_H
#define MP_H

#include "Model/Model.h"
class ClientLoop;

/**
   Model Pointer. Permits operations on models
*/
class MP {
public:
    MP( ClientLoop *c, Model *m );

    MP operator[]( const char *path ) { return operator[]( QString( path ) ); }
    MP operator[]( QString path ); ///< returns a sub-model

    MP operator=( qint64 val );

    operator int    () const;
    operator quint64() const;
    operator double () const;

    Model *model() const { return m; }
    QString type() const { return m ? m->type() : QString(); }

    bool has_been_modified() const;
    bool has_been_directly_modified() const;

private:
    friend QDebug operator<<( QDebug dbg, const MP &c );

    ClientLoop *c;
    QString p;
    Model *m;
};


#endif // MP_H
