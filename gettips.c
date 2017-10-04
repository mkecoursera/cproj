#include<stdio.h>
#include <fcntl.h>
#include <string.h>

#include<winsock2.h>
 
#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFFSIZE 4096

static void fgetstr(char *file_name , char *buf);

int main(int argc , char *argv[]){

int n;
char buf[BUFFSIZE];

    WSADATA wsa;
    SOCKET s;
struct hostent *remoteHost;    
struct sockaddr_in server;
   // char *message , response[4096];
    char response[4096],message[2048];
	char  *file_name = "request.json";
	//char *message;
//char *message_fmt = "POST /%s HTTP/1.0\r\n\r\n{\"cardNumbersHash\":[\"33B48AEEB64BED2D8FD64ED17B022C307AC8530C\",\"two\"]}\n";
char *message_fmt = "POST %s HTTP/1.0\r\nHost: %s:%s\r\nContent-Type: application/json\r\nCache-Control: no-cache\r\nContent-Length: %d\r\n\r\n%s";
    int recv_size, bytes, sent, received, total;
if (argc < 4) 
{ puts("Parameters: <host> <port> <URL>"); 
exit(0); 
}

fgetstr(file_name, buf);


printf("buff %s\n", buf);
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
	
	//message = "POST /tips/api/v1/tips HTTP/1.0\r\nHost: localhost:8080\r\nContent-Type: application/json\r\nCache-Control: no-cache\r\nContent-Length: 70\r\n\r\n{\"cardNumbersHash\":[\"33B48AEEB64BED2D8FD64ED17B022C307AC8530C\",\"two\"]}";
	sprintf(message,message_fmt,argv[3],argv[1],argv[2],strlen(buf),buf);
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
//	if( send(s , buf , n , 0) < 0)
//    {
//        puts("Send failed");
 //       return 1;
 //   }
     puts("JSON Send\n");
   
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

    if (received == total)
puts("ERROR storing complete response from socket");
        return 1;

    /* close the socket */
    close(s);



printf(buf);
//if (lseek(fd, 0, SEEK_CUR) == -1)
//printf("cannot seek\n");
//else
//printf("seek OK\n");
exit(0);
}

void fgetstr(char *s, char *buf){
int fd;
int n;
printf("*******************************\n");

if ((fd = open("request.json", O_RDONLY)) < 0) {
printf("json file open error");
exit(-1);
}
n = read(fd, buf, BUFFSIZE);

if(n == 0){
printf("read error");
close(fd);
exit(-1);
}
close(fd);

buf[n] = '\0';
printf("json file read");
//return n;

}


