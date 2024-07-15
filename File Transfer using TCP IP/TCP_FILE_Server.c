#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SIZE 1024
#define PORT 8080
void send_file(int sockfd)
{
int n;
FILE *fp;
char buffer[SIZE];
bzero(buffer,SIZE);
n= recv(sockfd,buffer, SIZE,0);
fp= fopen(buffer,"r");
while((fgets(buffer,SIZE,fp))!=NULL)
{
if(send(sockfd,buffer,sizeof(buffer),0)==-1)
{
perror("\nError in sending file");
exit(1);
}
bzero(buffer,SIZE);
}
printf("\nFile sent successfully\n");
fclose(fp);
}
int main()
{
int sockfd,len;
struct sockaddr_in serv, cli;
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<=0)
{
printf("\nSocket creation failed...\n");
exit(1);
}
printf("\nSocket successfully created...\n");
bzero(&serv,sizeof(serv));
serv.sin_family= AF_INET;
serv.sin_port=htons(PORT);
serv.sin_addr.s_addr=htonl(INADDR_ANY);
if((bind(sockfd,(struct sockaddr*)&serv, sizeof(serv)))!=0){
printf("\nSocket bind failed...\n");
exit(0);
}
printf("\nSocket successfully binded\n");
if((listen(sockfd,5))!=0)
{
printf("\nListen failed...\n");
exit(0);}
printf("\nServer listening...\n");
len = sizeof(cli);
int connfd = accept(sockfd, (struct sockaddr*)&cli, &len);
if(connfd<0)
{
printf("\nServer accept failed...\n");
exit(0);
}
printf("\nServer accepted the client...\n");
send_file(connfd);
close(sockfd);
return 0;
}
