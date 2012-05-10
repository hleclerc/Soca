#ifndef DATABASE_H
#define DATABASE_H

#include "../Model/Model.h"
#include <QMap>

/**
*/
class Database {
public:
    Database();

    QMap<qint64,Model *> model_map; ///< server_id -> local Model *
};

#endif // DATABASE_H
