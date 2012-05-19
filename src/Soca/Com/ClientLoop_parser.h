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
        sipe_data->ptr = 0;;
        sipe_data->str = 0;;
        sipe_data->callback = 0;;
    }
    ~SipeData() {
    }

    void *_inp_cont;
    SIPE_CHARP _mark[ 1 ];
    quint64 model_id;
    unsigned len;
    quint64 ptr;
    char *str;
    unsigned callback;
};
int parse( SipeData *sipe_data, SIPE_CHARP data, SIPE_CHARP end ) {
     if ( sipe_data->_inp_cont )
         goto *sipe_data->_inp_cont;
     
     #define INCR( N ) if ( ++data >= end ) goto p_##N; c_##N:
     
l_1: if ( *data != 'U' ) goto l_0;
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
     { sipe_data->model_id  = (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 12 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 13 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 14 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 24; }
     INCR( 15 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 32; }
     INCR( 16 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 40; }
     INCR( 17 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 48; }
     INCR( 18 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 56; }
     INCR( 19 )
     { sipe_data->len  = *reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 20 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 21 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 22 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) << 24; }
     { rep_update_PI32( sipe_data->model_id, sipe_data->len ); }
l_3: INCR( 23 )
     goto l_1;
l_0: if ( *data != 'V' ) goto l_2;
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
     INCR( 36 )
     INCR( 37 )
     INCR( 38 )
     INCR( 39 )
     data = sipe_data->_mark[ 0 ];
     { sipe_data->model_id  = (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 40 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 41 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 42 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 24; }
     INCR( 43 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 32; }
     INCR( 44 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 40; }
     INCR( 45 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 48; }
     INCR( 46 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 56; }
     INCR( 47 )
     { sipe_data->ptr  = (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 48 )
     { sipe_data->ptr += (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 49 )
     { sipe_data->ptr += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 50 )
     { sipe_data->ptr += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 24; }
     INCR( 51 )
     { sipe_data->ptr += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 32; }
     INCR( 52 )
     { sipe_data->ptr += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 40; }
     INCR( 53 )
     { sipe_data->ptr += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 48; }
     INCR( 54 )
     { sipe_data->ptr += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 56; }
     { rep_update_PI64( sipe_data->model_id, sipe_data->ptr ); }
     goto l_3;
l_2: if ( *data != 'W' ) goto l_4;
     INCR( 55 )
     sipe_data->_mark[ 0 ] = data;
     INCR( 56 )
     INCR( 57 )
     INCR( 58 )
     INCR( 59 )
     INCR( 60 )
     INCR( 61 )
     INCR( 62 )
     INCR( 63 )
     INCR( 64 )
     INCR( 65 )
     INCR( 66 )
     data = sipe_data->_mark[ 0 ];
     { sipe_data->model_id  = (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 67 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 68 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 69 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 24; }
     INCR( 70 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 32; }
     INCR( 71 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 40; }
     INCR( 72 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 48; }
     INCR( 73 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 56; }
     INCR( 74 )
     { sipe_data->len  = *reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 75 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 76 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 77 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) << 24; }
     { sipe_data->str = data + 1; data += sipe_data->len;  }
     { rep_update_cstr( sipe_data->model_id, sipe_data->str, sipe_data->len ); }
     goto l_3;
l_4: if ( *data != 'X' ) goto l_5;
     INCR( 78 )
     sipe_data->_mark[ 0 ] = data;
     INCR( 79 )
     INCR( 80 )
     INCR( 81 )
     INCR( 82 )
     INCR( 83 )
     INCR( 84 )
     INCR( 85 )
     INCR( 86 )
     INCR( 87 )
     INCR( 88 )
     INCR( 89 )
     INCR( 90 )
     INCR( 91 )
     INCR( 92 )
     INCR( 93 )
     INCR( 94 )
     INCR( 95 )
     INCR( 96 )
     INCR( 97 )
     data = sipe_data->_mark[ 0 ];
     { sipe_data->model_id  = (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 98 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 99 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 100 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 24; }
     INCR( 101 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 32; }
     INCR( 102 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 40; }
     INCR( 103 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 48; }
     INCR( 104 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 56; }
     INCR( 105 )
     { sipe_data->ptr  = (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 106 )
     { sipe_data->ptr += (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 107 )
     { sipe_data->ptr += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 108 )
     { sipe_data->ptr += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 24; }
     INCR( 109 )
     { sipe_data->ptr += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 32; }
     INCR( 110 )
     { sipe_data->ptr += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 40; }
     INCR( 111 )
     { sipe_data->ptr += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 48; }
     INCR( 112 )
     { sipe_data->ptr += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 56; }
     INCR( 113 )
     { sipe_data->len  = *reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 114 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 115 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 116 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) << 24; }
     { rep_update_6432( sipe_data->model_id, sipe_data->ptr, sipe_data->len ); }
     goto l_3;
l_5: if ( *data != 'p' ) goto l_6;
     INCR( 117 )
     sipe_data->_mark[ 0 ] = data;
     INCR( 118 )
     INCR( 119 )
     INCR( 120 )
     data = sipe_data->_mark[ 0 ];
     { sipe_data->len  = *reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 121 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 122 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 123 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) << 24; }
     { sipe_data->str = data + 1; data += sipe_data->len;  }
     { rep_push_string( sipe_data->str, sipe_data->len ); }
     goto l_3;
l_6: if ( *data != 'P' ) goto l_7;
     INCR( 124 )
     sipe_data->_mark[ 0 ] = data;
     INCR( 125 )
     INCR( 126 )
     INCR( 127 )
     INCR( 128 )
     INCR( 129 )
     INCR( 130 )
     INCR( 131 )
     data = sipe_data->_mark[ 0 ];
     { sipe_data->model_id  = (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 132 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 133 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 134 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 24; }
     INCR( 135 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 32; }
     INCR( 136 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 40; }
     INCR( 137 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 48; }
     INCR( 138 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 56; }
     { rep_push_model( sipe_data->model_id ); }
     goto l_3;
l_7: if ( *data != 'N' ) goto l_8;
     INCR( 139 )
     sipe_data->_mark[ 0 ] = data;
     INCR( 140 )
     INCR( 141 )
     INCR( 142 )
     INCR( 143 )
     INCR( 144 )
     INCR( 145 )
     INCR( 146 )
     INCR( 147 )
     INCR( 148 )
     INCR( 149 )
     INCR( 150 )
     data = sipe_data->_mark[ 0 ];
     { sipe_data->model_id  = (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 151 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 152 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 153 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 24; }
     INCR( 154 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 32; }
     INCR( 155 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 40; }
     INCR( 156 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 48; }
     INCR( 157 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 56; }
     INCR( 158 )
     { sipe_data->len  = *reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 159 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 160 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 161 )
     { sipe_data->len += *reinterpret_cast<const unsigned char *>( data ) << 24; }
     { sipe_data->str = data + 1; data += sipe_data->len;  }
     { rep_creation( sipe_data->model_id, sipe_data->str, sipe_data->len ); }
     goto l_3;
l_8: if ( *data != 'L' ) goto l_9;
     INCR( 162 )
     sipe_data->_mark[ 0 ] = data;
     INCR( 163 )
     INCR( 164 )
     INCR( 165 )
     INCR( 166 )
     INCR( 167 )
     INCR( 168 )
     INCR( 169 )
     INCR( 170 )
     INCR( 171 )
     INCR( 172 )
     INCR( 173 )
     data = sipe_data->_mark[ 0 ];
     { sipe_data->model_id  = (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 174 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 175 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 176 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 24; }
     INCR( 177 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 32; }
     INCR( 178 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 40; }
     INCR( 179 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 48; }
     INCR( 180 )
     { sipe_data->model_id += (quint64)*reinterpret_cast<const unsigned char *>( data ) << 56; }
     INCR( 181 )
     { sipe_data->callback  = *reinterpret_cast<const unsigned char *>( data ) <<  0; }
     INCR( 182 )
     { sipe_data->callback += *reinterpret_cast<const unsigned char *>( data ) <<  8; }
     INCR( 183 )
     { sipe_data->callback += *reinterpret_cast<const unsigned char *>( data ) << 16; }
     INCR( 184 )
     { sipe_data->callback += *reinterpret_cast<const unsigned char *>( data ) << 24; }
     { rep_load( sipe_data->model_id, sipe_data->callback ); }
     goto l_3;
l_9: if ( *data != 'E' ) goto l_10;
     { rep_end(); }
     goto l_3;
l_10:sipe_data->_inp_cont = &&l_10;
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
p_47:sipe_data->_inp_cont = &&c_47; return 0;
p_48:sipe_data->_inp_cont = &&c_48; return 0;
p_49:sipe_data->_inp_cont = &&c_49; return 0;
p_50:sipe_data->_inp_cont = &&c_50; return 0;
p_51:sipe_data->_inp_cont = &&c_51; return 0;
p_52:sipe_data->_inp_cont = &&c_52; return 0;
p_53:sipe_data->_inp_cont = &&c_53; return 0;
p_54:sipe_data->_inp_cont = &&c_54; return 0;
p_55:sipe_data->_inp_cont = &&c_55; return 0;
p_56:sipe_data->_inp_cont = &&c_56; return 0;
p_57:sipe_data->_inp_cont = &&c_57; return 0;
p_58:sipe_data->_inp_cont = &&c_58; return 0;
p_59:sipe_data->_inp_cont = &&c_59; return 0;
p_60:sipe_data->_inp_cont = &&c_60; return 0;
p_61:sipe_data->_inp_cont = &&c_61; return 0;
p_62:sipe_data->_inp_cont = &&c_62; return 0;
p_63:sipe_data->_inp_cont = &&c_63; return 0;
p_64:sipe_data->_inp_cont = &&c_64; return 0;
p_65:sipe_data->_inp_cont = &&c_65; return 0;
p_66:sipe_data->_inp_cont = &&c_66; return 0;
p_67:sipe_data->_inp_cont = &&c_67; return 0;
p_68:sipe_data->_inp_cont = &&c_68; return 0;
p_69:sipe_data->_inp_cont = &&c_69; return 0;
p_70:sipe_data->_inp_cont = &&c_70; return 0;
p_71:sipe_data->_inp_cont = &&c_71; return 0;
p_72:sipe_data->_inp_cont = &&c_72; return 0;
p_73:sipe_data->_inp_cont = &&c_73; return 0;
p_74:sipe_data->_inp_cont = &&c_74; return 0;
p_75:sipe_data->_inp_cont = &&c_75; return 0;
p_76:sipe_data->_inp_cont = &&c_76; return 0;
p_77:sipe_data->_inp_cont = &&c_77; return 0;
p_78:sipe_data->_inp_cont = &&c_78; return 0;
p_79:sipe_data->_inp_cont = &&c_79; return 0;
p_80:sipe_data->_inp_cont = &&c_80; return 0;
p_81:sipe_data->_inp_cont = &&c_81; return 0;
p_82:sipe_data->_inp_cont = &&c_82; return 0;
p_83:sipe_data->_inp_cont = &&c_83; return 0;
p_84:sipe_data->_inp_cont = &&c_84; return 0;
p_85:sipe_data->_inp_cont = &&c_85; return 0;
p_86:sipe_data->_inp_cont = &&c_86; return 0;
p_87:sipe_data->_inp_cont = &&c_87; return 0;
p_88:sipe_data->_inp_cont = &&c_88; return 0;
p_89:sipe_data->_inp_cont = &&c_89; return 0;
p_90:sipe_data->_inp_cont = &&c_90; return 0;
p_91:sipe_data->_inp_cont = &&c_91; return 0;
p_92:sipe_data->_inp_cont = &&c_92; return 0;
p_93:sipe_data->_inp_cont = &&c_93; return 0;
p_94:sipe_data->_inp_cont = &&c_94; return 0;
p_95:sipe_data->_inp_cont = &&c_95; return 0;
p_96:sipe_data->_inp_cont = &&c_96; return 0;
p_97:sipe_data->_inp_cont = &&c_97; return 0;
p_98:sipe_data->_inp_cont = &&c_98; return 0;
p_99:sipe_data->_inp_cont = &&c_99; return 0;
p_100:sipe_data->_inp_cont = &&c_100; return 0;
p_101:sipe_data->_inp_cont = &&c_101; return 0;
p_102:sipe_data->_inp_cont = &&c_102; return 0;
p_103:sipe_data->_inp_cont = &&c_103; return 0;
p_104:sipe_data->_inp_cont = &&c_104; return 0;
p_105:sipe_data->_inp_cont = &&c_105; return 0;
p_106:sipe_data->_inp_cont = &&c_106; return 0;
p_107:sipe_data->_inp_cont = &&c_107; return 0;
p_108:sipe_data->_inp_cont = &&c_108; return 0;
p_109:sipe_data->_inp_cont = &&c_109; return 0;
p_110:sipe_data->_inp_cont = &&c_110; return 0;
p_111:sipe_data->_inp_cont = &&c_111; return 0;
p_112:sipe_data->_inp_cont = &&c_112; return 0;
p_113:sipe_data->_inp_cont = &&c_113; return 0;
p_114:sipe_data->_inp_cont = &&c_114; return 0;
p_115:sipe_data->_inp_cont = &&c_115; return 0;
p_116:sipe_data->_inp_cont = &&c_116; return 0;
p_117:sipe_data->_inp_cont = &&c_117; return 0;
p_118:sipe_data->_inp_cont = &&c_118; return 0;
p_119:sipe_data->_inp_cont = &&c_119; return 0;
p_120:sipe_data->_inp_cont = &&c_120; return 0;
p_121:sipe_data->_inp_cont = &&c_121; return 0;
p_122:sipe_data->_inp_cont = &&c_122; return 0;
p_123:sipe_data->_inp_cont = &&c_123; return 0;
p_124:sipe_data->_inp_cont = &&c_124; return 0;
p_125:sipe_data->_inp_cont = &&c_125; return 0;
p_126:sipe_data->_inp_cont = &&c_126; return 0;
p_127:sipe_data->_inp_cont = &&c_127; return 0;
p_128:sipe_data->_inp_cont = &&c_128; return 0;
p_129:sipe_data->_inp_cont = &&c_129; return 0;
p_130:sipe_data->_inp_cont = &&c_130; return 0;
p_131:sipe_data->_inp_cont = &&c_131; return 0;
p_132:sipe_data->_inp_cont = &&c_132; return 0;
p_133:sipe_data->_inp_cont = &&c_133; return 0;
p_134:sipe_data->_inp_cont = &&c_134; return 0;
p_135:sipe_data->_inp_cont = &&c_135; return 0;
p_136:sipe_data->_inp_cont = &&c_136; return 0;
p_137:sipe_data->_inp_cont = &&c_137; return 0;
p_138:sipe_data->_inp_cont = &&c_138; return 0;
p_139:sipe_data->_inp_cont = &&c_139; return 0;
p_140:sipe_data->_inp_cont = &&c_140; return 0;
p_141:sipe_data->_inp_cont = &&c_141; return 0;
p_142:sipe_data->_inp_cont = &&c_142; return 0;
p_143:sipe_data->_inp_cont = &&c_143; return 0;
p_144:sipe_data->_inp_cont = &&c_144; return 0;
p_145:sipe_data->_inp_cont = &&c_145; return 0;
p_146:sipe_data->_inp_cont = &&c_146; return 0;
p_147:sipe_data->_inp_cont = &&c_147; return 0;
p_148:sipe_data->_inp_cont = &&c_148; return 0;
p_149:sipe_data->_inp_cont = &&c_149; return 0;
p_150:sipe_data->_inp_cont = &&c_150; return 0;
p_151:sipe_data->_inp_cont = &&c_151; return 0;
p_152:sipe_data->_inp_cont = &&c_152; return 0;
p_153:sipe_data->_inp_cont = &&c_153; return 0;
p_154:sipe_data->_inp_cont = &&c_154; return 0;
p_155:sipe_data->_inp_cont = &&c_155; return 0;
p_156:sipe_data->_inp_cont = &&c_156; return 0;
p_157:sipe_data->_inp_cont = &&c_157; return 0;
p_158:sipe_data->_inp_cont = &&c_158; return 0;
p_159:sipe_data->_inp_cont = &&c_159; return 0;
p_160:sipe_data->_inp_cont = &&c_160; return 0;
p_161:sipe_data->_inp_cont = &&c_161; return 0;
p_162:sipe_data->_inp_cont = &&c_162; return 0;
p_163:sipe_data->_inp_cont = &&c_163; return 0;
p_164:sipe_data->_inp_cont = &&c_164; return 0;
p_165:sipe_data->_inp_cont = &&c_165; return 0;
p_166:sipe_data->_inp_cont = &&c_166; return 0;
p_167:sipe_data->_inp_cont = &&c_167; return 0;
p_168:sipe_data->_inp_cont = &&c_168; return 0;
p_169:sipe_data->_inp_cont = &&c_169; return 0;
p_170:sipe_data->_inp_cont = &&c_170; return 0;
p_171:sipe_data->_inp_cont = &&c_171; return 0;
p_172:sipe_data->_inp_cont = &&c_172; return 0;
p_173:sipe_data->_inp_cont = &&c_173; return 0;
p_174:sipe_data->_inp_cont = &&c_174; return 0;
p_175:sipe_data->_inp_cont = &&c_175; return 0;
p_176:sipe_data->_inp_cont = &&c_176; return 0;
p_177:sipe_data->_inp_cont = &&c_177; return 0;
p_178:sipe_data->_inp_cont = &&c_178; return 0;
p_179:sipe_data->_inp_cont = &&c_179; return 0;
p_180:sipe_data->_inp_cont = &&c_180; return 0;
p_181:sipe_data->_inp_cont = &&c_181; return 0;
p_182:sipe_data->_inp_cont = &&c_182; return 0;
p_183:sipe_data->_inp_cont = &&c_183; return 0;
p_184:sipe_data->_inp_cont = &&c_184; return 0;
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
