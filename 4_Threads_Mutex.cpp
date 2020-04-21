#include <iostream>
#include <thread>   // libreria per i thread
#include <mutex>    // libreria per i semafori mutex
 
using namespace std;
 
const int VALORE_INIZIALE = 10;
 
int totale = VALORE_INIZIALE; // risorsa condivisa
mutex mutexTotale; // semaforo per la risorsa "totale"
 
// funzione che aumenta le scorte
void carica(int n){
    /*
       lock: 1) verifica se la risorsa è occupata
                se semaforo è rosso si mette in attesa
             2) quando e' verde, lo mette a rosso e prosegue
     */
    mutexTotale.lock();
    // sezione critica INIZIO
        int aggiorno = totale + n;
        totale = aggiorno;
    // sezione critica FINE
    mutexTotale.unlock(); // rimette a verde il semaforo
}
 
// funzione che diminuisce le scorte
void scarica(int n){
    mutexTotale.lock();
        // sezione critica INIZIO
        int aggiorno = totale - n;
        totale = aggiorno;
        // sezione critica FINE
    mutexTotale.unlock();
}
 
int main() {
    int old = VALORE_INIZIALE;
    /*  creo un ciclo infinito perche'
        le interferenze di verificheranno in modo
        non prevedibile, quindi devo simulare un buon
     numero di esecuzioni dello stesso scenario (inizio:10;carica 5 e scarica 3)
     */
    while(true){
        // ad ogni inizio di test reimposto lo scenario iniziale
        totale = VALORE_INIZIALE;
        thread tProd(carica,5);   // creo il primo thread
        thread tCons(scarica, 3); // creo il secondo thread
        tProd.join();             // attendo i threads
        tCons.join();
        if (totale != old) {
            cout << "totale = " << totale <<" old = "<<old<< endl;
            old = totale;             // memorizzo il valore cambiato
        }
    }
    return 0;
}

