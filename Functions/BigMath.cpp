#include "BigMath.h"

ZZ mod(ZZ a, ZZ n){
    ZZ r = a-n*(a/n);
    r = r+(r<0)*n;
    return r;
}

ZZ modPow(ZZ a, ZZ n, ZZ m) {

    ZZ exp(1);
    ZZ x = mod(a, m);

    while (n > 0) {
        if (mod(n, ZZ(2)) == 1)
            exp = mod(exp * x, m);

        x = mod(x * x, m);
        n /= 2;
    }

    return exp;
}

ZZ gcd_bin(ZZ &u,ZZ &v){
    ZZ t, g, a, b;
    g=1;
    a=abs(u);
    b=abs(v);
    while(a%2==0 && b%2==0){
        a=a/2;
        b=b/2;
        g=2*g;
    }
    while(a!=0){
        if(a%2==0){
            a=a/2;
        }else if(b%2==0){
            b=b/2;
        }else{
            t=abs(a-b)/2;
            if(a>= b){
                a=t;
            }else{
                b=t;
            }
        }
    }
    return g*b;
}

void gcdExtended(ZZ a, ZZ b, ZZ &x, ZZ &y) {
    x = ZZ(1), y = ZZ(0);

    ZZ x1(0), y1(1), a1(a), b1(b);
    while (b1 != 0) {
        ZZ q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
}

ZZ inverse(ZZ a, ZZ n) {
    if (gcd_bin(a, n) == 1) {
        ZZ x, y;
        gcdExtended(a, n, x, y);
        return mod(x, n);
    }
    cout << "falla";
    return ZZ(-1);
}

ZZ RandomNumber(ZZ init, ZZ end) {
    ZZ k = end - init + 1;
    ZZ num = RandomBnd(k) + init;
    return num;
}

bool MillerRabinTest(ZZ d, ZZ n) {

    // obtener un numero random en [2..n-2]
    ZZ a = RandomNumber(ZZ(2), n - 2);

    // X =  a^d mod( n)
    ZZ x = modPow(a, d, n);

    if (x == 1 || x == n - 1)
        return true;


    while (d != n - 1) {
        x = mod(x * x, n);
        //x= x*x % n;
        d *= 2;

        if (x == 1) return false;
        if (x == n - 1) return true;
    }

    return false;
}

bool isPrime(ZZ number, ZZ iter) {
    // Casos Base
    if (mod(number, ZZ(2)) == 0) return false;
    if (number <= 1 || number == 4) return false;
    if (number <= 3) return true;

    // number-1 = 2^d * r ; r >= 1
    ZZ d = number - 1;

    //Hallar  el exponente d
    while (mod(d, ZZ(2)) == 0)
        d /= 2;


    // Iterar
    for (ZZ i(0); i < iter; i++)
        if (!MillerRabinTest(d, number))
            return false;

    return true;
}

ZZ RandomPrime(int bits) {
    ZZ num;
    do {
        num = RandomLen_ZZ(bits);
        //cout<<"\nRandom Number: "<<num<<"\n\n";

    } while (!(isPrime(num, ZZ(5))));

    return num;
}


string ZZtoStr(ZZ a) {
    stringstream temp;
    temp << a;
    return temp.str();
}

int countBits(ZZ number) {
    unsigned int count = 0;
    while (number != 0) {
        count++;
        number >>= 1;
    }
    return count;
}