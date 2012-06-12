#ifndef BOOL_H
#define BOOL_H

#include "Model.h"

/**
*/
class Bool : public Model {
public:
    Bool( bool val = true );

    virtual void    write_usr ( BinOut &nut, BinOut &uut, Database *db );
    virtual void    write_str ( QDebug dbg ) const;
    virtual QString type      () const;

    virtual bool    _set      ( qint64 a );

    virtual operator int      () const;
    virtual operator quint64  () const;
    virtual operator double   () const;

    bool _data;
};

#endif // BOOL_H
