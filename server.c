#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>


void *connection_handler(void *);

int main( int argc,  char *argv[]){
		int socket_desc , client_sock , c , *new_sock;
		struct sockaddr_in server, client;
		
		socket_desc = socket ( AF_INET , SOCK_STREAM , 0 );
		if ( socket_desc == -1) 
			printf("\n Could not create socket");
			puts("\n Socket created");
				server.sin_family = AF_INET;
				server.sin_addr.s_addr = INADDR_ANY ;
				server.sin_port = htons(8888);
				
				if( bind (socket_desc, (struct sockaddr *)&server , sizeof(server)) < 0 ) {
						perror( "\nBind failed. Error.");
						return 1;
						}
						
						puts("\n Bind done.");
						
						listen(socket_desc, 3);
						
						
						puts("\n Waiting for incoming connections");
						c= sizeof(struct sockaddr_in);
						
						
						puts("Waiting for incoming connections");
						c = sizeof(struct sockaddr_in);
						
						while( (client_sock  = accept(socket_desc , (struct sockaddr*)&client , (socklen_t*)&c)) ) {
								puts("\n Connection accepted");
								
								pthread_t sniffer_thread;
								new_sock =malloc(1);
								*new_sock = client_sock;
								if( pthread_create ( &sniffer_thread , NULL , connection_handler , (void*) new_sock ) < 0 )  {
										perror ( "\n Could not create thread");
										return 1;
										}
										
								//pthread_join( sniffer_thread , NULL);
								puts("\n Handler assigned");
								}
								
								if(client_sock <0 ) {
									perror("\n Accept failed");
									return 1;
								  }
		}
		
		
void *connection_handler(void *socket_desc)  {
		int sock = * (int *) socket_desc;
		int read_size;
		char *message,  client_message[200];
		
		while( ( read_size = recv (sock , client_message, 2000, 0 )) > 0 ) 	{
				write(sock , client_message , strlen (client_message) ); 
				}
				
				if(read_size == 0)  {
					puts(" \n client disconnected " );
					fflush(stdout);
					}
					
				else if (read_size == -1) 
					perror("\n recv failed");
					
					
					free(socket_desc);
					return 0;
							
}		
								  
