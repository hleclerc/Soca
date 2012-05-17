#ifndef STR_H
#define STR_H

#include "Model.h"

/**
*/
class Str : public Model {
public:
    Str();

    virtual void write_str( QDebug dbg ) const;
    virtual bool _set( const char *str, int len );

    QString _data;
};

#endif // STR_H
