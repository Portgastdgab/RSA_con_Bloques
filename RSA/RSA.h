#include "../Functions/BigMath.h"

typedef long long int ll;

class RSA {

private:

    int bits;
    ZZ d, p, q;

    void keysGenerator();

    void info();

    string alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ,.-( )abcdefghijklmnopqrstuvwxyz<>*1234567890[]";

public:
    ZZ e, n;
    string message;
    string crypted_letter;

    RSA(int);

    RSA(ZZ _p, ZZ _q, ZZ _d, ZZ _n); //e,d,n
    RSA(ZZ _e, ZZ n_);

    ~RSA();

    void cipher(string);                //Cifra el mensaje, el cifrado se almacena en el atributo crypted_letter

    void decipher(string);              //Descifrar el mensaje, el descifrado se almacena en el atributo message

    void show_encryption();             //muestra el atributo crypted_letter

    void show_decryption();             //muestra el atributo message

    string blocks(string);

    string firmaCipher(string ,ZZ,ZZ);

    string firmaDecipher(string ,ZZ,ZZ);

    string cipherSwap(string plaintext ,ZZ _e ,ZZ _n);

    string decipherSwap(string plaintext ,ZZ _e, ZZ _n);

    string completeZeros(string,ZZ);

    string divideBlocks(string );


};
