#ifndef PATH_H
#define PATH_H

#include "ModelWithAttr.h"

/**
*/
class Path : public ModelWithAttr {
public:
    Path();

    virtual void write_str( QDebug dbg ) const;
    // data is stored internally by the server
};

#endif // PATH_H
