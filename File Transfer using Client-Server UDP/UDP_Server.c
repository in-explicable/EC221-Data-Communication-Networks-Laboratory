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
#define FNF "File Not Found"
#define FLAG 0
void clearBuf(char * b){
for(int i=0;i<BUFF;++i)
b[i]='\0';
}
char cipher(char ch){
return ch^KEY;
}
int sendFile(FILE *fp,char *buf, int s){
int i,len;
if(fp==NULL){
strcpy(buf,FNF);
len = strlen(FNF);
buf[len]=EOF;
for(i=0;i<len;++i)
buf[i]=cipher(buf[i]);
return 1;
}
char ch;
for(i=0;i<s;++i){
ch=fgetc(fp);
buf[i]=cipher(ch);
if(buf[i]==EOF)
return 1;
}
return 0;
}
int main(){
int sockfd,nbytes,addrlen;
struct sockaddr_in addr;
addrlen=sizeof(addr);
addr.sin_family=AF_INET;
addr.sin_port= htons(PORT);
addr.sin_addr.s_addr=htonl(INADDR_ANY);
char buff[BUFF];
FILE *fp;
sockfd= socket(AF_INET,SOCK_DGRAM,0);
if(sockfd<0)printf("\nFile descriptor not received");
else
printf("\nFile descriptor %d received",sockfd);
if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr))==0)
printf("\nSuccessfully binded");
else
printf("\nBinding failed");
while(1){
printf("\nWaiting for file name ");
clearBuf(buff);
nbytes=recvfrom(sockfd,buff,BUFF,FLAG,(struct sockaddr*)&addr,&addrlen);
fp=fopen(buff,"r");
printf("\nFile name : %s ",buff);
if(fp==NULL)
printf("\nFile open failed");
else
printf("\nFile opened");
while(1){
if(sendFile(fp,buff,BUFF)){
sendto(sockfd,buff,BUFF,FLAG,(struct sockaddr*)&addr,addrlen);
break;
}
sendto(sockfd,buff,BUFF,FLAG,(struct sockaddr*)&addr,addrlen);
clearBuf(buff);
}
if(fp!=NULL)
fclose(fp);
}
printf("\n");
return 0;
}
