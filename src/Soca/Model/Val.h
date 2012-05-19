#ifndef VAL_H
#define VAL_H

#include "Model.h"

/**
*/
class Val : public Model {
public:
    Val( qint64 man = 0, qint64 exp = 0 );

    virtual void write_str( QDebug dbg ) const;
    virtual bool _set( qint64 a, qint32 b );

    qint64 man;
    qint64 exp;
};

#endif // VAL_H
