#ifndef MODELWITHATTR_H
#define MODELWITHATTR_H

#include "Model.h"
#include <QPair>

/**

*/
class ModelWithAttr : public Model {
public:
    struct Attr {
        QString key;
        Model  *val;
    };
    ModelWithAttr();

    virtual bool _set( int size, QVector<Model *> &model_stack, QVector<QString> &string_stack );

    bool has_attr( QString key ) const;

    QVector<Attr> _data;
};

#endif // MODELWITHATTR_H
