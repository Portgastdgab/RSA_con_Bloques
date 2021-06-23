#include <tuple>
#include <stdlib.h>
#include <time.h>
#include <NTL/mat_ZZ.h>
#include <string>
#include<sstream>

using namespace NTL;
using namespace std;

ZZ mod(ZZ, ZZ);

ZZ modPow(ZZ, ZZ, ZZ);

ZZ gcd(ZZ, ZZ);

void gcdExtended(ZZ, ZZ, ZZ&, ZZ&);

ZZ inverse(ZZ, ZZ);

ZZ RandomNumber(ZZ, ZZ);

bool MillerRabinTest(ZZ, ZZ);

bool isPrime(ZZ, ZZ);

ZZ RandomPrime(int);

string ZZtoStr(ZZ);

int countBits(ZZ);
