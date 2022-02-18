#include "includer.h"

int semid,SemID_NU;
int shmid;
int Bool = 0;
struct timespec start, stop;



void handler_int(int s) {

        SetSem(semid, 1, SO_USERS_NUM+SO_NODES_NUM);

        if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
        }
        Bool = 1;
        system("stty echoctl");
        signal(SIGINT, SIG_IGN);

}

/*void handler_int2(int s) {

        shmdt(dati);
        shmctl(shmid, 0, IPC_RMID);

        signal(SIGCHLD, SIG_DFL);

}*/


int main(int argc, char** argv){
    double accum;
    pid_t pid;
    int pID;
    int msgid;
    int/*for*/ i = 0,z = 0,l,m,o,n,k;
    int supBoy = 0;
    char str[10];
    struct MatrixNodes *datiNodi;
    
    
    
    system("stty -echoctl");
    signal(SIGINT, handler_int);
    /*signal(SIGCHLD, handler_int2);*/

    semid = semget(IPC_PRIVATE,2,IPC_CREAT|S_IRUSR | S_IWUSR);
    SemID_NU = semget(SEM_KEY,SO_NODES_NUM,IPC_CREAT|S_IRUSR | S_IWUSR);
    shmid = shmget(SHM_KEY, sizeof(struct MatrixNodes), IPC_CREAT|0666);
    datiNodi = (struct MatrixNodes *)shmat(shmid,NULL,0);

    
    initSemAvailable(semid,0);
    initSemInUse(semid,1);
    initSemAvailable(SemID_NU,0);

    Utenti(i, pid, semid, str);

    Nodi(z, pid, semid, str);

    printf("Press Ctrl+C to start.\n");
    printf("Press Ctrl+z or Ctrl+\\ to terminate.\n");

    while (1)
    {
        if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
        }

        accum = ( stop.tv_sec - start.tv_sec )
            + ( stop.tv_nsec - start.tv_nsec )
            / BILLION;

        if(accum == SO_SIM_SEC){

            printf("--------------------------------------\n");            
            printf("-terminazione per tempo\n");

            printf("-Bilancio Utenti:\n");
            /*for( l = 0; l < SO_USERS_NUM; l++){
                printf("%d = %d\n", dati->MatrixUsers[l][0], dati->MatrixUsers[l][1]);
            }*/

            printf("-Bilancio Nodi:\n");
            for( m = 0; m < SO_NODES_NUM; m++){
                printf("%d = %d\n", datiNodi->PID[m], datiNodi->Wallet[m]);
            }

            printf("-Utenti terminati prematuramente:\n");
            /*for( o = 0; o < SO_USERS_NUM; o++){
                supBoy += dati->MatrixUsers[o][2];
            }
                printf("%d\n", supBoy);*/

            printf("-Numero Blocchi Libro Mastro\n");

            printf("-Numero trasazioni ancora in trasaction pool:\n");
            /*for( n = 0; n < SO_NODES_NUM; n++){
                printf("%d = %d\n", dati->MatrixNodes[n][0], dati->MatrixNodes[n][2]);
            }*/
            

            semctl(semid, 0, IPC_RMID);
            semctl(SemID_NU, 0, IPC_RMID);
            for( k = 0; k < SO_NODES_NUM; k++){
                msgid = msgget(datiNodi->PID[k], 0);
                msgctl(msgid, IPC_RMID, NULL);
            }
            system("killall -SIGKILL Nodo");
            system("killall -SIGKILL Utente");
            shmdt(datiNodi);
            shmctl(shmid, 0, IPC_RMID);
            exit(EXIT_SUCCESS);
        }

        sleep(1);

        /*if(Bool == 1){
            printf("--------------------------------------\n");
            printf("Utente a Nodo attivi:\n");
            printf("budget corrente di ogni Utente e Nodo:\n");
        }*/
    }


}