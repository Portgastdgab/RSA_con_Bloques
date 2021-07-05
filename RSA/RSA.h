#include "../Functions/BigMath.h"
#include "fstream"

typedef long long int ll;

string fileOpen(string);

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

    void cipher(string);                                    //Cifra el mensaje, el cifrado se almacena en el atributo crypted_letter

    void decipher(string);                                 //Descifrar el mensaje, el descifrado se almacena en el atributo message

    void show_encryption();                               //muestra el atributo crypted_letter

    void show_decryption();                               //muestra el atributo message

    string blocks(string);                               //forma un bloque para con los  respectivos indices del texto plano

    string firmaCipher(string ,ZZ,ZZ);                   //cifra la firma con las claves publicas del receptor

    string firmaDecipher(string ,ZZ,ZZ);                 //descifra la firma con las claves publicas del emisor

    string cipherSwap(string plaintext ,ZZ _e ,ZZ _n);   //cifra con las claves e y n del receptor

    string decipherSwap(string plaintext ,ZZ _e, ZZ _n); //descifra con las claves publicas del emisor

    string completeZeros(string,ZZ);                     //completa ceros

    string divideBlocks(string );                        //divide el mensaje en bloque de tamaño N


};
