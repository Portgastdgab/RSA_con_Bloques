#include <tuple>
#include <stdlib.h>
#include <time.h>
#include <NTL/mat_ZZ.h>
#include <string>
#include<sstream>

using namespace NTL;
using namespace std;

ZZ mod(ZZ, ZZ);                         //modulo

ZZ modPow(ZZ, ZZ, ZZ);                  //exponenciacion modular

ZZ binaryGCD(ZZ&, ZZ&);                   //MCD binario

void gcdExtended(ZZ, ZZ, ZZ&, ZZ&);     //Algoritmo extendido de Euclides

ZZ inverse(ZZ, ZZ);                     //Inversa

ZZ RandomNumber(ZZ, ZZ);                //Numero aleatorio

bool MillerRabinTest(ZZ, ZZ);           //Test de Miller Rabin (Primalidad)

bool isPrime(ZZ, ZZ);

ZZ RandomPrime(int);

string ZZtoStr(ZZ);

int countBits(ZZ);
