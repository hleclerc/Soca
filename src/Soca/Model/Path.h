#ifndef PATH_H
#define PATH_H

#include "ModelWithAttr.h"

/**
*/
class Path : public ModelWithAttr {
public:
    Path();

    virtual void write_usr ( BinOut &nut, BinOut &uut, Database *db ) const;
    virtual void write_str( QDebug dbg ) const;
    virtual QString type() const;

    // data is stored internally by the server
};

#endif // PATH_H
