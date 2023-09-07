#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <pthread.h>
#include "client_data.h"

#define PORT_NUMBER 8080 



int main () {

    int connection_factory = 0;
    int socket_factory = 0;
    struct sockaddr_in serv_addr; 
    struct sockaddr_in client_addr; 
    unsigned int addrlen = sizeof(client_addr);
    client_data *cd; 
    pthread_t thr;

    char sendBuff[1025];
    time_t ticks; 

    printf("Configuring socket to listen TCP connections \n"); 

    /* Create socket
        DOMAIN = AF_INET = Address Family IPV4
        SOCK_STREAM =  Sequenced, reliable, connection-based byte streams. 
        IPPROTO_TCP = TCP  
    */
    socket_factory = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(socket_factory < 0){
    	perror("socket err");
    	return 1;
    }

    /* Empty I/O buffers */
    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(sendBuff, 0, sizeof(sendBuff)); 

	/* Whatever ip can connect to this socket, listening in port 8080 */ 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT_NUMBER); 


    printf("Configuring bind to specific address and port \n"); 

	/* Bind socket sockaddr_in */
    int bind_socket = bind(socket_factory, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    if (bind_socket < 0){
    	perror("bind err");
    	return 1;
    }

	/* Start listening, setting 10 connections to pool queue */
    listen(socket_factory, 10); 
    printf("Threading Server started at port %d \n", PORT_NUMBER);

    while(1) {

        cd = (client_data *)malloc(sizeof(client_data));

        cd->client_addr = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
        
        addrlen = sizeof(struct sockaddr_in);

		/* Wait for connection */	
        cd->socket_code = accept(socket_factory, (struct sockaddr*)&client_addr, &addrlen); 

		pthread_create(&thr, NULL, client_handle, (void *)cd);
        pthread_detach(thr);

     }  
}