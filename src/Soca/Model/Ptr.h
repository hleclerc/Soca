#ifndef PTR_H
#define PTR_H

#include "Model.h"

/**
*/
class Ptr : public Model {
public:
    Ptr();

    virtual void    write_usr ( BinOut &nut, BinOut &uut, Database *db );
    virtual void    write_str( QDebug dbg ) const;
    virtual operator quint64() const;
    virtual QString type() const;
    virtual bool    _set( qint64 a );

    qint64 _data;
};

#endif // PTR_H
