#ifndef MP_H
#define MP_H

#include "Model/Model.h"
class ClientLoop;

/**
   Model Pointer. Permits operations on models
*/
class MP {
public:
    MP( ClientLoop *c, Model *m );

    MP operator[]( QString path ); ///< returns a sub-model

    MP operator=( qint64 val );

private:
    friend QDebug operator<<( QDebug dbg, const MP &c );

    ClientLoop *c;
    QString p;
    Model *m;
};


#endif // MP_H
