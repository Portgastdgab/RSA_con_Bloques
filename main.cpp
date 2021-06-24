
#include <iostream>
//#include "InfInt.h" //libreria para numeros grandes
//#include "BigMath.h"
#include <stdlib.h>
#include <time.h>
#include <NTL/mat_ZZ.h>
#include "BigMath.h"
#include <string>


typedef long long int ll;
using namespace std;



const string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";


class RSA{

    private:
        ZZ d,p,q,phi;
        int bits;
        void keysGenerator(int);
        void info();



    public:
        ZZ e,n;
        RSA();
        RSA(int);
        RSA(ZZ _e,ZZ _d,ZZ _n); //e,d,n
        RSA(ZZ _e, ZZ n_);
        ~RSA();
        string cipher(string);
        string decipher(string);



};


//RECEPTOR N BITS
RSA::RSA(int _bits){
    bits = _bits;
    keysGenerator(_bits);
}

//EMISOR
RSA::RSA(ZZ _e, ZZ _n){
    e=_e;
    n=_n;
}

//RECEPTOR
RSA::RSA(ZZ _e,ZZ _d, ZZ _n){
    e=_e;
    d=_d;
    n=_n;
}
RSA::~RSA() {}



void RSA::keysGenerator(int bits) {
    //Hallamos p y q

    srand(time(NULL));

    //Hallamos n
    do{
        p = RandomPrime(bits/2);
        q = RandomPrime(bits/2);
        n=p*q;
    }while(countBits(n)!=bits);


    //Hallamos phi
    phi=(p-1)*(q-1);

    // 1 < e < phi
    do{
        e=RandomNumber(ZZ(2),phi-1);
    }while(binaryGCD(e,phi) !=1);

    //hallar d
    // 1 < d < phi -> inversa de gcd(e,phi)
    d=inverse(e,phi);

}



void RSA::info(){
    cout<<"\n___________________________________________\n";
    cout<<"\n\tRSA - "<<countBits(n);
    cout<<"\n\np: "<<p;
    cout<<"\n\nq: "<<q;
    cout<<"\n\nn: "<<n;
    cout<<"\n\nphi: "<<phi;
    cout<<"\n\ne: "<<e;
    cout<<"\n\nd: "<<d;
    cout<<"\n___________________________________________\n";

}


string RSA::cipher(string plaintext){


    info();

    string cipherCode,trans,block;

    int message_size,N_size,Extra,MS_letter;

    message_size = plaintext.size();
    N_size = ZZtoStr(n).size();
    Extra = alphabet.size();
    MS_letter = ZZtoStr(ZZ(Extra-1)).size();

    string plus(to_string(Extra));


    //TRANSFORMAR EN SECUENCIA DE DIGITOS

    for(int i=0;i<message_size;i++){

        int P = alphabet.find(plaintext[i]);
        int P_size = ZZtoStr(ZZ(Extra-1)).size() - to_string(P).size();

        if(to_string(P).size() < MS_letter){

            string zeros(P_size,'0');
            zeros += to_string(P);
            trans += zeros;

        }
        else{
            trans += to_string(P);
        }

    }


    while(mod(ZZ(trans.size()),ZZ(N_size-1))!=0 || mod(ZZ(trans.size()),ZZ(MS_letter))!=0){
        trans += plus;
    }



    //DIVIDIR EN BLOQUES

    ZZ C,num;

    for(int i=0;i<trans.size();i+=N_size-1){

        num = conv<ZZ>(trans.substr(i,N_size-1).c_str());

        C = modPow(num,e,n);


        int C_size = N_size - ZZtoStr(C).size();

        if(ZZtoStr(C).size() < N_size){

            string zeros(C_size,'0');
            zeros += ZZtoStr(C);
            cipherCode += zeros;

        }
        else{
            cipherCode += ZZtoStr(C);
        }


    }

    return cipherCode;

}



string  RSA::decipher(string cipherCode){

    string plaintext,trans;


    int message_size,N_size,Extra,MS_letter;

    message_size = plaintext.size();
    N_size = ZZtoStr(n).size();
    Extra = alphabet.size();
    MS_letter = ZZtoStr(ZZ(Extra-1)).size();

    //DIVIDIR MENSAJE EN N DIGITOS

    ZZ C,num;

    for(int i=0;i<cipherCode.size();i+=N_size){

        num = conv<ZZ>(cipherCode.substr(i,N_size).c_str());

        C = modPow_TRC(num,d,n,p,q);

        int C_size = N_size -1 - ZZtoStr(C).size();

        if(ZZtoStr(C).size() < N_size-1){

            string zeros(C_size,'0');
            zeros += ZZtoStr(C);
            trans += zeros;

        }
        else{
            trans += ZZtoStr(C);
        }

    }


    //REAGRUPAR

    for(int i=0;i<trans.size();i+=MS_letter){

        num = conv<ZZ>(trans.substr(i,MS_letter).c_str());

        if(num < Extra)
            plaintext += alphabet[to_int(num)];



    }

    return plaintext;

}



int main() {

    //RECEPTOR GEN
    /*
     * PROGRAMA DE INICIO
     * genera claves
     */

    string msj;
    RSA receptor(2048);
    cout<<"\nInput your message: "; getline(cin,msj);
    string cipher_msj = receptor.cipher(msj);
    cout<<"\n\nCipher message: "<<cipher_msj;
    cout<<"\n\nDecipher message: "<<receptor.decipher(cipher_msj)<<"\n\n\n";


     //EMISOR
     /*
      * PROGRAMA para enviar mensajes a terceros
      */

//    string msj;
//    ZZ e,n;
//    cout<<"\nInput e: "; cin>>e;
//    cout<<"\nInput n: "; cin>>n;
//    RSA emisor(e,n);
//    cin.ignore();
//    cout<<"\nInput your message: "; getline(cin,msj);
//    cout<<"\n\nDecipher message: "<<emisor.cipher(msj)<<"\n\n";






/*
 *  COMPROBAR RESULTADOS
    //RECEPTOR DECIPHER
    string ciphercode;
    ZZ e,d,n;
    cout<<"\nInput your e: "; cin>>e;
    cout<<"\nInput your d: "; cin>>d;
    cout<<"\nInput your n: "; cin>>n;
    RSA receptor(e,d,n);
    cin.ignore();
    cout<<"\nInput your cipher message: "; getline(cin,ciphercode);
    cout<<"\n\nDecipher message: "<<receptor.decipher(ciphercode)<<"\n\n\n";
*/




    return 0;
}
