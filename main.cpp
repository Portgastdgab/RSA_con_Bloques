#include <iostream>
#include "RSA/RSA.h"

int main() {

    RSA receptor(1024);                         //indico el numero de bits de quien recibira los mensajes
    RSA emisor(receptor.e, receptor.n); //La persona que mandara los mensajes recibe las claves generadas
    emisor.message = "Algebra Abstracta";             //La persona escribe su mensaje
    emisor.cipher(emisor.message);              //la persona cifra su mensaje, el cifrado se almacena en el atributo encrypted letter
    receptor.decipher(emisor.crypted_letter);   //quien recibe el mensaje lo decifra
    emisor.show_encryption();                   //muestra el cifrado almacenado en encrypted_letter
    receptor.show_decryption();                 //muestra el decifrado almacenado en message

    return 0;
}
