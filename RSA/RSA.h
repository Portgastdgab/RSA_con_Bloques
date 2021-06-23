#include "../Functions/BigMath.h"

typedef long long int ll;

class RSA{

private:
    ZZ d,p,q,phi;
    int bits;
    void keysGenerator(int);
    void info();
    string alphabet = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";


public:
    ZZ e,n;
    string message;
    string crypted_letter;

    RSA();
    RSA(int);
    RSA(ZZ _e,ZZ _d,ZZ _n); //e,d,n
    RSA(ZZ _e, ZZ n_);
    ~RSA();
    string cipher(string);
    string decipher(string);
    void show_encryption();
    void show_decryption();


};
