/*
Creare un figlio (dormiente) che si mette in attesa per 10 secondi (sleep), poi comunica a padre lo status 47. 
Inoltre se il programma viene richiamato usando il parametro 10, il processo padre, dopo aver creato il processo figlio  (dormiente), 
crea un secondo figlio (assassino) che ucciderà il primo figlio.
Il padre dopo l'attesa, stamperà  un messaggio appropriato: 
- se il primo figlio è terminato correttamente (dormito-svegliato-exit) e ho richiamato il programma senza parametro (esempioKill)
- se il secondo figlio ha ucciso il primo (esempioKill.exe 10)
*/
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main(int argc, char *argv[])
{
	// gestire il parametro per capire se creare un secondo figlio (assassino)
    bool creaAssassino = false;
    if (argc == 2){ // controllo che ci sia un parametro prima di usarlo
        int num = atoi(argv[1]); // converte una stringa in un intero, uso il parametro
        if (num < 1 || num > 10) {
            cout << "Attenzione: il numero deve essere compreso tra 1 e 10" << endl;
            return -2; // termina il programma con errore
        }
        creaAssassino = (num==10);
    }
    int sonPid = fork(); // creo un processo figlio
    int status; // utilizzata per far comunicare il primo figlio con il padre
    if (sonPid<0){
        cout << "Errore nella creazione del figlio!" << endl;
        return -1;
    }
    if (sonPid == 0){
        // sono il figlio 
        cout << "FIGLIO | Mi riposo 10 secondi" << endl;
        sleep(10);   // metto a riposo il processo figlio
        exit(47);    // figlio si sveglia e comunica al padre il mitico 47 
	} else {
        // sono il padre
        cout << "PADRE | mio figlio ha pid = " << sonPid << " e penso stia dormendo."<< endl;
        if (creaAssassino){
            // allora creo un secondo figlio
            if (fork()==0){
                // sono il secondo figlio
                cout << "FIGLIO 2 | Sono il fratello di " << sonPid << " ora uccido mio fratello!" << endl;
                kill(sonPid,9);  // avendo ho il pid di mio fratello lo uccido
                return 0;
            }
        }
        // il papa' si mette in attesa del figlio dormiente (primo)
        waitpid(sonPid,&status,0);
        if (WIFEXITED(status)) 
            cout << "PADRE | mio figlio terminato correttamento (EXIT) con status = " << WEXITSTATUS(status)<<endl; 
        else if (WIFSIGNALED(status)) 
            cout << "PADRE | mio figlio terminato con segnale (KILL) = " << WTERMSIG(status)<<endl; 
    }
	
	return 0;
}
