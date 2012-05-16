#ifndef MODEL_H
#define MODEL_H

#include <QtGlobal>
#include <QVector>
#include <QString>

/**
*/
class Model {
public:
    Model();

    virtual bool _set( int info, QVector<Model *> &model_stack, QVector<QString> &string_stack ) = 0;

    qint64 _server_id;
};

#endif // MODEL_H
