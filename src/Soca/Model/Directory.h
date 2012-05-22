#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "Lst.h"

/**
*/
class Directory : public Lst {
public:
    Directory();

    virtual QString type() const;
};

#endif // DIRECTORY_H
