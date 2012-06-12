#ifndef LSTWITHTYPE_H
#define LSTWITHTYPE_H

#include "Lst.h"

/**

*/
class LstWithType : public Lst {
public:
    LstWithType( QString type );
    virtual QString underlying_type() const;

    QString _type;
};

#endif // LSTWITHTYPE_H
