#ifndef BINOUT_H
#define BINOUT_H

#include <QByteArray>

/**
*/
class BinOut {
public:
    BinOut &BinOut::operator<<( const QString &str ) {
        QByteArray tmp = str.toAscii();
        *this << int( tmp.size() );
        data.append( tmp );
        return *this;
    }

    template<class T>
    BinOut &operator<<( const T &v ) {
        data.append( reinterpret_cast<const char *>( &v ), sizeof( T ) );
        return *this;
    }

private:
    QByteArray data;
};

#endif // BINOUT_H
