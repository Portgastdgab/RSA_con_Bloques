#include "RSA/RSA.h"



int main() {


    RSA receptor(2048);
    RSA emisor(2048);

    //FIRMA
    //Emisor
    string firmaCifrada=emisor.firmaCipher(fileOpen("Signature.txt"),receptor.e,receptor.n);
    cout<<"\n\nfirma Cifrada: "<<firmaCifrada;
    //Receptor
    string firmaDescifrada = receptor.firmaDecipher(firmaCifrada,emisor.e,emisor.n);
    cout<<"\n\nfirma Descifrada: "<<firmaDescifrada;

    emisor.e=receptor.e;emisor.n=receptor.n;
    emisor.message = fileOpen("Message.txt");                         //El emisor escribe su mensaje
    emisor.cipher(emisor.blocks(emisor.message));             //El emisor cifra su mensaje, el cifrado se almacena en el atributo crypted letter
    receptor.decipher(emisor.crypted_letter);                 //El receptor decifra el mensaje
    emisor.show_encryption();                   //Muestra el cifrado almacenado en crypted_letter
    receptor.show_decryption();                 //Muestra el decifrado almacenado en message

    return 0;
}