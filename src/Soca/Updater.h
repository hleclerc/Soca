#ifndef UPDATER_H
#define UPDATER_H

#include "MP.h"

/**
  class to deal with _can_be_computed / TreeItem_Computable objects
*/
class Updater {
public:
    typedef enum { ET_Info, ET_Error } ErrorType;

    void exec( const MP &mp );

protected:
    void clear_error_list( const MP &mp );
    void add_error( const MP &mp, ErrorType type, QString title );

    virtual void run( const MP &mp ) = 0;
};

#endif // UPDATER_H
