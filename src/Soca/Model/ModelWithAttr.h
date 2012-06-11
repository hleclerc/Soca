#ifndef MODELWITHATTR_H
#define MODELWITHATTR_H

#include "Model.h"
#include <QtCore/QPair>

/**

*/
class ModelWithAttr : public Model {
public:
    struct Attr {
        QString key;
        Model  *val;
    };
    ModelWithAttr();

    virtual void   write_usr ( BinOut &nut, BinOut &uut, Database *db ) const;
    virtual void   write_str ( QDebug  dbg ) const;
    virtual void   add_attr  ( QString key, Model *m );
    virtual int    attr_index( QString key ) const;
    virtual Model *attr      ( QString key ) const;

    virtual bool   _set      ( int size, QVector<Model *> &model_stack, QVector<QString> &string_stack );

    QVector<Attr> _data;
};

#endif // MODELWITHATTR_H
