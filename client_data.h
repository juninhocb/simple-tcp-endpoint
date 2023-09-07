#ifndef CLIENT_DATA_H
#define CLIENT_DATA_H

#include <netinet/in.h>

struct client_data_struct{
    int socket_code;
    struct sockaddr_in *client_addr;
};

typedef struct client_data_struct client_data; 

void *client_handle(void *cd);

#endif 

