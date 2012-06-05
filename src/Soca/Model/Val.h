#ifndef VAL_H
#define VAL_H

#include "Model.h"

/**
*/
class Val : public Model {
public:
    Val( qint64 man = 0, qint32 exp = 0 );

    virtual QString type     () const;
    virtual bool    _set     ( qint64 a, qint32 b );
    virtual bool    _set     ( qint64 a );
    virtual void    write_str( QDebug dbg ) const;
    virtual void    write_usr( BinOut &nut, BinOut &uut, Database *db ) const;

    qint64 man;
    qint32 exp;
};

#endif // VAL_H
