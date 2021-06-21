#include "Funciones.h"

int module(int a, int n){
    int r = a-n*(a/n);
    r = r+(r<0)*n;
    return r;
}

int recursive_Euclid(int a, int b){
    if (module(a, b) == 0){
        return b;
    }
    else   {
        int temp = b;
        b = module(a, b);
        a = temp;
        recursive_Euclid(a,b);
    }
}

int Euclid(int a, int b){
    while (module(a, b) != 0){
        int temp = b;
        b = module(a, b);
        a = temp;
    }
    return b;
}

int mcd(int a, int b){
    return Euclid(a, b);
}

int Euclid_extended(int a, int b) {
    int cont = 0;
    int temp1 = a;
    int temp2 = b;
    while (module(a, b) != 0) {
        int temp = b;
        b = module(a, b);
        a = temp;
        cont++;
    }
    cont = cont + 2;
    int g[cont];
    g[0] = temp1;
    g[1] = temp2;

    int y[cont], u[cont], v[cont];
    u[0] = 1, u[1] = 0, v[0] = 0, v[1] = 1;
    for (int i = 1;; ++i) {
        y[i + 1] = g[i - 1] / g[i];
        g[i + 1] = g[i - 1] - (y[i + 1] * g[i]);
        u[i + 1] = u[i - 1] - (y[i + 1] * u[i]);
        v[i + 1] = v[i - 1] - (y[i + 1] * v[i]);
        if (g[i + 1] == 0) {
            //cout<<"Valor de x: "<<u[i]<<endl;
            //cout<<"Valor de y: "<<v[i]<<endl;
            return module(u[i], g[1]);
        }
    }
}

int inverse(int a, int b){
    return Euclid_extended(a, b);
}

int modular_exponentiation(int base, int exponent, int mod){
    int reply = base;
    exponent/=2;
    while (exponent){
        base = module(base*base, mod);
        if (module(exponent, 2)){
            reply = module(reply*base, mod);
        }
        exponent/=2;
    }
    return reply;
}

int random(int begin, int end) {
    srand(time(NULL));
    return begin + rand() % (end - begin);
}

vector<int> criba_eratostenes(int limit)
{
    vector<int> criba;
    int prime_found;  // primos que se vayan encontrando

    // llenando el vector desde 2 hasta limit
    for (int i = 2; i <= limit; i++)
        criba.push_back(i);

    if (limit == 2 || limit == 3)
        return criba;

    // iteradores para la seleccion
    vector<int>::iterator it = criba.begin();
    vector<int>::iterator it2;
    prime_found = *it;  // El primer primo es 2

    while (prime_found*prime_found < limit)
    {
        it2 = it + 1;

        for(; it2 <= criba.end(); it2++) //Borra multiplos de los primos hallados
            if(*it2 % prime_found == 0)
                criba.erase(it2);
        it++;
        prime_found = *it;
    }

    return criba;
}


vector <int> prime_bits(int bit){ //devuelve los elementos primos segun el numero de bits que pide
    vector <int> primos = criba_eratostenes(pow(2, bit)-1);
    vector<int>::iterator it = primos.begin();
    while (*it < pow(2, bit)/2){
        primos.erase(it);
    }
    return primos;
}

string add_zeros(string mssg, int tamano){ //añade ceros segun el tamaño del string q se desea
    for (int j = mssg.size(); j < tamano; ++j) {
        mssg.insert(0, "0");
    }
    return mssg;
}

void division_to_string(vector <string> &div, string mssg, int tamano){ //divide un string en bloques segun el tamaño
    string repos;
    for (int i = 0; i < mssg.size(); ) {
        repos = "";
        for (int j = 0; j < tamano; ++j) {
            repos.push_back(mssg[i]);
            i++;
        }
        div.push_back(repos);
    }
}

void division_to_int(vector <int> &div, vector <string> divided){
    for (int i = 0; i < divided.size(); ++i) {
        div.push_back(string_to_int(divided[i]));
    }
}

string int_to_string(int num){
    string cad(to_string(num));
    return cad;
}

int string_to_int(string cad){
    int num = atoi(cad.c_str());
    return num;
}