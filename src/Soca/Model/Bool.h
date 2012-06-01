#ifndef BOOL_H
#define BOOL_H

#include "Model.h"

/**
*/
class Bool : public Model {
public:
    Bool( bool val = true );

    virtual void write_str( QDebug dbg ) const;
    virtual QString type() const;

    virtual bool _set( qint64 a );

    bool _data;
};

#endif // BOOL_H
