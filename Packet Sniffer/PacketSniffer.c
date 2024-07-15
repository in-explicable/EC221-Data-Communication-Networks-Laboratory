#include<netinet/in.h>
#include<errno.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/ip_icmp.h>
#include<netinet/udp.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
void ProcessPacket(unsigned char* , int);
FILE *logfile;
struct sockaddr_in source,dest;
int tcp=0,udp=0,icmp=0,others=0,igmp=0,arp=0,ospf=0,total=0,i,j;
int main()
{
int saddr_size , data_size;
struct sockaddr saddr;
unsigned char *buffer = (unsigned char *) malloc(65536);
logfile=fopen("log.txt","w");
if(logfile==NULL)
{
printf("Unable to create log.txt file.");
}
printf("Starting...\n");
int sock_raw = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ;
setsockopt(sock_raw , SOL_SOCKET , SO_BINDTODEVICE , "eth0" , strlen("eth0")+ 1 );
if(sock_raw < 0)
{
//Print the error with proper message
perror("Socket Error");
return 1;
}
while(1)
{
saddr_size = sizeof saddr;
//Receive a packet
data_size = recvfrom(sock_raw , buffer , 65536 , 0 , &saddr , (socklen_t*)&saddr_size);
if(data_size <0 )
{
printf("Recvfrom error , failed to get packets\n");return 1;
}
ProcessPacket(buffer , data_size);
}
close(sock_raw);
printf("Finished");
return 0;
}
/* This function will parse the packet read and identifies the packet type (ICMP, ARP etc
* based on the IP header protocol type */
void ProcessPacket(unsigned char* buffer, int size)
{
//Get the IP Header part of this packet , excluding the ethernet header
struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
++total;
switch (iph->protocol)
/* Check the Protocol type */
{
/* ICMP Protocol */
case 1:
++icmp;
break;
case 2:
++igmp;
break;
case 6:
++tcp;
break;
case 17:
/* UDP packet */
++udp;
break;
case 89:
/* OSPF packet */
++ospf;
break;
default:
++others;
break;
}
printf("TCP : %d UDP : %d ICMP : %d IGMP : %d Others : %d Total : %d\r",tcp, udp, icmp, igmp,
others, total);
}
