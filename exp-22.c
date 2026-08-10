#include <stdio.h>

/* ---------- S-DES ---------- */

int P10[10] = {3,5,2,7,4,10,1,9,8,6};
int P8[8]   = {6,3,7,4,8,5,10,9};
int IP[8]   = {2,6,3,1,4,8,5,7};
int IP_INV[8] = {4,1,3,5,7,2,8,6};
int EP[8] = {4,1,2,3,2,3,4,1};
int P4[4] = {2,4,3,1};

int S0[4][4] = {
    {1,0,3,2},
    {3,2,1,0},
    {0,2,1,3},
    {3,1,3,2}
};

int S1[4][4] = {
    {0,1,2,3},
    {2,0,1,3},
    {3,0,1,0},
    {2,1,0,3}
};

void permute(int *in, int *out, int *p, int n)
{
    for(int i=0;i<n;i++)
        out[i] = in[p[i]-1];
}

void leftShift(int *a, int n)
{
    int temp = a[0];

    for(int i=0;i<n-1;i++)
        a[i] = a[i+1];

    a[n-1] = temp;
}

void generateKeys(int *key, int *k1, int *k2)
{
    int temp[10], ls[10];

    permute(key,temp,P10,10);

    for(int i=0;i<5;i++)
    {
        ls[i] = temp[i];
        ls[i+5] = temp[i+5];
    }

    leftShift(ls,5);
    leftShift(ls+5,5);

    permute(ls,k1,P8,8);

    leftShift(ls,5);
    leftShift(ls+5,5);

    permute(ls,k2,P8,8);
}

void fk(int *bits,int *key)
{
    int ep[8], x[8], p4[4];
    int left[4], right[4];

    for(int i=0;i<4;i++)
    {
        left[i]=bits[i];
        right[i]=bits[i+4];
    }

    permute(right,ep,EP,8);

    for(int i=0;i<8;i++)
        x[i]=ep[i]^key[i];

    int r1=(x[0]*2+x[3]);
    int c1=(x[1]*2+x[2]);

    int r2=(x[4]*2+x[7]);
    int c2=(x[5]*2+x[6]);

    int value0=S0[r1][c1];
    int value1=S1[r2][c2];

    int s[4]={
        (value0>>1)&1,
        value0&1,
        (value1>>1)&1,
        value1&1
    };

    permute(s,p4,P4,4);

    for(int i=0;i<4;i++)
        bits[i]^=p4[i];
}

void sdesEncrypt(int *plain,int *cipher,int *k1,int *k2)
{
    int temp[8];

    permute(plain,temp,IP,8);

    fk(temp,k1);

    int t;
    for(int i=0;i<4;i++)
    {
        t=temp[i];
        temp[i]=temp[i+4];
        temp[i+4]=t;
    }

    fk(temp,k2);

    permute(temp,cipher,IP_INV,8);
}

void sdesDecrypt(int *cipher,int *plain,int *k1,int *k2)
{
    int temp[8];

    permute(cipher,temp,IP,8);

    fk(temp,k2);

    int t;
    for(int i=0;i<4;i++)
    {
        t=temp[i];
        temp[i]=temp[i+4];
        temp[i+4]=t;
    }

    fk(temp,k1);

    permute(temp,plain,IP_INV,8);
}

void printBits(int *a,int n)
{
    for(int i=0;i<n;i++)
        printf("%d",a[i]);

    printf("\n");
}

int main()
{
    int key[10] =
        {0,1,1,1,1,1,1,1,0,1};

    int iv[8] =
        {1,0,1,0,1,0,1,0};

    int plaintext[16] =
        {0,0,0,0,0,0,0,1,
         0,0,1,0,0,0,1,1};

    int k1[8],k2[8];

    int c1[8],c2[8];
    int temp[8];
    int decrypted[16];

    generateKeys(key,k1,k2);

    /* CBC Encryption - Block 1 */
    for(int i=0;i<8;i++)
        temp[i]=plaintext[i]^iv[i];

    sdesEncrypt(temp,c1,k1,k2);

    /* CBC Encryption - Block 2 */
    for(int i=0;i<8;i++)
        temp[i]=plaintext[i+8]^c1[i];

    sdesEncrypt(temp,c2,k1,k2);

    printf("Ciphertext: ");
    printBits(c1,8);
    printBits(c2,8);

    /* CBC Decryption - Block 1 */
    sdesDecrypt(c1,temp,k1,k2);

    for(int i=0;i<8;i++)
        decrypted[i]=temp[i]^iv[i];

    /* CBC Decryption - Block 2 */
    sdesDecrypt(c2,temp,k1,k2);

    for(int i=0;i<8;i++)
        decrypted[i+8]=temp[i]^c1[i];

    printf("Decrypted:  ");
    printBits(decrypted,16);

    return 0;
}