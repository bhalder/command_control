/****************** SERVER CODE ****************/
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 10

typedef struct connection_t {
    pthread_t tid;
    int sock;
    // This can be extended later to include more details related to 
    // the connection

} connection;

typedef struct command_t {
    int type;
} command;


void command_prompt(char * cmd) {
    char cmd_in[512];
    printf("\n@> ");
    scanf("%s", cmd_in);
    strcpy(cmd, cmd_in);
}

void * do_work( void * fptr ) {
    int newSocket = *(int*)fptr;
    char buffer[1024] = "TYP:10;LEN:7;VAL:/bin/sh";
    while(1) {
        //command_prompt( buffer );
        send(newSocket,buffer,strlen(buffer),0);
    }
    close( newSocket );
    return NULL;
}

int main(){
    int welcomeSocket, *newSocket = NULL;
    pthread_t threads[NUM_THREADS];
    int thread = 0;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
      
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    while(1) {
        if(listen(welcomeSocket,5)==0)
            printf("Listening\n");
        else
            printf("Error\n");
      
        addr_size = sizeof serverStorage;
        newSocket = ( int * ) malloc( sizeof( int ) );
        *newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
        int rc = pthread_create(&threads[thread++], NULL, do_work, (void *)newSocket);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(0);
        } 
    }
    return 0;
}
