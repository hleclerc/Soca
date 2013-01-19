#include <Soca/Model/TypedArray.h>
#include <Soca/Com/SodaClient.h>

int main( int argc, char **argv ) {
    SodaClient sc( QHostAddress::Any, 8890 );
    if ( not sc.connected() )
        return 1;

    MP mp = sc.load( "/pouet" );
    srand( time( NULL ) );
    // mp.clear();

    static_cast<TypedArray<double> *>( mp.model() )->_data.resize( 4 * 40000 );
    static_cast<TypedArray<double> *>( mp.model() )->_data[ 0 ] = rand();
    static_cast<TypedArray<double> *>( mp.model() )->_size[ 1 ] = 40000;
    mp.signal_change();

    // mp.flush();
}
