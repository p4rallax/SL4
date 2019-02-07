#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main( int argc ,char *argv[])  {
		int sock;
		struct sockaddr_in server;
		char message[1000] , server_reply [2000];
		char m1[10], m2[10], m3[3] ;
		
		
		sock = socket (AF_INET , SOCK_STREAM , 0 );
		if (sock == -1 )
			printf("\n could not create socket ");
			
		puts("\n socket created");
		
		server.sin_addr.s_addr =  inet_addr ( "127.0.0.1");
		server.sin_family = AF_INET;
		server.sin_port = htons( 8888);
		
		if(connect(sock , (struct sockaddr *)&server , sizeof(server)	) < 0)	{
				perror("\n connection failed. Error.");
				return 1;
				}
			
		puts("\n Connected");
		while(1)  {
				bzero( message, 2000);
				printf("\n enter message");
				scanf("%s ", message);
				
				if( send( sock, message , strlen(message) , 0 ) < 0 )	{
						puts ("\n Send failed.");
						return 1;
						}
				
				if ( recv (sock ,server_reply , 2000,0 ) < 0 ) 	{
						puts("\n Recv failed.");
						break;
					}
				
				
				puts ("\n Server reply : ");
				puts(server_reply);
				strncpy(server_reply ," " , 2000);
			}
			close(sock);
			return 0;
		}
