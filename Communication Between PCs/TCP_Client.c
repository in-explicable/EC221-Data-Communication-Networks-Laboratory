#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#define MAX 80
#define PORT 8080

void func(int sockfd)
{
        char buff[MAX];
        int n;
        while(1) {
                bzero(buff,sizeof(buff));
                printf("Enter the string:");
                n=0;
                while((buff[n++]=getchar())!='\n');
                write(sockfd,buff,sizeof(buff));
                bzero(buff,sizeof(buff));
                read(sockfd,buff,sizeof(buff));
                printf("From Server: %s", buff);
                if(strncmp(buff,"exit",4)==0) {
                        printf("Client Exit...\n");
                        break;
                }
        }
}

int main()
{
        int sockfd,connfd;
        struct sockaddr_in servaddr;
        sockfd = socket(AF_INET,SOCK_STREAM,0);
        
        if(sockfd==1) {
                printf("Socket creation failed...\n");
        }
        
                printf("Socket successfully created...\n");
        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=inet_addr("192.168.0.145");
        servaddr.sin_port=htons(PORT);
        connfd=connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
        if(connfd!=0) {
                printf("Connection with the server failed...\n");
                exit(0);
        }
                printf("Connected to the server...\n");
        func(sockfd);
        close(sockfd);        
}
                
