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

    virtual void write_str( QDebug dbg ) const;
    virtual bool _set( int size, QVector<Model *> &model_stack, QVector<QString> &string_stack );

    Model *attr( QString key ) const;
    int attr_index( QString key ) const;

    QVector<Attr> _data;
};

#endif // MODELWITHATTR_H
