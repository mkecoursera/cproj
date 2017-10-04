/*
    Create a TCP socket
*/
 
#include<stdio.h>
#include<winsock2.h>
 
#pragma comment(lib,"ws2_32.lib") //Winsock Library
 
int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET s;
struct hostent *remoteHost;    
struct sockaddr_in server;
   // char *message , response[4096];
    char message[1024],response[4096];
char *message_fmt = "GET /%s HTTP/1.0\r\n\r\n";
    int recv_size, bytes, sent, received, total;
if (argc < 4) 
{ puts("Parameters: <host> <port> <URL>"); 
exit(0); 
}
 
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
     
    printf("Initialised.\n");
     
    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
 
    printf("Socket created.\n");
     
    remoteHost = gethostbyname(argv[1]);
sprintf(message,message_fmt,argv[3]);
printf("Request:\n%s\n",message);
memcpy(&server.sin_addr.s_addr,remoteHost ->h_addr,remoteHost ->h_length);    
//server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons( atoi(argv[2]) );
 
    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }
     
    puts("Connected");

    //Send data
    if( send(s , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");
     
   
/* receive the response */
   // memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
     do {
       printf("%s", response);
       memset(response, 0, sizeof(response));
       bytes = recv(s, response, 1024, 0);
        if (bytes < 0)
           printf("ERROR reading response from socket");
       if (bytes == 0)
           break;
       received+=bytes;
    } while (1);

    if (received == total){
puts("ERROR storing complete response from socket");
        return 1;
	}
    /* close the socket */
    close(s);





  //  puts(server_reply);
 
    return 0;
}