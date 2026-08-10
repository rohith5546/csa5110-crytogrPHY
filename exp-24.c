#include <stdio.h>

int main()
{
    int e = 31;
    int n = 3599;

    int p, q;
    int phi;
    int d;

    /* Find p and q */
    for(p = 2; p <= n; p++)
    {
        if(n % p == 0)
        {
            q = n / p;
            break;
        }
    }

    phi = (p - 1) * (q - 1);

    /* Find d */
    for(d = 1; d < phi; d++)
    {
        if((e * d) % phi == 1)
            break;
    }

    printf("p = %d\n", p);
    printf("q = %d\n", q);
    printf("n = %d\n", n);
    printf("phi(n) = %d\n", phi);
    printf("Public key  = (%d, %d)\n", e, n);
    printf("Private key = (%d, %d)\n", d, n);

    return 0;
}