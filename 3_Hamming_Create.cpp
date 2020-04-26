/*  Data un stringa binaria determina la codifica in base
    al codice di HAMMING
    https://it.wikipedia.org/wiki/Codice_di_Hamming
    Corso TPI anno III
 */
#include <iostream>
#include <math.h>
using namespace std;

// verifica se la stringa in input è composta solo da 0 e 1
bool isBinary(string s){
    for (int i=0; i<s.length(); i++){
        if (s[i] != '0' && s[i] != '1')
            return false; //abbiamo trovato qualcosa di diverso da 0 e 1
    }
    return true;
}

int main() {
    
    int n;   // lunghezza in bit dell'informazione
    int r=0; // numero di bit di controllo da aggiungere
    string number; // stringa in input
    
    // richiedo l'input fino a quando non è corretto
    do {
        cout << "Dammi la stringa binaria da codificare:";
        cin >> number;
    } while (! isBinary(number));
    
    n = (int)number.length(); // determino i bit informazione
    cout << "La stringa da codificare ha "<< n << " bits.";
    
    // Calcoliamo quanti bit di controllo saranno necessari
    while (pow(2,r)<= n+r) //aumento r fino a quanto 2^r non è inferiore a n+r
        r++;
    cout << "\nSaranno necessari "<<r<< " bits di controllo. ";

    // ATTENZIONE: per rendere tale algoritmo simile al procedimento
    // usato con excel useremo le posizioni da 1 a n+r dell'array
    // sprecando la posizione 0. Lo scopo di tale algoritmo è puramente didattico
    
    int message[n+r]; // array con la codifica di hammming

    // inserisco i bit di informazione nelle posizioni che non sono potenze due
    // le potenze di due hanno una caratteristica AND-BIT-A-BIT con il loro predecessore è uguale a ZERO
    // 1000 & 0111 = 0
    for (int i=1,j=0; i<=n+r; i++){
       if ( (i & (i - 1)) != 0) // considero le posizioni non potenze di due
            message[i] = (int) number[j++]-48; //inserisco il bit di informazione trasformando il suo valore ASCII
       else
            message[i] = 0; // impostiamo le posizioni di controllo a 0
    }
    // valorizzo le potenze di 2: 1, 2, 4, 8, etc... le ottengo facilmente con lo SHIFT a sinistra
    for (int i=1;i<=n+r;i=i<<1){
        for (int j = i+1; j<=n+r; j++){ // considero le posizioni successive, ma solo quelle necessarie
            if ((i&j)==i) { //le posizioni che hanno il bit 1 nella stessa posizione di i (i AND-BIT-A-BIT j == i)
                message[i] = message[i] ^ message[j];
            }
        }
        
        
    }
    // stampo il risultato
    cout << endl << "La stringa codificata: ";
    
    for (int i=1; i<=n+r; i++){
        cout << message[i];
    }
    cout << endl;
    return 0;
}
