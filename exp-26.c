#include <stdio.h>

// Function to calculate (base^exp) mod mod
long long mod_pow(long long base, long long exp, long long mod)
{
    long long result = 1;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp = exp / 2;
    }

    return result;
}

int main()
{
    long long p = 61;
    long long q = 53;

    // Calculate modulus
    long long n = p * q;

    // Euler's totient
    long long phi = (p - 1) * (q - 1);

    // Original public and private keys
    long long e = 17;
    long long d = 2753;

    int message = 65;

    // Encryption: C = M^e mod n
    long long cipher = mod_pow(message, e, n);

    // Decryption: M = C^d mod n
    long long decrypted = mod_pow(cipher, d, n);

    printf("Original Message : %d\n", message);
    printf("Public Key       : (%lld, %lld)\n", e, n);
    printf("Private Key      : (%lld, %lld)\n", d, n);
    printf("Encrypted        : %lld\n", cipher);
    printf("Decrypted        : %lld\n", decrypted);

    /*
       Suppose Bob's private key d is leaked.

       Bob cannot make the old RSA modulus n safe simply by
       generating a new public/private exponent pair (e,d)
       while keeping the same n.

       The factorization of n is still the same. If an attacker
       has learned d, they may be able to derive information
       about phi(n) and factor n.

       Therefore, Bob should generate a completely new RSA key
       pair, including a new modulus n.
    */

    return 0;
}