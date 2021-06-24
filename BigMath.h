//
// Created by misash
//

#ifndef RSA_BIGMATH_H
#define RSA_BIGMATH_H


#include <tuple>
#include <stdlib.h>
#include <time.h>
#include <NTL/mat_ZZ.h>
#include <string>
#include <sstream>





using namespace NTL;
using namespace std;



/* TOOLS */

string toBinary(ZZ n)
{
    string r;
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
    return r;
}

string ZZtoStr(ZZ a){
    stringstream temp;
    temp<<a;
    return temp.str();
}

int countBits(ZZ number)
{
    unsigned int count = 0;
    while (number != 0)
    {
        count++;
        number >>= 1;
    }
    return count;
}




/* END TOOLS*/





/*-----------ALGORITHMS--------------------*/



ZZ mod(ZZ a, ZZ n){
    ZZ r = a-n*(a/n);
    r = r+(r<0)*n;
    return r;
}

ZZ binaryGCD(ZZ u,ZZ v){
    ZZ t, g, a, b;
    g=1;
    a=abs(u);
    b=abs(v);
    while((a&1)==0 && (b&1)==0){
        a>>=1;
        b>>=1;
        g<<=1;
    }
    while(a!=0){
        if((a&1)==0){
            a>>=1;
        }else if((b&1)==0){
            b>>=1;
        }else{
            t=abs(a-b)>>1;
            if(a>= b){
                a=t;
            }else{
                b=t;
            }
        }
    }
    return g*b;
}


ZZ modPow(ZZ a, ZZ e, ZZ n){
    ZZ A(1);
    string bin = toBinary(e);
    for (int i = bin.size(); i != -1; i--){
        A = mod(A * A, n);
        if(bin[i] == '1'){
            A = mod(A * a, n);
        }
    }
    return A;
}


void gcdExtended(ZZ a, ZZ b, ZZ& x, ZZ& y) {
    x = ZZ(1), y = ZZ(0);

    ZZ x1(0), y1(1), a1(a), b1(b);
    while (b1 != 0) {
        ZZ q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
}

ZZ inverse(ZZ a,ZZ n){
    ZZ x,y;
    gcdExtended(a,n,x,y);
    return mod(x,n);
}


class Trivium{

private:
    int s[288];
    int IV[80],key[80];
    int t1,t2,t3;
    ZZ base10;

    void generate_Key_and_IV(){
        for(int i=0;i<80;i++){
            ZZ ran(rand());
            IV[i]=to_int(mod(ran,ZZ(2)));
            key[i]=to_int(mod(ran,ZZ(2)));
        }
    }

    void rotate(){
        for(int j=93;j>=1;--j)
            s[j]=s[j-1];
        for(int j=177;j>=94;--j)
            s[j]=s[j-1];
        for(int j=288;j>=178;--j)
            s[j]=s[j-1];
        s[0]=t3;  s[93]=t1;  s[177]=t2;
    }


    void init(){
        generate_Key_and_IV();

        for(int i=0;i<288;i++) s[i]= 0;

        for(int i=0;i<80;++i){
            s[i]=key[i];
            s[i+93]=IV[i];
        }
        for(int i=285;i<288;++i) s[i]=1;

        //rotate
        for(int i=1;i<1152;i++){
            t1 = ((s[65] ^ (s[90] & s[91]) )^ s[92] )^ s[170];
            t2 = ((s[161] ^ (s[174] & s[175]) )^ s[176] )^ s[263];
            t3 = ((s[242] ^ (s[285] & s[286]) )^ s[287] )^ s[68];
            rotate();
        }
    }
    void keyStream(int N){
        ZZ z(0);
        base10 =0;
        for(int i=0;i<N;i++){

            t1 = s[65] ^ s[92];
            t2 = s[161] ^ s[176];
            t3 = s[242] ^ s[287];

            z = t1 ^ t2 ^ t3;

            t1 ^= s[90] ^ s[91] & s[170] ;
            t2 ^= s[174] ^ s[175] & s[263] ;
            t3 ^= s[285] ^ s[286] & s[68] ;
            rotate();
            base10 += z<<i;
        }
    }

    int count_Bits(ZZ number)
    {
        unsigned int count = 0;
        while (number != 0)
        {
            count++;
            number >>= 1;
        }
        return count;
    }

public:

    Trivium(){
        init();
    }

    ZZ RandomBits(int bits){
        do{
            keyStream(bits);
        }while(count_Bits(base10)!=bits);

        return base10;
    }

    ZZ RandomRange(ZZ init,ZZ end){
        int bits = count_Bits(end);
        do{
            keyStream(bits);
        }while(!(base10>=init && base10<=end));

        return base10;
    }
};


ZZ RandomNumber(ZZ init,ZZ end) {
    ZZ k = end - init + 1;
    ZZ num = RandomBnd(k)+init;
    return num;
}


bool MillerRabinTest(ZZ d, ZZ n)
{
    Trivium gen;


    // obtener un numero random en [2..n-2]
    ZZ a = gen.RandomRange(ZZ(2),n-2);

    // X =  a^d mod( n)
    ZZ x = modPow(a, d, n);

    if (x == 1  || x == n-1)
        return true;

    while (d != n-1)
    {
        x= mod(x*x,n);
        //x= x*x % n;
        d *= 2;

        if (x == 1)      return false;
        if (x == n-1)    return true;
    }

    return false;
}


bool isPrime(ZZ number, ZZ iter)
{
    // Casos Base
    if(mod(number,ZZ(2))== 0) return false;
    if (number <= 1 || number == 4)  return false;
    if (number <= 3) return true;

    // number-1 = 2^d * r ; r >= 1
    ZZ d = number - 1;

    //Hallar  el exponente d
    while (mod(d,ZZ(2)) == 0)
        d /= 2;

    // Iterar
    for (ZZ i (0); i < iter; i++)
        if (!MillerRabinTest(d, number))
            return false;

    return true;
}


ZZ RandomPrime(int bits){
    Trivium x;
    ZZ num;
    do{
        num= x.RandomBits(bits);
    }while(!(isPrime(num,ZZ(5))));

    return num;
}




#endif //RSA_BIGMATH_H
