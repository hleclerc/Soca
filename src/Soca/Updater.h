#ifndef UPDATER_H
#define UPDATER_H

#include "MP.h"

/**
  class to deal with _can_be_computed / TreeItem_Computable objects
*/
class Updater {
public:
    typedef enum { ET_Success, ET_Info, ET_Error } ErrorType;

    void exec( const MP &mp );
    bool add_message( const MP &mp, ErrorType type, QString title );

protected:
    void clear_error_list( const MP &mp );
    virtual bool run( MP mp ) = 0;
    virtual QString type() const = 0;
};

#endif // UPDATER_H
