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

/*void handler_master(int s) {

            semctl(semid, 0, IPC_RMID);
            semctl(SemID_NU, 0, IPC_RMID);
            semctl(semID,0, IPC_RMID);
            for( k = 0; k < SO_NODES_NUM; k++){
                msgid = msgget(T[k], 0);
                msgctl(msgid, IPC_RMID, NULL);
            }
            shmdt(datiNodi);
            shmdt(T);
            shmctl(shmid, 0, IPC_RMID);
            shmctl(shmid_table, 0, IPC_RMID);
            exit(EXIT_SUCCESS);

}*/

/*void handler_int2(int s) {

        shmdt(dati);
        shmctl(shmid, 0, IPC_RMID);

        signal(SIGCHLD, SIG_DFL);

}*/


int main(int argc, char** argv){
    double accum;
    int shmid_table;
    int pID;
    int msgid;
    int semID;
    int/*for*/ i = 0,z = 0,*T,m,k;
    int supBoy = 0;
    char str[10];
    Struttura_Stampa *datiNodi;
    
    
    
    system("stty -echoctl");
    signal(SIGINT, handler_int);
    /*signal(SIGUSR2, handler_master);*/
    /*signal(SIGCHLD, handler_int2);*/

    semid = semget(IPC_PRIVATE,2,IPC_CREAT|S_IRUSR | S_IWUSR);
    SemID_NU = semget(SEM_KEY,SO_NODES_NUM,IPC_CREAT|S_IRUSR | S_IWUSR);
    semID = semget(1000, 2, IPC_CREAT|S_IRUSR | S_IWUSR);
    shmid = shmget(SHM_KEY, sizeof(Struttura_Stampa), IPC_CREAT|0666);
    shmid_table = shmget(SHM_TABLE, sizeof(int)*((SO_NODES_NUM)), IPC_CREAT|0666);
    datiNodi = (Struttura_Stampa *)shmat(shmid,NULL,0);

    T = shmat(shmid_table, NULL,0);
    
    initSemAvailable(semid,0);
    initSemInUse(semid,1);
    initSemInUse(semID,0);
    initSemInUse(semID,1);
    initSemAvailable(SemID_NU,0);

    Utenti(i, T, semid, str);

    Nodi(z, T, semid, str);

    printf("Press Ctrl+C to start.\n");
    printf("Press Ctrl+z or Ctrl+\\ to terminate.\n");
    printf("--------------------------------------\n");

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

            system("killall -SIGKILL Nodo");
            system("killall -SIGKILL Utente");

            printf("--------------------------------------\n");            
            printf("-terminazione per tempo\n");

            printf("-Bilancio Utenti:\n");
            /*for( m = 0; m < SO_USERS_NUM; m++){
                printf("%d\n", T[m]);
            }*/

            printf("-Bilancio Nodi:\n");
            for( m = 0; m < SO_NODES_NUM; m++){
                printf("%d\n", T[m]);
            }

            printf("-Utenti terminati prematuramente:\n");
            /*for( m = SO_USERS_NUM; m < SO_USERS_NUM*2; m++){
                supBoy += T[m];
            }
                printf("%d\n", supBoy);*/

            printf("-Numero Blocchi Libro Mastro\n");

            printf("-Numero trasazioni ancora in trasaction pool:\n");
            /*for( n = 0; n < SO_NODES_NUM; n++){
                printf("%d = %d\n", dati->MatrixNodes[n][0], dati->MatrixNodes[n][2]);
            }*/
            

            semctl(semid, 0, IPC_RMID);
            semctl(SemID_NU, 0, IPC_RMID);
            semctl(semID,0, IPC_RMID);
            for( k = 0; k < SO_NODES_NUM; k++){
                msgid = msgget(T[k], 0);
                msgctl(msgid, IPC_RMID, NULL);
            }
            shmdt(datiNodi);
            shmdt(T);
            shmctl(shmid, 0, IPC_RMID);
            shmctl(shmid_table, 0, IPC_RMID);
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