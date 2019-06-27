#ifndef RSA_H
#define RSA_H

#include <stdlib.h>
#include <sys/timeb.h>

#include "bigint.h"



struct _rsa{
    BigInt p;
    BigInt q;
    BigInt e;
    BigInt d;
};

typedef struct _rsa rsa;

class Rsa
{
public:
    Rsa();
    static BigInt randomGenerator(int flag);
    static BigInt randomGenerator(BigInt, BigInt, int);

    static BigInt randomPrimeGenerator(int flag);
    static BigInt publicKeyGenerator(BigInt, BigInt);
    static BigInt privateKeyGenerator(BigInt, BigInt);

    static rsa createRandomRsa(int flag);
    static BigInt encrypt(BigInt, BigInt, BigInt);
    static BigInt decrypt(BigInt, BigInt, BigInt);
    static const int RSA128 = 0;
    static const int RSA256 = 1;
    static const int RSA512 = 2;
    static const int RSA1024 = 3;
    static const int RSA2048 = 4;


private:

    //bool millerRabin(int,int);

    static bool wintess(BigInt, BigInt);
    static bool millerRabin(BigInt, int);
    static BigInt modExp(BigInt, BigInt, BigInt);

    static BigInt gcd(BigInt const &, BigInt const &);
    static BigInt eculid(BigInt, BigInt, BigInt &, BigInt &);
    //static BigInt euclid();


};

#endif // RSA_H

#ifndef _MAGBONE_
#define _MAGBONE_
#endif
