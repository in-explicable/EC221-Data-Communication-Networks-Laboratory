#include<stdio.h>
#include<stdlib.h>
struct  packet
{
int time;
int size;
} p[50];

int main() {
        int i,n,m,k=0;
        int bsize,bfilled,outrate;
        printf("Enter the number of packets:");
        scanf("%d",&n);
        printf("Enter packets in the order of their arrival time\n");
        for(i=0;i<n;i++) {
                printf("Enter the time and size:");
                scanf("%d%d",&p[i].time,&p[i].size);
        }
        printf("Enter the bucket size:");
        scanf("%d",&bsize);
        printf("Enter the output rate:");
        scanf("%d",&outrate);
        m=p[n-1].time;
        i=1;
        k=0;
        bfilled=0;
        while(i<=m || bfilled!=0)
        {
                printf("\n\nAt time %d", i);
                if(p[k].time==i) {
                        if(bsize>=bfilled+p[k].size)
                        {
                        bfilled=bfilled+p[k].size;
                        printf("\n%d byte packet is inserted", p[k].size);
                        k=k+1;
                        }
                        else
                        {
                        printf("\n%d byte packet is discarded", p[k].size);
                        k=k+1;
                        }
                }
                if(bfilled==0)
                {
                        printf("\nNo packets to be transmitted");
                }
                else if(bfilled>outrate)
                {
                        bfilled=bfilled-outrate;
                        printf("\n%d byte transferred", outrate);
                }
                else
                {
                        printf("\n%d byte transferred", bfilled);
                        bfilled=0;
                }
                printf("\nPackets in the bucket %d byte", bfilled);
                i++;
       }
       return 0;
}
