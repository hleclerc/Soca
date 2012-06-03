#ifndef MODEL_H
#define MODEL_H

#ifdef METIL_COMP_DIRECTIVE
#pragma inc_path /usr/include/qt4
#endif // METIL_COMP_DIRECTIVE

#include <QtCore/QtGlobal>
#include <QtCore/QVector>
#include <QtCore/QString>
#include <QtCore/QDebug>

/**
*/
class Model {
public:
    Model();

    virtual void    write_str ( QDebug dbg ) const = 0;
    virtual void    add_attr  ( QString key, Model *m );
    virtual int     attr_index( QString key ) const;
    virtual Model  *attr      ( QString key ) const;
    virtual QString type      () const = 0;

    virtual bool _set( int info, QVector<Model *> &model_stack, QVector<QString> &string_stack );
    virtual bool _set( const char *str, int len );
    virtual bool _set( qint64 a, qint32 b );
    virtual bool _set( qint64 a );

    qint64 _server_id;
};

QDebug operator<<( QDebug dbg, const Model *c );

#endif // MODEL_H
