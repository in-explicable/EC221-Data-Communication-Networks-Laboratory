#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int connfd)
{
        char buff[MAX];
        int n;
        while(1) {
                bzero(buff,MAX);
                read(connfd,buff,sizeof(buff));
                printf("From client: %s\tto client", buff);
                bzero(buff,MAX);
                n=0;
                while((buff[n++]=getchar())!='\n');
                write(connfd,buff,sizeof(buff));
                if(strncmp("exit",buff,4)==0) {
                        printf("Server Exit...\n");
                        break;
                }
        }
}

int main()
{
        int sockfd,len;
        struct sockaddr_in servaddr, cli;
        sockfd = socket(AF_INET,SOCK_STREAM,0);
        if(sockfd==1) {
                printf("Socket creation failed...\n");
                exit(0);
        }
        
                printf("Socket successfully created...\n");
        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=htons(INADDR_ANY);
        servaddr.sin_port=htons(PORT);
        if((bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)))!=0) {
                printf("Socket bind failed...\n");
                exit(0);
        }
        
                printf("Socket successfully binded...\n");
        if((listen(sockfd,5))!=0) {
                printf("Listen failed...\n");
                exit(0);
        }
        
                printf("Server listening...\n");
        len=sizeof(cli);
        int connfd=accept(sockfd,(struct sockaddr*)&cli,&len);
        if(connfd<0) {
                printf("Server accept failed...\n");
                exit(0);
        }
        
                printf("Server accepted the client...\n");
        func(connfd);
        close(sockfd);
}
                
                
                
                
                
