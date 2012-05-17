#ifndef MODEL_H
#define MODEL_H

#include <QtGlobal>
#include <QVector>
#include <QString>
#include <QDebug>

/**
*/
class Model {
public:
    Model();

    virtual void write_str( QDebug dbg ) const = 0;

    virtual bool _set( int info, QVector<Model *> &model_stack, QVector<QString> &string_stack );
    virtual bool _set( const char *str, int len );
    virtual bool _set( qint64 a, qint32 b );
    virtual bool _set( qint64 a );

    qint64 _server_id;
};

QDebug operator<<( QDebug dbg, const Model *c );

#endif // MODEL_H
