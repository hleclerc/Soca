/*
 Copyright 2012 Structure Computation  www.structure-computation.com
 Copyright 2012 Hugo Leclerc

 This file is part of Soca.

 Soca is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Soca is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with Soca. If not, see <http://www.gnu.org/licenses/>.
*/


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
