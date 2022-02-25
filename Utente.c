#include "includer.h"

/*void handler_child(int s){

    shmdt(dati);
    shmctl(shmid, 0, IPC_RMID);
    }*/

int main(int argc, char** argv){
    
    
    int i = SO_BUDGET_INIT, n = 0, j=0, k = 0;
    time_t t;
    Struttura_Stampa *datiNodi;
    int shmid;

    struct timespec tim, tim2;
    messaggio msg;

    int timerand;
    int semid,shmid_table, msgsend;
    int msgid = 0;
    int *T;

    timerand = (SO_MAX_TRANS_GEN_NSEC-SO_MIN_TRANS_GEN_NSEC)+1;
    srand((unsigned) time(&t)*getpid()/*wallet*/);
        
    shmid = shmget(SHM_KEY, sizeof(Struttura_Stampa), 0);
    datiNodi = (Struttura_Stampa *)shmat(shmid,NULL,0);
    semid = semget(1000, 2, S_IRUSR | S_IWUSR);
    shmid_table = shmget(SHM_TABLE, sizeof(int)*(SO_NODES_NUM), 0);
    T = shmat(shmid_table, NULL, 0);
    tim.tv_sec = 0;
    tim.tv_nsec = rand() % timerand + SO_MIN_TRANS_GEN_NSEC;
    
    /*signal(SIGKILL, handler_child);*/
    

    while(i != 0){
        
        if(/*wallet*/3 >= 2){
                reserveSem(semid,0);
            
            while(msgid < 0){
                msgid = msgget((pid_t)T[rand() % SO_NODES_NUM],0777);
            }

                    msg.qualcosa = 200;
                    msg.pid = getpid();
                    
                    msgsend=msgsnd(msgid, &msg,sizeof(msg),IPC_NOWAIT);

                    if( msgsend < 0){
                        
                    while (msgsend < 0)
                    {
                        /*printf("while\n");*/
                        msgsend=msgsnd(msgid, &msg,sizeof(msg),IPC_NOWAIT);
                        if(k == 1-1){
                            printf("Uccisione Utente\n");
                            kill(getpid());
                        }
                        k++;
                    }

                    printf("redivivo\n");
                    
                    }

                /*Transaction.Timestamp = 0;
                Transaction.sender = GetPid();
                Transaction.reciver = 0;
                Transaction.transfer = 0;
                Transaction.reward = 0;*/
                
                releaseSem(semid,1);
                /*SetWallet(GetWallet()- (rand() % (GetWallet()-1)+2));*/
                i= i-100;
                releaseSem(semid,0);
            nanosleep(&tim, &tim2);
        }
        else if(/*wallet*/1 < 2){
            i++;
        }
    }


    /*dati->MatrixUsers[atoi(argv[1])][2] = 1;*/
        
}