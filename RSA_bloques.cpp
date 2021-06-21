#include "RSA_bloques.h"

RSA::RSA(int bits) {
    vector<int> random_prime = prime_bits(bits); //genera los primos entre (bits^2)/2 y (bits^2)-1

    //De los primos encontrados asignar aleatoriamente 3 de estos para p, q y e
    //Como srand funciona con el tiempo de la PC se asignaria los mismos valores para p, q y e; para evitar esto
    // a la variable p y q les sumo 123 y 321 al tamaño de el vector prime_bits, consigo un numero random en el intevalo
    // y le saco el modulo para q el valor este entre 0 y el tamaño de prime_bits
    p = random_prime[module(random(123, 123 + random_prime.size()), random_prime.size() - 1)];
    q = random_prime[module(random(321, 321 + random_prime.size()), random_prime.size() - 1)];
    e = random_prime[random(0, random_prime.size() - 1)];
    N = p * q;
    oN = (p-1)*(q-1);
    while (mcd(e, oN) != 1) { //si el mcd(e, oN) != 1, busco otro primo tal que mcd(e, oN) == 1
        e = random_prime[random(0, random_prime.size() - 1)];
    }
    d = inverse(e, oN);
    cout << "El valor de \"p\" es: " << p << endl;
    cout << "El valor de \"q\" es: " << q << endl;
    cout << "El valor de \"e\" es: " << e << endl;
    cout << "El valor de \"d\" es: " << d << endl;
    cout << "El valor de \"N\" es: " << N << endl;
}

RSA::RSA(int a, int b) {
    e = a;
    N = b;
}

void RSA::chiper(string mssg) {
    for (int i = module(mssg.size(), ((int_to_string(N)).size())-1); i < ((int_to_string(N)).size())-1 and i != 0; ++i) {
        mssg.append(" ");       //añade la letra menos significativa si el tamaño del mensaje no es multiplo de el tamaño de N-1
    }
    string numbers_text;

    cout<<"convierte las posiciones y luego anade los ceros"<<endl;
    for (int i = 0;i < mssg.size(); ++i) { //convierte las posiciones y luego anade los ceros
        cout<<add_zeros(int_to_string(alfabeto.find(mssg[i])), int_to_string(alfabeto.size()).size())<<" ";
        numbers_text.append(add_zeros(int_to_string(alfabeto.find(mssg[i])), int_to_string(alfabeto.size()).size()));
    }
    mssg = numbers_text;

    cout<<endl<<"Bloques segun N-1"<<endl;
    vector <string> division_for_N;
    division_to_string(division_for_N, mssg, ((int_to_string(N)).size())-1);
    for (int i = 0; i < division_for_N.size(); ++i) {
        cout<<division_for_N[i]<<" ";
    }
    vector <int> mssg_empower;

    cout<<endl<<"Bloques segun N-1 en numeros"<<endl;
    division_to_int(mssg_empower, division_for_N);
    for (int i = 0; i < mssg_empower.size(); ++i) {
        cout<<mssg_empower[i]<<" ";
    }
    cout<<endl<<"C^e)mod N"<<endl;
    for (int i = 0; i < mssg_empower.size(); ++i) { // (C^e)mod N
        mssg_empower[i] = modular_exponentiation(mssg_empower[i], e, N);
        cout<<mssg_empower[i]<<" ";
    }
    for (int i = 0;i < mssg_empower.size(); ++i) { //convierte las posiciones a string con los ceros añadidos
        encrypted_letter.append(add_zeros(int_to_string(mssg_empower[i]), int_to_string(N).size()));
    }

}

void RSA::dechiper(string letters) {
    vector <string> division_for_N;

    cout<<endl<<endl<<endl<<"Bloques segun N-1"<<endl;
    division_to_string(division_for_N, letters, int_to_string(N).size());
    for (int i = 0; i < division_for_N.size(); ++i) {
        cout<<division_for_N[i]<<" ";
    }
    cout<<endl<<"Bloques segun N-1 con numeros"<<endl;
    vector <int> mssg_empower;
    division_to_int(mssg_empower, division_for_N);
    for (int i = 0; i < mssg_empower.size(); ++i) {
        cout<<mssg_empower[i]<<" ";
    }
    cout<<endl<<"(C^d)mod N"<<endl;
    for (int i = 0; i < mssg_empower.size(); ++i) {
        mssg_empower[i] = modular_exponentiation(mssg_empower[i], d, N);
        cout<<mssg_empower[i]<<" ";
    }
    letters = "";
    cout<<endl<<"Primer anadida en bloques de N-1"<<endl;
    for (int i = 0; i < division_for_N.size(); ++i) {
        cout<<add_zeros(int_to_string(mssg_empower[i]), int_to_string(N).size()-1)<<" ";
        letters.append(add_zeros(int_to_string(mssg_empower[i]), int_to_string(N).size()-1));
    }

    for (vector <string>::iterator it = division_for_N.end(); it > division_for_N.begin() ; --it) { // limpia el vector division_for_N para volver a usarlo
        division_for_N.erase(it);
    }

    for (vector <int>::iterator it = mssg_empower.end()-1; it > mssg_empower.begin() ; --it) { // limpia el vector division_for_N para volver a usarlo
        mssg_empower.erase(it);
    }
    mssg_empower.erase(mssg_empower.begin());

    division_to_string(division_for_N, letters, int_to_string(alfabeto.size()).size());
    division_to_int(mssg_empower, division_for_N);
    for (int i = 0; i < mssg_empower.size(); ++i) {
        message.push_back(alfabeto[mssg_empower[i]]);
    }

}

void RSA::show_encryption() {
    cout << endl << "Mensaje cifrado: "<<encrypted_letter<<endl;
}

void RSA::show_decryption() {
    cout << endl << "Mensaje decifrado: "<<message;
}