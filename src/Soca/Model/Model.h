#ifndef MODEL_H
#define MODEL_H

#ifdef METIL_COMP_DIRECTIVE
#pragma inc_path /usr/include/qt4
#endif // METIL_COMP_DIRECTIVE

#include <QtCore/QtGlobal>
#include <QtCore/QVector>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QDebug>
class Database;
class BinOut;

/**
*/
class Model {
public:
    struct Callback {
        QObject *receiver;
        const char *member;
    };

    Model();

    void bind( QObject *receiver, const char *member );

    virtual void     write_str ( QDebug dbg ) const = 0;
    virtual void     add_attr  ( QString key, Model *m );
    virtual int      attr_index( QString key ) const;
    virtual Model   *attr      ( QString key ) const;
    virtual QString  type      () const = 0;
    virtual void     write_usr ( BinOut &nut, BinOut &uut, Database *db ) const {}
    virtual operator double    () const { return 0; }
    quint64          get_server_id( Database *db ) const; ///<

    virtual bool _set( int info, QVector<Model *> &model_stack, QVector<QString> &string_stack );
    virtual bool _set( const char *str, int len );
    virtual bool _set( qint64 a, qint32 b );
    virtual bool _set( qint64 a );

    mutable qint64 _server_id;
    QVector<Callback> _onchange_list;
    bool _changed_from_ext; ///< true if last change come from the server
};

QDebug operator<<( QDebug dbg, const Model *c );

#endif // MODEL_H
