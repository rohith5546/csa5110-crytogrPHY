#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8

void printBlock(unsigned char *b)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
        printf("%02X ", b[i]);
    printf("\n");
}

/* Simple XOR-based demonstration cipher */
void encryptBlock(unsigned char *in, unsigned char *out,
                  unsigned char *key)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
        out[i] = in[i] ^ key[i];
}

void decryptBlock(unsigned char *in, unsigned char *out,
                  unsigned char *key)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
        out[i] = in[i] ^ key[i];
}

/* ECB Mode */
void ECB(unsigned char *plain, unsigned char *cipher,
         unsigned char *key, int blocks)
{
    for (int i = 0; i < blocks; i++)
        encryptBlock(&plain[i * BLOCK_SIZE],
                     &cipher[i * BLOCK_SIZE], key);
}

/* CBC Mode */
void CBC(unsigned char *plain, unsigned char *cipher,
         unsigned char *key, unsigned char *iv, int blocks)
{
    unsigned char temp[BLOCK_SIZE];

    for (int b = 0; b < blocks; b++)
    {
        for (int i = 0; i < BLOCK_SIZE; i++)
            temp[i] = plain[b * BLOCK_SIZE + i] ^ iv[i];

        encryptBlock(temp, &cipher[b * BLOCK_SIZE], key);

        for (int i = 0; i < BLOCK_SIZE; i++)
            iv[i] = cipher[b * BLOCK_SIZE + i];
    }
}

/* CFB Mode */
void CFB(unsigned char *plain, unsigned char *cipher,
         unsigned char *key, unsigned char *iv, int blocks)
{
    unsigned char temp[BLOCK_SIZE];

    for (int b = 0; b < blocks; b++)
    {
        encryptBlock(iv, temp, key);

        for (int i = 0; i < BLOCK_SIZE; i++)
            cipher[b * BLOCK_SIZE + i] =
                plain[b * BLOCK_SIZE + i] ^ temp[i];

        for (int i = 0; i < BLOCK_SIZE; i++)
            iv[i] = cipher[b * BLOCK_SIZE + i];
    }
}

int main()
{
    unsigned char plaintext[16] =
        "HELLOWORLD12345";

    unsigned char key[BLOCK_SIZE] =
        "12345678";

    unsigned char iv[BLOCK_SIZE] =
        "ABCDEFGH";

    unsigned char cipher[16];

    int blocks = 2;

    printf("Plaintext: %s\n\n", plaintext);

    printf("ECB Mode:\n");
    ECB(plaintext, cipher, key, blocks);
    printBlock(cipher);

    printf("\nCBC Mode:\n");
    unsigned char iv1[BLOCK_SIZE] = "ABCDEFGH";
    CBC(plaintext, cipher, key, iv1, blocks);
    printBlock(cipher);

    printf("\nCFB Mode:\n");
    unsigned char iv2[BLOCK_SIZE] = "ABCDEFGH";
    CFB(plaintext, cipher, key, iv2, blocks);
    printBlock(cipher);

    return 0;
}