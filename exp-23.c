#include <stdio.h>

/*
   CTR mode demonstration using S-DES.

   The S-DES functions are the same as in Question 22.
   For each block:

       C = P XOR S-DES(Key, Counter)

   Counter is increased after every block.
*/

int P10[10]={3,5,2,7,4,10,1,9,8,6};
int P8[8]={6,3,7,4,8,5,10,9};
int IP[8]={2,6,3,1,4,8,5,7};
int IP_INV[8]={4,1,3,5,7,2,8,6};
int EP[8]={4,1,2,3,2,3,4,1};
int P4[4]={2,4,3,1};

int S0[4][4]={
    {1,0,3,2},
    {3,2,1,0},
    {0,2,1,3},
    {3,1,3,2}
};

int S1[4][4]={
    {0,1,2,3},
    {2,0,1,3},
    {3,0,1,0},
    {2,1,0,3}
};

void permute(int *in,int *out,int *p,int n)
{
    for(int i=0;i<n;i++)
        out[i]=in[p[i]-1];
}

void leftShift(int *a,int n)
{
    int t=a[0];

    for(int i=0;i<n-1;i++)
        a[i]=a[i+1];

    a[n-1]=t;
}

void generateKeys(int *key,int *k1,int *k2)
{
    int t[10];

    permute(key,t,P10,10);

    leftShift(t,5);
    leftShift(t+5,5);

    permute(t,k1,P8,8);

    leftShift(t,5);
    leftShift(t+5,5);

    permute(t,k2,P8,8);
}

void fk(int *b,int *key)
{
    int ep[8],x[8],p4[4];

    permute(b+4,ep,EP,8);

    for(int i=0;i<8;i++)
        x[i]=ep[i]^key[i];

    int r1=x[0]*2+x[3];
    int c1=x[1]*2+x[2];

    int r2=x[4]*2+x[7];
    int c2=x[5]*2+x[6];

    int a=S0[r1][c1];
    int d=S1[r2][c2];

    int s[4]={
        (a>>1)&1,
        a&1,
        (d>>1)&1,
        d&1
    };

    permute(s,p4,P4,4);

    for(int i=0;i<4;i++)
        b[i]^=p4[i];
}

void encrypt(int *p,int *c,int *k1,int *k2)
{
    int t[8];

    permute(p,t,IP,8);

    fk(t,k1);

    for(int i=0;i<4;i++)
    {
        int x=t[i];
        t[i]=t[i+4];
        t[i+4]=x;
    }

    fk(t,k2);

    permute(t,c,IP_INV,8);
}

void printBits(int *a,int n)
{
    for(int i=0;i<n;i++)
        printf("%d",a[i]);

    printf("\n");
}

void incrementCounter(int *counter)
{
    for(int i=7;i>=0;i--)
    {
        if(counter[i]==0)
        {
            counter[i]=1;
            break;
        }

        counter[i]=0;
    }
}

int main()
{
    int key[10]=
        {0,1,1,1,1,1,1,1,0,1};

    int counter[8]=
        {0,0,0,0,0,0,0,0};

    int plaintext[24]=
        {0,0,0,0,0,0,0,1,
         0,0,0,0,0,0,1,0,
         0,0,0,0,0,1,0,0};

    int ciphertext[24];
    int decrypted[24];

    int k1[8],k2[8];
    int stream[8];

    generateKeys(key,k1,k2);

    /* Encryption */
    for(int block=0;block<3;block++)
    {
        encrypt(counter,stream,k1,k2);

        for(int i=0;i<8;i++)
            ciphertext[block*8+i] =
                plaintext[block*8+i]^stream[i];

        incrementCounter(counter);
    }

    printf("Ciphertext: ");
    printBits(ciphertext,24);

    /* Reset counter for decryption */
    for(int i=0;i<8;i++)
        counter[i]=0;

    /* Decryption */
    for(int block=0;block<3;block++)
    {
        encrypt(counter,stream,k1,k2);

        for(int i=0;i<8;i++)
            decrypted[block*8+i] =
                ciphertext[block*8+i]^stream[i];

        incrementCounter(counter);
    }

    printf("Decrypted:  ");
    printBits(decrypted,24);

    return 0;
}