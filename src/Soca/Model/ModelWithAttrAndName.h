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


#ifndef MODELWITHATTRANDNAME_H
#define MODELWITHATTRANDNAME_H

#include "ModelWithAttr.h"

/**
*/
class ModelWithAttrAndName : public ModelWithAttr {
public:
    ModelWithAttrAndName( QString _type );
    virtual QString type() const;

    QString _type;
};

#endif // MODELWITHATTRANDNAME_H
