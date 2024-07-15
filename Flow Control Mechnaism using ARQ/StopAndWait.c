#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
void main()
{
        int i=1,j=1,noframes,x,x1=10,x2;
        printf("Enter the number of frames:");
        scanf("%d",&noframes);
        printf("Number of frames is %d\n",noframes);
        while(noframes>0)
        {
        printf("\nSending frame %d \n",i);
        srand(x1++);
        x=rand()%10;
        if(x%2==0) {
                for(x2=1;x2<2;x2++)
                {
                printf("Waiting for %d seconds, No acknowlegement received, so retransmitting frame \n", x2);
                sleep(x2);
                }
                printf("Retransmitting frame %d\n",i);
                srand(x1++);
                x=rand()%10;
                }
                printf("Acknowledgment for frame %d\n",j);
                noframes-=1;
                i++;
                j++;
        }
        printf("\nEnd of stop wait protocol");
}
