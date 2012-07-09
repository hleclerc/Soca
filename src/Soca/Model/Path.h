#ifndef PATH_H
#define PATH_H

#include "ModelWithAttr.h"

/**
*/
class Path : public ModelWithAttr {
public:
    Path();

    virtual void write_str( QDebug dbg ) const;
    virtual operator QString() const;
    virtual QString type() const;

    virtual bool _set( const char *str, int len );

    QString _data;
};

#endif // PATH_H
