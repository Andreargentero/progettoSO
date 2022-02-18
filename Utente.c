#include "includer.h"

/*void handler_child(int s){

    shmdt(dati);
    shmctl(shmid, 0, IPC_RMID);
    }*/

int main(int argc, char** argv){
    
    
    int i = 0, n = 0;
    time_t t;
    struct MatrixNodes *datiNodi;
    int shmid;

    struct timespec tim, tim2;
    struct my_msg Transaction;

    int timerand;
    int semid;
    int msgid;
    

    timerand = (SO_MAX_TRANS_GEN_NSEC-SO_MIN_TRANS_GEN_NSEC)+1;
    srand((unsigned) time(&t)*getpid()/*wallet*/);
        
    shmid = shmget(SHM_KEY, sizeof(struct MatrixNodes), 0);
    datiNodi = (struct MatrixNodes *)shmat(shmid,NULL,0);
    semid = semget(SEM_KEY, SO_NODES_NUM, S_IRUSR | S_IWUSR);
    tim.tv_sec = 0;
    tim.tv_nsec = rand() % timerand + SO_MIN_TRANS_GEN_NSEC;
    
    /*signal(SIGKILL, handler_child);*/
    
    while(i < SO_RETRY){

        if(/*wallet*/3 >= 2){
            i = 0;
            if(n == 0){
                reserveSem(semid,0);
                if(semctl(semid, 0, GETVAL) == 0){
                /*msgid = msgget(datiNodi->PID[0], 0);
                /*Transaction.Timestamp = 0;
                Transaction.sender = GetPid();
                Transaction.reciver = 0;
                Transaction.transfer = 0;
                Transaction.reward = 0;*/
                Transaction.msg_type = 1;
                Transaction.some_text[0] = 1;
                if(msgsnd(msgid, (void *)&Transaction, 5, 0) == -1){
                    /*printf("messaggio non inviato\n");*/
                }
                releaseSem(semid,0);
                }
                /*SetWallet(GetWallet()- (rand() % (GetWallet()-1)+2));*/
                n++;
            }
            else{
                n--;
                i++;
            }
        }
        else if(/*wallet*/1 < 2){
            i++;
        }


       nanosleep(&tim, &tim2);
    }


    /*dati->MatrixUsers[atoi(argv[1])][2] = 1;*/
        
}