#include <Soca/Com/SodaClient.h>

int main( int argc, char **argv ) {
    SodaClient sc( QHostAddress::Any, 8890 );
    if ( not sc.connected() )
        return 1;

    MP obj = MP::new_obj();

    MP mp = sc.load( "/home/monkey/sessions" );
    mp.clear();
    srand( time( NULL ) );
    mp << MP::new_file( QString( "toto_%1" ).arg( rand() ), obj );

    mp.flush();
}
