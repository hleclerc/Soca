#ifndef LST_H
#define LST_H

#include "Model.h"

/**

*/
class Lst : public Model {
public:
    Lst();

    virtual void    write_usr ( BinOut &nut, BinOut &uut, Database *db ) const;
    virtual void    write_str ( QDebug  dbg ) const;
    virtual int     attr_index( QString key ) const;
    virtual Model  *attr      ( QString key ) const;
    virtual void    push      ( Model *m );
    virtual Model  *attr      ( int index   ) const;
    virtual int     size      () const;
    virtual QString type() const;

    virtual bool _set( int size, QVector<Model *> &model_stack, QVector<QString> &string_stack );

    QVector<Model *> _data;
};

#endif // LST_H
