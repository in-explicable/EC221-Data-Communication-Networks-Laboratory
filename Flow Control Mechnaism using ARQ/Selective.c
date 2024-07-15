#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
        int n,N,nt=0;
        printf("Enter no of frames:");
        scanf("%d",&n);
        printf("Enter the window size:");
        scanf("%d",&N);
        int i=1;
        while(i<=n)
        {
                int x=0;
                for(int j=i;j<i+N&&j<=n;j++)
                {
                        printf("Sent Frame: %d",j);
                        nt++;
                }
                for(int j=i;j<i+N&&j<=n;j++)
                {
                        int f=rand()%2;
                        if(!f)
                        {
                                printf("\nAcknowledgement for frame %d",j);
                                x++;
                        }
                        else
                        {
                                printf("\nFrame %d",j);
                                printf("\tNot Received\n");
                                printf("Retransmitting Frame: %d",j);
                                j--;
                                nt++;
                        }
                }
                printf("\n");
                i+=x;
        }
        printf("Total number of transmissions: %d\n",nt);
}
