#include "RSA/RSA.h"

int main() {
    string file = "Message.txt";
    //RSA receptor(512);                         //El receptor indica el numero de bits para generar claves
    //RSA emisor(receptor.e, receptor.n); //El emisor que mandara los mensajes recibe las claves generadas
    ZZ p = conv <ZZ> ("83618702482976873355419185741462327875394103316198637477777483049307926570473");
    ZZ q = conv <ZZ> ("105251049421353313181103190131801353996604096101813730606770075755135246197629");
    ZZ d = conv <ZZ> ("1840309856668376933155638126995080591304945663816041708759107639748208699708507221084087039405244171513435949567557741301913484953316478635155617379020193");
    ZZ n = conv <ZZ> ("8800956187585237898505264599051143886382655083622737613367702104247583660916386270531869215664928173069596422233627744177103019346052453570741411554008517");
    RSA receptor(p, q, d, n);
    string cypher_message = fileOpen(file);
    //emisor.message = "Algebra Abstracta";       //El emisor escribe su mensaje
    //emisor.cipher(emisor.message);              //El emisor cifra su mensaje, el cifrado se almacena en el atributo crypted letter
    //receptor.decipher(emisor.crypted_letter);   //El receptor decifra el mensaje
    receptor.decipher(cypher_message);
    //emisor.show_encryption();                   //Muestra el cifrado almacenado en crypted_letter
    receptor.show_decryption();                 //Muestra el decifrado almacenado en message

    return 0;
}
