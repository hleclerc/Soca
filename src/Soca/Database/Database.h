#ifndef DATABASE_H
#define DATABASE_H

#include "../Model/Model.h"
#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QSet>
class ClientLoop;

/**
*/
class Database : public QObject {
    Q_OBJECT
public:
    Database();
    Model  *model( qint64 m ) const; ///< server_id -> local Model *
    Model  *signal_change( Model *m, bool from_ext = false ); ///<
    quint64 new_tmp_server_id();

private slots:
    void    end_round(); ///<

signals:
    void    _model_sig( Model * );

public:
    QMap<qint64,Model *> model_map;      ///< server_id -> local Model *
    QSet<ClientLoop *>   clients;        ///<
    QSet<Model *>        changed_models; ///< not the most efficient containers...
    quint64              prev_tmp_server_id;
    bool                 reg_changes;    ///<
    bool                 end_round_timer; ///<
};

#endif // DATABASE_H
