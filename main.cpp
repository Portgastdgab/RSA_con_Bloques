#include "RSA/RSA.h"

int main() {

    RSA receptor(512);                         //El receptor indica el numero de bits para generar claves
    RSA emisor(receptor.e, receptor.n); //El emisor que mandara los mensajes recibe las claves generadas
    emisor.message = "Algebra Abstracta";       //El emisor escribe su mensaje
    emisor.cipher(emisor.message);              //El emisor cifra su mensaje, el cifrado se almacena en el atributo crypted letter
    receptor.decipher(emisor.crypted_letter);   //El receptor decifra el mensaje
    emisor.show_encryption();                   //Muestra el cifrado almacenado en crypted_letter
    receptor.show_decryption();                 //Muestra el decifrado almacenado en message

    return 0;
}
