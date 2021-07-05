#include "RSA.h"

string fileOpen(string file){
    ifstream archivo(file.c_str());
    string linea;
    string text;
    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (getline(archivo, linea)) {
        // Lo vamos imprimiendo
        text = text + linea;
    }
    return text;
}

//RECEPTOR N BITS
RSA::RSA(int _bits) {
    bits = _bits;
    keysGenerator();
}

//EMISOR
RSA::RSA(ZZ _e, ZZ _n) {
    e = _e;
    n = _n;
}

//RECEPTOR
RSA::RSA(ZZ _p, ZZ _q, ZZ _d, ZZ _n) {
    p = _p;
    q = _q;
    d = _d;
    n = _n;
}

RSA::~RSA() {}

void RSA::info() {
    cout << "\n___________________________________________\n";
    cout << "\n\tRSA - " << countBits(n);
    cout << "\n\np: " << p;
    cout << "\n\nq: " << q;
    cout << "\n\nn: " << n;
    cout << "\n\ne: " << e;
    cout << "\n\nd: " << d;
    cout << "\n___________________________________________\n";

}

void RSA::keysGenerator() {
    //Hallamos p y q
    srand(time(NULL));

    //Hallamos n
    do {
        p = RandomPrime(bits / 2);
        q = RandomPrime(bits / 2);
        n = p * q;
    } while (countBits(n) != bits);

    //Hallamos phi
    ZZ phi = (p - 1) * (q - 1);
    // 1 < e < phi
    do {
        e = RandomNumber(ZZ(2), phi - 1);
    } while (check(e,phi) != 1);

    //hallar d
    // 1 < d < phi -> inversa de gcd(e,phi)
    d = inverse(e, phi);

    info();                    //Mostrar numero de bits y claves generadas
}


void RSA::decipher(string cipherCode) {

    string trans = divideBlocks(cipherCode);
    string plaintext;

    int MS_letter ( ZZtoStr(ZZ(alphabet.size() - 1)).size());
    ZZ num;

    //REAGRUPAR
    for (int i = 0; i < trans.size(); i += MS_letter) {
        num = conv<ZZ>(trans.substr(i, MS_letter).c_str());
        if (num < alphabet.size())
            plaintext += alphabet[to_int(num)];
    }
    message = plaintext;
}


string RSA:: divideBlocks(string cipherCode){

    string  trans;
    int N_size = ZZtoStr(n).size();
    ZZ C, num;

    //DIVIDIR MENSAJE EN BLOQUES DE TAMAÑO N
    for (int i = 0; i < cipherCode.size(); i += N_size) {
        num = conv<ZZ>(cipherCode.substr(i, N_size).c_str());
//        C = modPow_TRC(num, d, n, p, q);
        C = modPow(num, d,n);
        int C_size = N_size - 1 - ZZtoStr(C).size();
        reagroup(C, trans, N_size, C_size);
    }
    return trans;
}



void RSA::cipher(string plaintext ){

//   plaintext = blocks(plaintext);

    string cipherCode;
    ZZ C, num;
    int N_size = ZZtoStr(n).size();

    for (int i = 0; i < plaintext.size(); i += N_size - 1) {
        num = conv<ZZ>(plaintext.substr(i, N_size - 1).c_str());
        C = modPow(num, e, n);
        int C_size = N_size - ZZtoStr(C).size();
        reagroup(C, cipherCode, N_size, C_size);
    }

    crypted_letter = cipherCode;
    message = "";
    plaintext = "";
}



string RSA::cipherSwap(string plaintext ,ZZ _e,ZZ _n){
    // C = modPow(num, e, n);
    Swap(e,_e); Swap(n,_n);
    cipher(plaintext);
    Swap(e,_e); Swap(n,_n);
    return crypted_letter;
}

string RSA::decipherSwap(string plaintext ,ZZ _e, ZZ _n){
    // C = modPow(num, e, n);
    Swap(d,_e);  Swap(n,_n);
    int a= to_int(mod(ZZ(plaintext.size() ), ZZ(ZZtoStr(n).size())));
    plaintext = plaintext.substr(a);
    decipher(plaintext);
    Swap(d,_e);  Swap(n,_n);
    return message;
}



string RSA::completeZeros(string msg, ZZ _n){
    int digit =ZZtoStr(_n).size()-1;
    int c = to_int(mod(ZZ(msg.size()),ZZ(digit)));
    string zero(digit-c,'0');
    return zero+msg;
}


string RSA::firmaCipher(string msg,ZZ _e,ZZ _n){
    string rubric = cipherSwap(blocks(msg),d,n);
    rubric = completeZeros(rubric,_n);
    //Firma
    return  cipherSwap(rubric,_e,_n);
}



string RSA::firmaDecipher(string msg,ZZ _e,ZZ _n){
    string firma = divideBlocks(msg);
    return decipherSwap(firma,_e,_n);
}


string RSA:: blocks(string msg){

    string cipherCode, trans, block;
    int  N_size, Extra, MS_letter;
    N_size = ZZtoStr(n).size();
    Extra = alphabet.size();
    MS_letter = ZZtoStr(ZZ(Extra - 1)).size();
    string plus(to_string(Extra));

    //TRANSFORMAR EN SECUENCIA DE DIGITOS

    for (int i = 0; i < msg.size(); i++) {
        ZZ P = ZZ(alphabet.find(msg[i]));
        int P_size = ZZtoStr(ZZ(Extra - 1)).size() - ZZtoStr(P).size();
        reagroup(P, trans, N_size, P_size);
    }

    //AÑADIR DIGITO EXTRA
    while (mod(ZZ(trans.size()), ZZ(N_size - 1)) != 0 || mod(ZZ(trans.size()), ZZ(MS_letter)) != 0) {
        trans += plus;
    }
    return trans;

}



void RSA::show_encryption() {
    cout << endl << "Mensaje cifrado: " << crypted_letter << endl;
}

void RSA::show_decryption() {
    cout << endl << "Mensaje decifrado: " << message;
}