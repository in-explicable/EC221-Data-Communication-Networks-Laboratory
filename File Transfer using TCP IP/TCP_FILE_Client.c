#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SIZE 1024
#define PORT 8080
void write_file(int sockfd)
{
int n;
FILE *fp;
char buffer[SIZE];
printf("\nEnter the file name: ");
scanf("%s",buffer);
fp=fopen("recv.txt","w");
if(send(sockfd,buffer,sizeof(buffer),0)==-1)
{
perror("\nError in sending file");
exit(1);
}
bzero(buffer,SIZE);
printf("\nFile content:\n");
while(1)
{
n=recv(sockfd,buffer,SIZE,0);
if(n<=0)
break;
fprintf(fp,"%s",buffer);
printf("%s",buffer);
bzero(buffer,SIZE);
}
fclose(fp);
}
int main(){
int sockfd,connfd;
struct sockaddr_in serv;
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd==1){
printf("\nSocket creation failed...\n");
exit(0);
}
printf("\nSocket successfully created...\n");
bzero(&serv,sizeof(serv));
serv.sin_family= AF_INET;
serv.sin_port=htons(PORT);
serv.sin_addr.s_addr=htonl(INADDR_ANY);
connfd=connect(sockfd,(struct sockaddr*)&serv,sizeof(serv));
if(connfd!=0) {
printf("\nConnection with server failed\n");
exit(0);
}else
{
printf("\nConnected to the server!!!\n\n");
}
write_file(sockfd);
close(sockfd);
return 0;
}
