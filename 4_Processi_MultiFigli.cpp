/* 
    Creare n processi figli:
        - ogni figlio stamperà il proprio pid
        - il padre dopo aver atteso l'ultimo figlio stamperà tutti i pid dei figli
    il numero di figli da creare sarà impostato come argomento da linea di comando

*/
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[]){
    int status=0; //usato per la wait del padre
    int pid = 0; // gestire il valore di ritorno della fork
    
    if (argc == 2 && atoi(argv[1]) > 0) {
        int num = atoi(argv[1]); // leggo il parametro e lo trasformo in intero  
        int mySon[num]; // array i pid dei figli creati
    
        for (int i = 0;i<num; i++){
            pid = fork();
            if (pid==0) {
                sleep(2); 
                cout << "\nFIGLIO n." << i <<" | PID = " << getpid()<< endl;
                exit(0); // il figlio termina e comunica lo status con exit
            } else {
                // padre (memorizza il figlio) e continua a generare se i<num
                mySon[i]= pid;
            }
        }
        // questo codice sarà eseguito solo dal padre (i figli terminano prima di questa istruzione)
        waitpid(mySon[num-1], &status,0);

        for (int i = 0; i<num; i++)
            cout << mySon [i]<<" ";
        cout << endl;
    } else {
        cout << "Bisogna passare come parametro il numero di figli "<< endl;
    }
    return 0;
}
