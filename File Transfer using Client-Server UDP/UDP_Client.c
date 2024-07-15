#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 8088
#define BUFF 32
#define KEY 'S'
#define FLAG 0
void clearBuf(char * b){
for(int i=0;i<BUFF;++i)
b[i]='\0';
}
char cipher(char ch){
return ch^KEY;
}
int recvFile(char * buff,int s){
char ch;
for(int i=0;i<s;++i){
ch=buff[i];
ch=cipher(ch);
if(ch==EOF)
return 1;
else
printf("%c",ch);
}
return 0;
}
int main(){
int sockfd,nbytes;
struct sockaddr_in addr;
int addrlen=sizeof(addr);
addr.sin_family=AF_INET;
addr.sin_port= htons(PORT);
addr.sin_addr.s_addr=htonl(INADDR_ANY);
char buff[BUFF];
FILE *fp;
sockfd= socket(AF_INET,SOCK_DGRAM,0);
if(sockfd<0)
printf("\nFile descriptor not received");
else
printf("\nFile descriptor %d received",sockfd);
while(1){
printf("\nEnter file name : ");
scanf("%s",buff);
sendto(sockfd,buff,BUFF,FLAG,(struct sockaddr*)&addr,addrlen);
printf("\n-----------------Data Received-----------------\n");while(1){
clearBuf(buff);
nbytes=recvfrom(sockfd,buff,BUFF,FLAG,(struct
sockaddr*)&addr,&addrlen);
if(recvFile(buff,BUFF))
break;
}
printf("\n-----------------------------------------------\n");
}
return 0;
}
