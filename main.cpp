#include "RSA/RSA.h"



int main() {

    RSA receptor(512);                         //El receptor indica el numero de bits para generar claves
    RSA emisor(receptor.e, receptor.n); //El emisor que mandara los mensajes recibe las claves generadas
//    ZZ p = conv <ZZ> ("83618702482976873355419185741462327875394103316198637477777483049307926570473");
//    ZZ q = conv <ZZ> ("105251049421353313181103190131801353996604096101813730606770075755135246197629");
//    ZZ d = conv <ZZ> ("1840309856668376933155638126995080591304945663816041708759107639748208699708507221084087039405244171513435949567557741301913484953316478635155617379020193");
//    ZZ n = conv <ZZ> ("8800956187585237898505264599051143886382655083622737613367702104247583660916386270531869215664928173069596422233627744177103019346052453570741411554008517");
//    RSA receptor(p, q, d, n);
//    string cypher_message = "5291702368152087946076128350432133427619525644298358252989305580235335472718400325939467290944651759621145206963744475018767935489489438378791860426419490197937641227105068882137173072937851857430981159166177802494567096737048984940043528326672459465320226996807863483254660570006640477939003067967297731928175392890206820780754793505698746101272516614468354217634105901309538335406749099576339331890281877002949277657658392977918229586006559375922531178841503428584042496723812467183803957607016485059533894571648395275679285395066018510101362451969731433823407933118497354126279184787599862182751028340925498442846";
    emisor.message = "Algebra Abstracta";       //El emisor escribe su mensaje
    emisor.cipher(emisor.blocks(emisor.message));              //El emisor cifra su mensaje, el cifrado se almacena en el atributo crypted letter
    receptor.decipher(emisor.crypted_letter);   //El receptor decifra el mensaje
//    receptor.decipher(cypher_message);
    emisor.show_encryption();                   //Muestra el cifrado almacenado en crypted_letter
    receptor.show_decryption();                 //Muestra el decifrado almacenado en message

    return 0;
}



/*------FIRMA---------*/

/*
int main(){
    string firmaDescifrada,firmaCifrada;

    RSA emisor(500);
    RSA receptor(100);

    string msj = "coasdas";

    //Emisor
    firmaCifrada=emisor.firmaCipher(msj,receptor.e,receptor.n);
    cout<<"\nfirma Cifrada: "<<firmaCifrada;

    //Receptor
    firmaDescifrada = receptor.firmaDecipher(firmaCifrada,emisor.e,emisor.n);
    cout<<"\nfirma Descifrada: "<<firmaDescifrada;

}
*/

