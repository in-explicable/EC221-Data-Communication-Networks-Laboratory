#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
        int nf,N;
        int no_tr=0;
        printf("Enter the number of frames:");
        scanf("%d",&nf);
        printf("Enter the window size:");
        scanf("%d",&N);
        int i=1;
        while(i<=nf)
        {
                int x=0;
                for(int j=i; j<i+N && j<=nf; j++)
                {
                        printf("Sent Frame %d\n",j);
                        no_tr++;
                }
                for(int j=i; j<i+N && j<=nf; j++)
                {
                        int flag=rand()%2;
                        if(!flag)
                        {
                        printf("Acknowledgement for Frame %d\n",j);
                        x++;
                        }
                        else
                        {
                        printf("Frame %d",j);
                        printf("Not Received\n");
                        printf("Retransmitting Window");
                        break;
                        }
                }
                printf("\n");
                i+=x;
        }
        printf("Total number of transmissions: %d\n",no_tr);
        return 0;
}
        
                      
