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
    // Public values
    long long a = 5;
    long long q = 23;

    // Private secret numbers
    long long x = 6;   // Alice's secret
    long long y = 15;  // Bob's secret

    // Alice sends A = a^x mod q
    long long A = mod_pow(a, x, q);

    // Bob sends B = a^y mod q
    long long B = mod_pow(a, y, q);

    // Alice calculates the shared key
    long long keyAlice = mod_pow(B, x, q);

    // Bob calculates the shared key
    long long keyBob = mod_pow(A, y, q);

    printf("Public base (a) : %lld\n", a);
    printf("Public modulus  : %lld\n", q);

    printf("Alice secret x  : %lld\n", x);
    printf("Bob secret y    : %lld\n", y);

    printf("Alice sends     : %lld\n", A);
    printf("Bob sends       : %lld\n", B);

    printf("Alice's key     : %lld\n", keyAlice);
    printf("Bob's key       : %lld\n", keyBob);

    if (keyAlice == keyBob)
        printf("Shared key successfully established.\n");
    else
        printf("Key exchange failed.\n");

    /*
       Correct Diffie-Hellman:

       Alice sends a^x mod q
       Bob sends a^y mod q

       Both obtain:

       a^(xy) mod q

       If they instead send x^a and y^a, the normal
       Diffie-Hellman property does not hold.

       An attacker can intercept x^a and y^a and may be able
       to derive information without solving the intended
       discrete logarithm problem.

       Therefore x^a is NOT a replacement for a^x.
    */

    return 0;
}