#include <iostream>
#include "Funciones/Funciones.h"

using namespace std;

class RSA {
private:
    int d;
    int p;
    int q;
    int oN;
    string alfabeto = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

public:
    int e;
    int N;
    string message;
    string encrypted_letter;

    RSA(int);

    RSA(int, int);

//    virtual ~RSA(void);
//    int resto_chino(int);

    void chiper(string);        //convierte cada letra del mensaje en (su posicion^e)mod N

    void dechiper(string); //convierte cada numero del vector en (numero^d)mod N

    void show_encryption();     //imprime cada valor del vector encrypted_letter de quien cifro el mensaje

    void show_decryption();     //imprime el string de quien decifro el mensaje cifrado
};

