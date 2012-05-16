#ifdef SIPE_MAIN
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#endif // SIPE_MAIN
#ifndef SIPE_CHARP
#define SIPE_CHARP const char *
#endif // SIPE_CHARP
struct SipeData {
    SipeData() {
        _inp_cont = 0;
        SipeData *sipe_data = this;
        sipe_data->model_id = 0;;
        sipe_data->len = 0;;
        sipe_data->str = 0;;
        sipe_data->callback = 0;;
    }
    ~SipeData() {
    }

    void *_inp_cont;
    SIPE_CHARP _mark[ 1 ];
    unsigned long model_id;
    unsigned len;
    char *str;
    unsigned callback;
};
int parse( SipeData *sipe_data, SIPE_CHARP data, SIPE_CHARP end ) {
     if ( sipe_data->_inp_cont )
         goto *sipe_data->_inp_cont;
     
     #define INCR( N ) if ( ++data >= end ) goto p_##N; c_##N:
     
l_1: if ( *data != 'N' ) goto l_0;
     INCR( 0 )
     sipe_data->_mark[ 0 ] = data;
     INCR( 1 )
     INCR( 2 )
     INCR( 3 )
     INCR( 4 )
     INCR( 5 )
     INCR( 6 )
     INCR( 7 )
     INCR( 8 )
     INCR( 9 )
     INCR( 10 )
     INCR( 11 )
     data = sipe_data->_mark[ 0 ];
     { sipe_data->model_id  = (unsigned long)*reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 12 )
     { sipe_data->model_id += (unsigned long)*reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 13 )
     { sipe_data->model_id += (unsigned long)*reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 14 )
     { sipe_data->model_id += (unsigned long)*reinterpret_cast<const unsigned char *>( data ) << 24; }
     INCR( 15 )
     { sipe_data->model_id += (unsigned long)*reinterpret_cast<const unsigned char *>( data ) << 32; }
     INCR( 16 )
     { sipe_data->model_id += (unsigned long)*reinterpret_cast<const unsigned char *>( data ) << 40; }
     INCR( 17 )
     { sipe_data->model_id += (unsigned long)*reinterpret_cast<const unsigned char *>( data ) << 48; }
     INCR( 18 )
     { sipe_data->model_id += (unsigned long)*reinterpret_cast<const unsigned char *>( data ) << 56; }
     INCR( 19 )
     { sipe_data->len  = *reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 20 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 21 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 22 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) << 24; }
     { sipe_data->str = ++data; data += sipe_data->len;  }
     { rep_creation( sipe_data->model_id, sipe_data->str, sipe_data->len ); }
l_3: INCR( 23 )
     goto l_1;
l_0: if ( *data != 'L' ) goto l_2;
     INCR( 24 )
     sipe_data->_mark[ 0 ] = data;
     INCR( 25 )
     INCR( 26 )
     INCR( 27 )
     INCR( 28 )
     INCR( 29 )
     INCR( 30 )
     INCR( 31 )
     INCR( 32 )
     INCR( 33 )
     INCR( 34 )
     INCR( 35 )
     data = sipe_data->_mark[ 0 ];
     { sipe_data->model_id  = (unsigned long)*reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 36 )
     { sipe_data->model_id += (unsigned long)*reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 37 )
     { sipe_data->model_id += (unsigned long)*reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 38 )
     { sipe_data->model_id += (unsigned long)*reinterpret_cast<const unsigned char *>( data ) << 24; }
     INCR( 39 )
     { sipe_data->model_id += (unsigned long)*reinterpret_cast<const unsigned char *>( data ) << 32; }
     INCR( 40 )
     { sipe_data->model_id += (unsigned long)*reinterpret_cast<const unsigned char *>( data ) << 40; }
     INCR( 41 )
     { sipe_data->model_id += (unsigned long)*reinterpret_cast<const unsigned char *>( data ) << 48; }
     INCR( 42 )
     { sipe_data->model_id += (unsigned long)*reinterpret_cast<const unsigned char *>( data ) << 56; }
     INCR( 43 )
     { sipe_data->callback  = *reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 44 )
     { sipe_data->callback += *reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 45 )
     { sipe_data->callback += *reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 46 )
     { sipe_data->callback += *reinterpret_cast<const unsigned char *>( data ) << 24; }
     { rep_load( sipe_data->model_id, sipe_data->callback ); }
     goto l_3;
l_2: if ( *data != 'E' ) goto l_4;
     { rep_end(); }
     goto l_3;
l_4: sipe_data->_inp_cont = &&l_4;
     return 1;
p_0: sipe_data->_inp_cont = &&c_0; return 0;
p_1: sipe_data->_inp_cont = &&c_1; return 0;
p_2: sipe_data->_inp_cont = &&c_2; return 0;
p_3: sipe_data->_inp_cont = &&c_3; return 0;
p_4: sipe_data->_inp_cont = &&c_4; return 0;
p_5: sipe_data->_inp_cont = &&c_5; return 0;
p_6: sipe_data->_inp_cont = &&c_6; return 0;
p_7: sipe_data->_inp_cont = &&c_7; return 0;
p_8: sipe_data->_inp_cont = &&c_8; return 0;
p_9: sipe_data->_inp_cont = &&c_9; return 0;
p_10:sipe_data->_inp_cont = &&c_10; return 0;
p_11:sipe_data->_inp_cont = &&c_11; return 0;
p_12:sipe_data->_inp_cont = &&c_12; return 0;
p_13:sipe_data->_inp_cont = &&c_13; return 0;
p_14:sipe_data->_inp_cont = &&c_14; return 0;
p_15:sipe_data->_inp_cont = &&c_15; return 0;
p_16:sipe_data->_inp_cont = &&c_16; return 0;
p_17:sipe_data->_inp_cont = &&c_17; return 0;
p_18:sipe_data->_inp_cont = &&c_18; return 0;
p_19:sipe_data->_inp_cont = &&c_19; return 0;
p_20:sipe_data->_inp_cont = &&c_20; return 0;
p_21:sipe_data->_inp_cont = &&c_21; return 0;
p_22:sipe_data->_inp_cont = &&c_22; return 0;
p_23:sipe_data->_inp_cont = &&c_23; return 0;
p_24:sipe_data->_inp_cont = &&c_24; return 0;
p_25:sipe_data->_inp_cont = &&c_25; return 0;
p_26:sipe_data->_inp_cont = &&c_26; return 0;
p_27:sipe_data->_inp_cont = &&c_27; return 0;
p_28:sipe_data->_inp_cont = &&c_28; return 0;
p_29:sipe_data->_inp_cont = &&c_29; return 0;
p_30:sipe_data->_inp_cont = &&c_30; return 0;
p_31:sipe_data->_inp_cont = &&c_31; return 0;
p_32:sipe_data->_inp_cont = &&c_32; return 0;
p_33:sipe_data->_inp_cont = &&c_33; return 0;
p_34:sipe_data->_inp_cont = &&c_34; return 0;
p_35:sipe_data->_inp_cont = &&c_35; return 0;
p_36:sipe_data->_inp_cont = &&c_36; return 0;
p_37:sipe_data->_inp_cont = &&c_37; return 0;
p_38:sipe_data->_inp_cont = &&c_38; return 0;
p_39:sipe_data->_inp_cont = &&c_39; return 0;
p_40:sipe_data->_inp_cont = &&c_40; return 0;
p_41:sipe_data->_inp_cont = &&c_41; return 0;
p_42:sipe_data->_inp_cont = &&c_42; return 0;
p_43:sipe_data->_inp_cont = &&c_43; return 0;
p_44:sipe_data->_inp_cont = &&c_44; return 0;
p_45:sipe_data->_inp_cont = &&c_45; return 0;
p_46:sipe_data->_inp_cont = &&c_46; return 0;
}
#ifdef SIPE_CLASS
int parse( SIPE_CHARP beg, SIPE_CHARP end ) {
    return parse( &sipe_data, beg, end );
}
SipeData sipe_data;
#endif // SIPE_CLASS
#ifdef SIPE_MAIN
int parse_file( int fd ) {
    SipeData sd;
    char buffer[ 2048 ];
    while ( true ) {
        int r = read( fd, buffer, 2048 );
        if ( r == 0 )
            return 0;
        if ( int res = parse( &sd, buffer, buffer + r ) )
            return res;
    }
    return 0;
}
int main( int argc, char **argv ) {
    if ( argc == 1 )
        return parse_file( 0 );
    for( int i = 1; i < argc; ++i ) {
        int fd = open( argv[ i ], O_RDONLY );
        if ( fd < 0 )
            perror( "Opening file" );
        else
            parse_file( fd );
    }
    return 0;
}
#endif // SIPE_MAIN
