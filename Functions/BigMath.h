#include <tuple>
#include <stdlib.h>
#include <time.h>
#include <NTL/mat_ZZ.h>
#include <string>
#include <sstream>
#include <chrono>

using namespace NTL;
using namespace std;

string toBinary(ZZ);

string ZZtoStr(ZZ);

int countBits(ZZ);

ZZ mod(ZZ, ZZ);                         //modulo

ZZ getSystemTime();                     //SystemTime

ZZ seed(int);                           //Seed

class Trivium {

private:
    int s[288];
    int IV[80], key[80];
    int t1, t2, t3;
    ZZ base10;

    void generate_Key_and_IV();

    void rotate();

    void init();

    void keyStream(int);

    int count_Bits(ZZ);

public:

    Trivium();

    ZZ RandomBits(int);

    ZZ RandomRange(ZZ, ZZ);
};

ZZ modPow(ZZ, ZZ, ZZ);                  //exponenciacion modular

ZZ binaryGCD(ZZ , ZZ );                   //MCD binario

bool check(ZZ, ZZ);

void gcdExtended(ZZ, ZZ, ZZ &, ZZ &);     //Algoritmo extendido de Euclides

ZZ inverse(ZZ, ZZ);                     //Inversa

ZZ modPow_TRC(ZZ, ZZ, ZZ, ZZ, ZZ);

ZZ RandomNumber(ZZ, ZZ);                //Numero aleatorio

bool MillerRabinTest(ZZ, ZZ);           //Test de Miller Rabin (Primalidad)

bool isPrime(ZZ, ZZ);

ZZ RandomPrime(int);

void blocks(ZZ, string &, int, int);

