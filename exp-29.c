#include <stdio.h>

#define STATE_LANES 25
#define RATE_BITS 1024
#define LANE_BITS 64

int main()
{
    int rate_lanes;
    int capacity_lanes;
    int i;

    /*
       SHA-3/Keccak uses a 1600-bit internal state.

       1600 / 64 = 25 lanes.

       For a 1024-bit block:

       Rate     = 1024 bits
       Capacity = 1600 - 1024 = 576 bits

       Number of rate lanes:
             1024 / 64 = 16

       Number of capacity lanes:
             576 / 64 = 9
    */

    rate_lanes = RATE_BITS / LANE_BITS;
    capacity_lanes = STATE_LANES - rate_lanes;

    printf("SHA-3 / Keccak State : 1600 bits\n");
    printf("Block (Rate)         : %d bits\n", RATE_BITS);
    printf("Rate lanes            : %d\n", rate_lanes);
    printf("Capacity              : %d bits\n", 1600 - RATE_BITS);
    printf("Capacity lanes        : %d\n", capacity_lanes);

    /*
       Initially all capacity lanes are zero.

       During absorbing, the message block is XORed only
       into the RATE portion of the state.

       Therefore, without applying the Keccak permutation,
       the capacity lanes remain zero.

       The question explicitly says to IGNORE the permutation.

       Consequently, the zero capacity lanes can NEVER
       become nonzero.
    */

    printf("\nInitial capacity lanes:\n");

    for (i = 0; i < capacity_lanes; i++)
        printf("Lane %d = 0\n", i);

    printf("\nWithout permutation, capacity lanes remain zero.\n");
    printf("Time required for all capacity lanes to become nonzero: INFINITE.\n");

    return 0;
}