#include <stdio.h>

int gcd(int a, int b)
{
    while(b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

int main()
{
    int n, e, m;
    int factor;

    printf("Enter RSA modulus n: ");
    scanf("%d", &n);

    printf("Enter public key e: ");
    scanf("%d", &e);

    printf("Enter plaintext block m: ");
    scanf("%d", &m);

    factor = gcd(m, n);

    printf("\ngcd(m,n) = %d\n", factor);

    if(factor > 1 && factor < n)
    {
        int p = factor;
        int q = n / p;

        int phi = (p - 1) * (q - 1);

        int d;

        for(d = 1; d < phi; d++)
        {
            if((e * d) % phi == 1)
                break;
        }

        printf("RSA is compromised!\n");
        printf("p = %d\n", p);
        printf("q = %d\n", q);
        printf("phi(n) = %d\n", phi);
        printf("Private key d = %d\n", d);
    }
    else
    {
        printf("No useful common factor found.\n");
    }

    return 0;
}