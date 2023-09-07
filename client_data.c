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

    const char* http_response = "HTTP/1.0 200 OK\r\n"
                                "Content-Type: text/plain\r\n"
                                "Content-Length: 12\r\n"
                                "\r\n"
                                "Hello, World!";

        
    send(client->socket_code, http_response, strlen(http_response), 0);

    close(client->socket_code);

    free(client->client_addr);
    free(client);

    return NULL;
}