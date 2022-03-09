#include "includer.h"

/*void handler_nodes(int s){

        shmdt(dati);
        shmctl(shmid, 0, IPC_RMID);

}*/

int main(int argc, char** argv){

    struct LibroMastro *dati;
    Struttura_Stampa *datiNodi;
    struct msqid_ds controllocoda;
    
    int msgid,shmid, shmid_table, *T, semid;
    time_t t;
    int i,j, TransactionPool = 0, flag = 1, lb = 0;
    int timerand = (SO_MAX_TRANS_PROC_NSEC-SO_MIN_TRANS_PROC_NSEC)+1;
    long block[5][SO_BLOCK_SIZE];
    long msg_to_rec = 0;

    struct timespec tim, tim2;
    messaggio msg;

    /*signal(SIGKILL, handler_nodes);*/

    srand((unsigned) time(&t)*getpid()/*aggiungere portafoglio*/);

    tim.tv_sec = 0;
    tim.tv_nsec = rand() % timerand + SO_MIN_TRANS_PROC_NSEC;
    shmid = shmget(SHM_KEY, sizeof(Struttura_Stampa), 0);
    shmid_table = shmget(SHM_TABLE,sizeof(int)*(SO_NODES_NUM), 0);
    semid = semget(1000, 2, S_IRUSR | S_IWUSR);
    datiNodi = (Struttura_Stampa *)shmat(shmid,NULL,0);
    T = shmat(shmid_table,NULL,0);

    if((msgid = msgget(getpid(), IPC_CREAT| 0777))<0){
        printf("error nodi\n");
    }     

    releaseSem(semid,0);


    while(flag == 1){   

        reserveSem(semid,1);

            if((msgrcv(msgid, (void *)&msg, sizeof(msg), msg_to_rec, 0))<0){
                printf("messaggio non ricevuto\n");
            }
            else{
                printf("Transazione di %d con reward di %.0f all'istante %.4f, NODO %d, Utente sender %d, Utente reciver %d\n\n", msg.transfer, msg.reward, msg.Timestamp, getpid(), msg.sender, msg.reciver);
                TransactionPool++;
            }

            if(TransactionPool == SO_TP_SIZE){
                TransactionPool=TransactionPool-10;
                lb++;
                if(lb = 10){
                /*kill(getppid(), SIGUSR2);*/
                }
            }

        releaseSem(semid, 1);

        nanosleep(&tim, &tim2);
    }

       

}