#include "Database.h"

#pragma lib_name QtCore

Database::Database() {
}

Model *Database::model( qint64 m ) const {
    QMap<qint64,Model *>::const_iterator iter = model_map.find( m );
    if ( iter != model_map.end() )
        return iter.value();
    return 0;
}
