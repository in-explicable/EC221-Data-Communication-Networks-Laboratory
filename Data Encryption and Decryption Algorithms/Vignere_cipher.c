#include<stdio.h>
#include<string.h>
int main()
{
        char msg[100],key[100];
        int i,j;
        printf("Enter the message:");
        scanf("%s",msg);
        printf("Enter the key:");
        scanf("%s",key);
        int msglen=strlen(msg), keylen=strlen(key);
        char newkey[msglen],encryptedmsg[msglen],decryptedmsg[msglen];
        for(i=0,j=0;i<msglen;++i,++j) {
                if(j==keylen)
                j=0;
                newkey[i]=key[j];
        }
        newkey[i]='\0';
        for(i=0;i<msglen;++i) {
        encryptedmsg[i]=((msg[i]+newkey[i])%26)+'A';
        }
        encryptedmsg[i]='\0';
        for(i=0;i<msglen;++i) {
        decryptedmsg[i]=((encryptedmsg[i]-newkey[i]+26)%26)+'A';
        }
        decryptedmsg[i]='\0';
        printf("Original message: %s",msg);
        printf("\nKey: %s",key);
        printf("\nNewly Generated Key: %s",newkey);
        printf("\nEncrypted message: %s",encryptedmsg);
        printf("\nDecrypted message: %s",decryptedmsg);
        return 0;
}

