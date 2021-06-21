#include "RSA_bloques.h"

//#include "../../Funciones/Funciones.h"

int main() {
    RSA yo(7);                              //indico el numero de bits del que recibira los mensajes
    RSA persona(yo.e, yo.N);                //La persona que mandara los mensajes recibe las claves generadas
    persona.message = "modo diablo";           //La persona escribe su mensaje
    persona.chiper(persona.message);        //la persona cifra su mensaje, el cifrado se almacena en el atributo encrypted letter
    yo.dechiper(persona.encrypted_letter);  //quien recibe el mensaje lo decifra
    persona.show_encryption();              //muestra el cifrado almacenado en encrypted_letter
    yo.show_decryption();                   //muestra el decifrado almacenado en message

    return 0;
}
