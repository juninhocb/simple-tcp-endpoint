#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <arpa/inet.h>
#include "client_data.h"

void * client_handle(void* cd){

    client_data *client = (struct client_data *)cd;
    char sendBuff[1024];
    time_t ticks; 

    memset(sendBuff, 0, sizeof(sendBuff)); 

    //Do the same as the blocking approach
    printf("Received connection from %s:%d\n", inet_ntoa(client->client_addr->sin_addr), ntohs(client->client_addr->sin_port));
    fflush(stdout);

    sleep(1);    

    ticks = time(NULL);
    snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        
    send(client->socket_code, sendBuff, strlen(sendBuff)+1, 0);

    close(client->socket_code);

    free(client->client_addr);
    free(client);

    return NULL;
}