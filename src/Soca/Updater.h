#ifndef UPDATER_H
#define UPDATER_H

#include "MP.h"

/**
  class to deal with _can_be_computed / TreeItem_Computable objects
*/
class Updater {
public:
    void exec( const MP &mp );

protected:
    virtual void run( const MP &mp ) = 0;
};

#endif // UPDATER_H
