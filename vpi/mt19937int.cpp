export module mt19937int;

export {
    /*
     * Context structure for PRNG in mt19937int.c
     */
    struct context_s {
        int		mti;		/* the array for the state vector */
        unsigned long	mt[1023];	/* mti==N+1 means mt[N] is not init */
    };

    void sgenrand(struct context_s* context, unsigned long seed);

    unsigned long genrand(struct context_s* context);
}

module :private;

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0df   /* constant vector a */
#define UPPER_MASK 0x80000000 /* most significant w-r bits */
#define LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y)  (y >> 11)
#define TEMPERING_SHIFT_S(y)  (y << 7)
#define TEMPERING_SHIFT_T(y)  (y << 15)
#define TEMPERING_SHIFT_L(y)  (y >> 18)

/* initializing the array with a NONZERO seed */
void
sgenrand(struct context_s* context, unsigned long seed)
{
    unsigned long* mt = context->mt;
    int mti;

    /* setting initial seeds to mt[N] using         */
    /* the generator Line 25 of Table 1 in          */
    /* [KNUTH 1981, The Art of Computer Programming */
    /*    Vol. 2 (2nd Ed.), pp102]                  */
    mt[0] = seed & 0xffffffff;
    for (mti = 1; mti < N; mti++)
        mt[mti] = (69069 * mt[mti - 1]) & 0xffffffff;

    context->mti = mti;
}

unsigned long
genrand(struct context_s* context)
{
    unsigned long y;

    unsigned long* mt = context->mt;
    int mti = context->mti;

    if (mti >= N) { /* generate N words at one time */
        /* mag01[x] = x * MATRIX_A  for x=0,1 */
        static const unsigned long mag01[2] = { 0x0, MATRIX_A };
        int kk;

        if (mti == N + 1)   /* if sgenrand() has not been called, */
            sgenrand(context, 4357); /* a default initial seed is used   */

        for (kk = 0; kk < N - M; kk++) {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        for (; kk < N - 1; kk++) {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1];

        mti = 0;
    }

    y = mt[mti++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);

    context->mti = mti;

    return y;
}
