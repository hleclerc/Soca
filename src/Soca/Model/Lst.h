#ifndef LST_H
#define LST_H

#include "Model.h"

/**

*/
class Lst : public Model {
public:
    Lst();

    virtual bool _set( int size, QVector<Model *> &model_stack, QVector<QString> &string_stack );

    QVector<Model *> _data;
};

#endif // LST_H
