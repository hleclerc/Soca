#ifndef BINOUT_H
#define BINOUT_H

#include <QByteArray>

/**
*/
class BinOut {
public:
    BinOut &operator<<( const QString &str ) {
        QByteArray tmp = str.toAscii();
        *this << int( tmp.size() );
        _data.append( tmp );
        return *this;
    }

    template<class T>
    BinOut &operator<<( const T &v ) {
        _data.append( reinterpret_cast<const char *>( &v ), sizeof( T ) );
        return *this;
    }

    void clear() { _data.clear(); }

    const QByteArray &data() const { return _data; }

private:
    QByteArray _data;
};

#endif // BINOUT_H
