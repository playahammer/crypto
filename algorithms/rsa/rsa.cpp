#include "rsa.h"

Rsa::Rsa()
{

}

rsa Rsa::createRandomRsa(int flag){
    rsa r;
    r.p = randomPrimeGenerator(flag - 1);
    r.q = randomPrimeGenerator(flag - 1);

    r.e =  publicKeyGenerator(r.p, r.q);
    r.d = privateKeyGenerator((r.p - 1) * (r.q - 1), r.e);
    return r;
}
BigInt Rsa::encrypt(BigInt c, BigInt e, BigInt n){
    // c^e mod n
    return modExp(c, e, n);
}

BigInt Rsa::decrypt(BigInt c, BigInt e, BigInt n){
    return modExp(c, e, n);
}

BigInt Rsa::randomPrimeGenerator(int flag){
    BigInt prime;
    prime = randomGenerator(flag);
    do{
       prime += BigInt(2);
       qDebug()<<QString::fromStdString(prime.toString());
    }while (!millerRabin(prime, 5));
    return prime;
}

BigInt Rsa::publicKeyGenerator(BigInt primerP, BigInt primerQ){
    BigInt key;
    BigInt n = primerP * primerQ;
    BigInt fn = (primerP - 1) * (primerQ - 1);
    int flag = *fn.getNumbers().begin() % 2;
    do{
        key = randomGenerator(1, fn, flag);
    }while(gcd(fn, key) != BigInt(1));
    return key;
}



BigInt Rsa::privateKeyGenerator(BigInt fn, BigInt e){
    BigInt a = e;
    BigInt b = fn;
    BigInt x;
    BigInt y;
    //qDebug()<<"x:"<<QString::fromStdString(x.toString());
    BigInt ret = eculid(a, b, x, y);
    return  (x % fn + fn) % fn;
}
/**
 * a^m mod n
 * @brief Rsa::modExp
 * @param a
 * @param m
 * @param n
 * @return
 */
BigInt Rsa::modExp(BigInt a, BigInt m, BigInt n){
    BigInt result(1), z = a;
    while (m > BigInt(0)) {
        while (m.mod2() == 0) {
            z = (z * z) % n;
            m = m.divide2();
        }
        m -= 1;
        result = (result * z) % n;
    }
    return result;
}
bool Rsa::wintess(BigInt a, BigInt n){
    //preprocess

    BigInt primes[25] = {BigInt(2), BigInt(3), BigInt(5), BigInt(7), BigInt(11), BigInt(13), BigInt(17)
                        , BigInt(19), BigInt(23), BigInt(29), BigInt(31), BigInt(37), BigInt(41), BigInt(43),
                        BigInt(47), BigInt(53), BigInt(59), BigInt(61), BigInt(67), BigInt(71), BigInt(73),
                        BigInt(79), BigInt(83), BigInt(89), BigInt(37)};
    for (int i = 0; i < 25; i++) {
        if(n % primes[i] == 0) return true;
    }

    BigInt y = (1), m = n - 1, z = a;
    clock_t t1 = clock();
    while(m > BigInt(0)){
        //qDebug()<<(m % 2 == BigInt(0));

        while(m.mod2() == 0){
            BigInt x = z;
            clock_t t = clock();
            z = (z * z) % n;
            //qDebug()<<"mode_1:"<<clock() - t;
            m = m.divide2();
            if(z == BigInt(1) && x != BigInt(1) && x != n - 1) return true;
        }
        m = m - 1;
        y = (y * z) % n;
    }

    //qDebug()<<"mode_2:"<<clock() - t1;
    if(y == BigInt(1)) return false;
    return true;
}

bool Rsa::millerRabin(BigInt bint, int times = 5){
    for (int i = 0; i < times; i++) {
        BigInt a = randomGenerator(BigInt(0), bint - 1, 0);
        clock_t t = clock();
        if(wintess(a, bint)) { qDebug()<<"wintess:"<<clock() - t; return false;}

    }
    return true;
}
BigInt Rsa::randomGenerator(int flag){
    std::vector<int> randoms;
    BigInt min, max;
    switch(flag){
        case -1:
            min = BigInt("9223372036854775808");
            max = BigInt("18446744073709551616");
            break;
        case 0:
            min = BigInt("170141183460469231731687303715884105728");
            max = BigInt("340282366920938463463374607431768211456");
            break;

        case 1:
            min = BigInt("57896044618658097711785492504343953926634992332820282019728792003956564819968");
            max = BigInt("115792089237316195423570985008687907853269984665640564039457584007913129639936");
            break;

        case 2:
            min = BigInt("703903964971298549787012499102923063739682910296196688861780721860882015036773488400937149083451713845015929093243025426876941405973284973216824503042048");
            max = BigInt("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084096");
            break;
        case 3:
            min = BigInt("89884656743115795386465259539451236680898848947115328636715040578866337902750481566354238661203768010560056939935696678829394884407208311246423715319737062188883946712432742638151109800623047059726541476042502884419075341171231440736956555270413618581675255342293149119973622969239858152417678164812112068608");
            max = BigInt("179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137216");
            break;

    }


    return randomGenerator(min, max, 0);
}

BigInt Rsa::randomGenerator(BigInt min, BigInt max, int flag){
    BigInt s;
    std::vector<int> randoms;

    struct timeb timeSeed;
    ftime(&timeSeed);

    srand(static_cast<unsigned>(timeSeed.time * 1000 + timeSeed.millitm));
    do{
        //detect numbers if odd;
        randoms.clear();
        int lastVe = 0;
        do{
            lastVe = rand() % 1000000000;
        }while(lastVe % 2 == flag);
        randoms.push_back(lastVe);

        for (int i = 1; i < min.getNumbersLength() - 1; i++) {
            randoms.push_back(rand() % 1000000000);
        }
        int headMax = *(max.getNumbers().end() - 1);
        int headMin = min.getNumbersLength() != max.getNumbersLength() ? 0 : *(min.getNumbers().end() - 1);
        randoms.push_back((rand() % (headMax - headMin) + headMin + 1));
        s = BigInt(randoms);
        //qDebug()<<QString::fromStdString(s.toString());
    }while (s >= max || s <= min);

    return s;
}


/**
 * ax+by = gcd(a,b)
 * @brief Rsa::eculid
 * @param a
 * @param b
 * @param x
 * @param y
 * @return
 */

// gcd(a, b) = gcd (b, a % b);
// x2 = y1;
// y2 = y1 - a / b * x1;
BigInt Rsa::eculid(BigInt a, BigInt b, BigInt & x, BigInt &y){
    BigInt ret;
    if(b == BigInt(0)){
        x = BigInt(1);
        y = BigInt(0);
        return a;
    }

    ret  = eculid(b, a % b, y, x);

    y = y - a / b * x;
    return ret;

}
BigInt Rsa::gcd(const BigInt &big,const BigInt &small){
    BigInt b = big, s = small;
    //assert(b >= s);
    if(b == s) return b;
    while (1) {
        BigInt t = b % s;
        if(t == BigInt(0)) break;
        else{
            b = s;
            s = t;
        }
    }
    return s;
}
