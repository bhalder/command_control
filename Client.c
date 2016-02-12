/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
  int clientSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

    int type;
    int length;
    char value[1000];
    char * pos_typ = NULL;
    char * pos_len = NULL;
    char * pos_val = NULL;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
 
  recv(clientSocket, buffer, 1024, 0);
  pos_typ = strstr( buffer, "TYP:"); 
  pos_len = strstr( buffer, ";LEN:"); 
  pos_val = strstr( buffer, ";VAL:"); 

  printf("Data received: %s",buffer);   

  type = atoi( pos_typ + 4 );
  length = atoi( pos_len + 5);
  strncpy( value ,pos_val+5, length);  

  printf("\nType = %d ; Length = %d \nValue = %s", type, length, value);
  system( value );
  return 0;
}
