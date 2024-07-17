#include <stdio.h>
int i,key;
char msg[100], encode[100], decode[100];
void getDetails(){
	printf("Enter your message : ");
	scanf("%s",msg);
	printf("Enter the key : ");
	scanf("%d",&key);
	key = key%26;
}
char encryptLetter(char letter,int key, int limit){
	if((letter+key) > limit)
		return (letter+key-26);
	return (letter+key);
}
char decryptLetter(char letter,int key, int limit){
	if((letter-key) < limit)
		return (letter - key + 26);
	return (letter-key);
}



int main(){
	getDetails();
	for(i=0;msg[i] != '\0';i++){
		if(msg[i]>= 'a' && msg[i] <= 'z')
			encode[i] = encryptLetter(msg[i],key, 'z');
		else if(msg[i]>= 'A' && msg[i] <= 'Z')
			encode[i] = encryptLetter(msg[i],key, 'Z');
		else
			encode[i] = msg[i];
	}
	printf("Encrypted message : %s",encode);
	for(i=0;encode[i] != '\0';i++){
		if(encode[i]>= 'a' && encode[i] <= 'z')
			decode[i] = decryptLetter(encode[i],key, 'a');
		else if(encode[i]>= 'A' && encode[i] <= 'Z')
			decode[i] = decryptLetter(encode[i],key, 'A');
		else
			decode[i] = encode[i];
	}
	printf("\nDecrypted message : %s\n", decode);
	return 0;
}
