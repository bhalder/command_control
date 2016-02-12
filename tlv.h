
#include "net.h"
// Author : Barun Halder
// Date : February, 2016
// TLV header

enum tlv_type = { INT, CHAR, STR };

typedef struct tlv_t {
    int type;
    int length;
    char * value;
} tlv;

tlv * create_tlv( int type, int length, char * value);
int connect_and_send( int sock, tlv * tlv_ref );
tlv * receive_and_tlv( int sock );
