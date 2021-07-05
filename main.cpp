#include "RSA/RSA.h"



int main() {


    RSA receptor(512);
    RSA emisor(100);

    ZZ e,n;
    e=emisor.e;n=emisor.n;
    emisor.e=receptor.e;emisor.n=receptor.n;

    emisor.message = "Algebra Abstracta";                     //El emisor escribe su mensaje
    emisor.cipher(emisor.blocks(emisor.message));             //El emisor cifra su mensaje, el cifrado se almacena en el atributo crypted letter
    receptor.decipher(emisor.crypted_letter);                 //El receptor decifra el mensaje
    emisor.show_encryption();                   //Muestra el cifrado almacenado en crypted_letter
    receptor.show_decryption();                 //Muestra el decifrado almacenado en message

    emisor.e=e;emisor.n=n;

    string msj="[Aaron Misash Apaza Coaquira(201-10-48240,77569358) , Gabriel Santiago Choque Mayta (201-10-48248,70809056) , Geraldo Mark Romero Guillen (201-10-48119,77956852) , Jean Carlo Gino Condori Gonzales (201-10-47536,78957018) , Jose Enrique Vilca Campana (201-10-48429,79632845) ]";

    //Emisor
    string firmaCifrada=emisor.firmaCipher(msj,receptor.e,receptor.n);
    cout<<"\n\nfirma Cifrada: "<<firmaCifrada;
    //Receptor
    string firmaDescifrada = receptor.firmaDecipher(firmaCifrada,emisor.e,emisor.n);
    cout<<"\n\nfirma Descifrada: "<<firmaDescifrada;


    return 0;
}








/*------FIRMA---------*/

/*
int main(){
    string firmaDescifrada,firmaCifrada;

    RSA emisor(500);
    RSA receptor(100);

    string msj="[Aaron Misash Apaza Coaquira(201-10-48240,77569358) , Gabriel Santiago Choque Mayta (201-10-48248,70809056) , Geraldo Mark Romero Guillen (201-10-48119,77956852) , Jean Carlo Gino Condori Gonzales (201-10-47536,78957018) , Jose Enrique Vilca Campana (201-10-48429,79632845) ]";

    //Emisor
    firmaCifrada=emisor.firmaCipher(msj,receptor.e,receptor.n);
    cout<<"\nfirma Cifrada: "<<firmaCifrada;

    //Receptor
    firmaDescifrada = receptor.firmaDecipher(firmaCifrada,emisor.e,emisor.n);
    cout<<"\nfirma Descifrada: "<<firmaDescifrada;

}
*/

