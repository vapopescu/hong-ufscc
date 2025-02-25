#ifndef _RAND_WIN32_H
#define _RAND_WIN32_H

#include <stdlib.h>
#include <math.h>

#define RAND48_SEED_0   (0x330e)
#define RAND48_SEED_1   (0xabcd)
#define RAND48_SEED_2   (0x1234)
#define RAND48_MULT_0   (0xe66d)
#define RAND48_MULT_1   (0xdeec)
#define RAND48_MULT_2   (0x0005)
#define RAND48_ADD      (0x000b)

unsigned static short _rand48_seed[3] = {
    RAND48_SEED_0,
    RAND48_SEED_1,
    RAND48_SEED_2
};
unsigned static short _rand48_mult[3] = {
    RAND48_MULT_0,
    RAND48_MULT_1,
    RAND48_MULT_2
};
unsigned static short _rand48_add = RAND48_ADD;

inline void _dorand48(unsigned short xseed[3])
{
    unsigned long accu;
    unsigned short temp[2];

    accu = (unsigned long)_rand48_mult[0] * (unsigned long)xseed[0] +
        (unsigned long)_rand48_add;
    temp[0] = (unsigned short)accu;        /* lower 16 bits */
    accu >>= sizeof(unsigned short) * 8;
    accu += (unsigned long)_rand48_mult[0] * (unsigned long)xseed[1] +
        (unsigned long)_rand48_mult[1] * (unsigned long)xseed[0];
    temp[1] = (unsigned short)accu;        /* middle 16 bits */
    accu >>= sizeof(unsigned short) * 8;
    accu += _rand48_mult[0] * xseed[2] + _rand48_mult[1] * xseed[1] + _rand48_mult[2] * xseed[0];
    xseed[0] = temp[0];
    xseed[1] = temp[1];
    xseed[2] = (unsigned short)accu;
}

inline double erand48(unsigned short xseed[3])
{
    _dorand48(xseed);
    return ldexp((double)xseed[0], -48) +
        ldexp((double)xseed[1], -32) +
        ldexp((double)xseed[2], -16);
}

inline double drand48(void)
{
    return erand48(_rand48_seed);
}

inline long lrand48(void)
{
    _dorand48(_rand48_seed);
    return ((long)_rand48_seed[2] << 15) + ((long)_rand48_seed[1] >> 1);
}

inline long nrand48(unsigned short xseed[3])
{
    _dorand48(xseed);
    return ((long)xseed[2] << 15) + ((long)xseed[1] >> 1);
}

inline long mrand48(void)
{
    _dorand48(_rand48_seed);
    return ((long)_rand48_seed[2] << 16) + (long)_rand48_seed[1];
}

inline long jrand48(unsigned short xseed[3])
{
    _dorand48(xseed);
    return ((long)xseed[2] << 16) + (long)xseed[1];
}

inline void srand48(long seed)
{
    _rand48_seed[0] = RAND48_SEED_0;
    _rand48_seed[1] = (unsigned short)seed;
    _rand48_seed[2] = (unsigned short)(seed >> 16);
    _rand48_mult[0] = RAND48_MULT_0;
    _rand48_mult[1] = RAND48_MULT_1;
    _rand48_mult[2] = RAND48_MULT_2;
    _rand48_add = RAND48_ADD;
}

inline unsigned short* seed48(unsigned short xseed[3])
{
    static unsigned short sseed[3];

    sseed[0] = _rand48_seed[0];
    sseed[1] = _rand48_seed[1];
    sseed[2] = _rand48_seed[2];
    _rand48_seed[0] = xseed[0];
    _rand48_seed[1] = xseed[1];
    _rand48_seed[2] = xseed[2];
    _rand48_mult[0] = RAND48_MULT_0;
    _rand48_mult[1] = RAND48_MULT_1;
    _rand48_mult[2] = RAND48_MULT_2;
    _rand48_add = RAND48_ADD;
    return sseed;
}

inline void lcong48(unsigned short p[7])
{
    _rand48_seed[0] = p[0];
    _rand48_seed[1] = p[1];
    _rand48_seed[2] = p[2];
    _rand48_mult[0] = p[3];
    _rand48_mult[1] = p[4];
    _rand48_mult[2] = p[5];
    _rand48_add = p[6];
}

#endif // _RAND_WIN32_H