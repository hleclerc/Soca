#ifndef STR_H
#define STR_H

#include "Model.h"

/**
*/
class Str : public Model {
public:
    Str( QString _data );
    Str();

    virtual void     write_usr( BinOut &nut, BinOut &uut, Database *db );
    virtual void     write_str( QDebug dbg ) const;
    virtual operator QString  () const;
    virtual QString  type     () const;

    virtual bool    _set( const char *str, int len );

    QString _data;
};

#endif // STR_H
