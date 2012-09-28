#ifndef PATH_H
#define PATH_H

#include "ModelWithAttr.h"

/**
*/
class Path : public ModelWithAttr {
public:
    Path( QString _data = QString() );

    virtual void write_str( QDebug dbg ) const;
    virtual operator QString() const;
    virtual QString type() const;

    virtual bool _set( const char *str, int len );
    virtual void write_usr( BinOut &nut, BinOut &uut, Database *db );

    QString _data;
};

#endif // PATH_H
