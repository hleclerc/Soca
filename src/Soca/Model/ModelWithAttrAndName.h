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
