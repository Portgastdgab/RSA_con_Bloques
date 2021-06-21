#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <cmath>

using namespace std;

int module(int, int );
int recursive_Euclid(int, int );
int Euclid(int, int );
int mcd(int, int);
int Euclid_extended(int, int );
int inverse(int, int );
int modular_exponentiation(int, int, int );
int random(int begin = 0, int ind = 100);
vector<int> criba_eratostenes(int);
vector <int> prime_bits(int);

//para RSA con bloques
string add_zeros(string, int);
void division_to_string(vector <string> &, string, int);
void division_to_int(vector <int> &, vector <string>);
string int_to_string(int);
int string_to_int(string);