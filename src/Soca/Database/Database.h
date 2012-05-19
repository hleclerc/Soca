#ifndef DATABASE_H
#define DATABASE_H

#include "../Model/Model.h"
#include <QtCore/QMap>

/**
*/
class Database {
public:
    Database();
    Model *model( qint64 m ) const;

    QMap<qint64,Model *> model_map; ///< server_id -> local Model *
};

#endif // DATABASE_H
