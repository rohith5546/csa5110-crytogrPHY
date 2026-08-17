#include <stdio.h>

long long mod_pow(long long base, long long exp, long long mod)
{
    long long result = 1;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

int main()
{
    // Small demonstration RSA parameters
    long long p = 61;
    long long q = 53;
    long long n = p * q;

    long long e = 17;
    long long d = 2753;

    char message[] = "HELLO";
    int i;

    printf("Original Message : %s\n", message);

    printf("Encrypted values : ");

    for (i = 0; message[i] != '\0'; i++)
    {
        // Convert A-Z into 0-25
        int m = message[i] - 'A';

        // RSA encryption
        long long c = mod_pow(m, e, n);

        printf("%lld ", c);
    }

    printf("\n");

    /*
       SECURITY NOTE:

       Encrypting each character separately with RSA is NOT secure.

       There are only 26 possible plaintext values:
             A = 0
             B = 1
             ...
             Z = 25

       Therefore an attacker can encrypt all 26 possible values
       using the public key and construct a lookup table.

       This is called a codebook attack.

       Once the attacker receives a ciphertext, he compares it
       with the table and immediately determines the plaintext.
    */

    return 0;
}