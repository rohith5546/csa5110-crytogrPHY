#include <stdio.h>
#include <stdint.h>

/*
   Simple demonstration of the CBC-MAC construction.

   This is NOT a real cryptographic AES implementation.
   It is only used to demonstrate the mathematical CBC-MAC
   attack described in the question.
*/

// Dummy block cipher for demonstration
uint8_t E(uint8_t x)
{
    // Simple reversible transformation
    return x ^ 0xAA;
}

// CBC-MAC for a one-block message
uint8_t CBC_MAC_1(uint8_t X)
{
    uint8_t IV = 0;

    // T = E(X XOR IV)
    return E(X ^ IV);
}

// CBC-MAC for a two-block message
uint8_t CBC_MAC_2(uint8_t X, uint8_t Y)
{
    uint8_t IV = 0;
    uint8_t C1, C2;

    C1 = E(X ^ IV);
    C2 = E(Y ^ C1);

    return C2;
}

int main()
{
    uint8_t X = 0x35;

    // First obtain the MAC of X
    uint8_t T = CBC_MAC_1(X);

    /*
       Construct:

              X || (X XOR T)

       The attacker knows X and T.
    */

    uint8_t secondBlock = X ^ T;

    // Calculate CBC-MAC of the forged two-block message
    uint8_t forgedMAC = CBC_MAC_2(X, secondBlock);

    printf("Message X       = 0x%02X\n", X);
    printf("MAC T            = 0x%02X\n", T);
    printf("Second block     = X XOR T = 0x%02X\n", secondBlock);

    printf("MAC of X         = 0x%02X\n", T);
    printf("MAC of X||(X^T)  = 0x%02X\n", forgedMAC);

    if (T == forgedMAC)
        printf("\nForgery successful: both MACs are equal.\n");
    else
        printf("\nForgery failed.\n");

    /*
       Mathematical explanation:

       For the one-block message:

            T = E_K(X)

       For the two-block message:

            X || (X XOR T)

       First block:
            C1 = E_K(X) = T

       Second block:
            C2 = E_K((X XOR T) XOR C1)

       Since C1 = T:

            C2 = E_K((X XOR T) XOR T)

            C2 = E_K(X)

            C2 = T

       Therefore:

            MAC(X) = MAC(X || (X XOR T))

       This demonstrates why basic CBC-MAC is unsafe for
       variable-length messages.
    */

    return 0;
}