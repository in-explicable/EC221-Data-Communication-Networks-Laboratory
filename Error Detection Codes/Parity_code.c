#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

char data[20], rdata[20];
int datalen;
int check(char data[20]);

int main() {
	int i, count=0, tflag, rflag, test;
	printf("Enter the total bits of data:");
	scanf("%d", &datalen);
	printf("Enter the data:");
	scanf("%s", data);
	tflag = check(data);
	printf("Received data:\n");
	strcpy(rdata,data);
	for(i=0;i<datalen;i++)
		printf("%c",rdata[i]);
	srand(time(NULL));
	test = rand()%2;
	printf("rand=%d\n",test);
	rdata[0] = (test>0.5)?'1':'0';
	printf("Received data after replacing with rand");
	for(i=0;i<datalen;i++)
		printf("%c",rdata[i]);
	rflag = check(rdata);
	if (tflag==rflag)
		printf("\nSuccess!! The received message has no error");
	else
		printf("\nFailure!! The received message has some error in it");
	return 0;
}

int check(char data[20]) {
	int i, evenpar, oddpar, count=0;
	for(i=0;i<datalen;i++) {
		if(data[i]=='1')
		count++;
	}
	printf("\nCount:%d\n",count);
	if(count%2) {
		evenpar=1; oddpar=0;
	}
	else {
		evenpar=0; oddpar=1;
	}
	printf("Even parity = %d, Odd parity = %d", evenpar, oddpar);
	return evenpar;
}

