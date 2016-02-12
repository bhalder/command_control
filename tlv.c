
#include "net.h"
#include "string.h"

// Author : Barun Halder
// Date : February, 2016
// TLV header

enum tlv_type = { INT, CHAR, STR };

typedef struct tlv_t {
    int type;
    int length;
    char * value;
} tlv;

tlv * create_tlv( int type, int length, char * value) {

    tlv * new_tlv = (tlv *) malloc( sizeof(tlv) );
    new_tlv->value = (char *) malloc( strlen( value )+1 );
    strcpy( new_tlv->value, value );
    return new_tlv;
}
int connect_and_send( int sock, tlv * tlv_ref ) {

}


tlv * receive_and_tlv( int sock );
