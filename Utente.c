#include "includer.h"

/*void handler_child(int s){

    shmdt(dati);
    shmctl(shmid, 0, IPC_RMID);
    }*/

int main(int argc, char** argv){
    
    
    int Budget = SO_BUDGET_INIT, Random, Try = 0, Trasfer;
    time_t t;
    Struttura_Stampa *datiNodi;
    int shmid;

    struct timespec tim, tim2, STAMP;
    messaggio msg;

    int timerand;
    int semid,shmid_table,shmid_user, msgsend;
    int msgid;
    int *T,*U;
    float timeTransf, Reward;

    timerand = (SO_MAX_TRANS_GEN_NSEC-SO_MIN_TRANS_GEN_NSEC)+1;
    srand((unsigned) time(&t)*getpid()*Budget);
        
    shmid = shmget(SHM_KEY, sizeof(Struttura_Stampa), 0);
    datiNodi = (Struttura_Stampa *)shmat(shmid,NULL,0);
    semid = semget(1000, 2, S_IRUSR | S_IWUSR);
    shmid_table = shmget(SHM_TABLE, sizeof(int)*(SO_NODES_NUM), 0);
    shmid_user =    shmget(SHM_USER, sizeof(int)*(SO_USERS_NUM), 0);
    T = shmat(shmid_table, NULL, 0);
    U = shmat(shmid_user, NULL, 0);
    tim.tv_sec = 0;
    tim.tv_nsec = rand() % timerand + SO_MIN_TRANS_GEN_NSEC;
    
    /*signal(SIGKILL, handler_child);*/
    

    while(Try < SO_RETRY){

        if(Budget >= 2){
            Try = 0;
            reserveSem(semid,0);

            msgid = msgget((pid_t)T[rand() % SO_NODES_NUM],0777);
            while(msgid < 0){
                msgid = msgget((pid_t)T[rand() % SO_NODES_NUM],0777);
            }

                    if( clock_gettime( CLOCK_REALTIME, &STAMP) == -1 ) {
                        perror( "clock gettime" );
                        exit( EXIT_FAILURE );
                    }

                    timeTransf = STAMP.tv_sec + (STAMP.tv_nsec*pow(10, -9));
                    msg.Timestamp =  timeTransf;
                    msg.sender = getpid();

                    do
                    {
                        Random = (pid_t)U[rand() % SO_USERS_NUM];
                    }while(Random == getpid());

                    msg.reciver = Random;

                    Trasfer = rand() % (Budget-2)+2;

                    Reward = ((float)Trasfer/100)*SO_REWARD;
                    if(Reward < 1){Reward = 1;}
                    if((Reward - (int)Reward) >= 0.5){
                        Reward = (int)Reward + 1;
                    }
                    else{
                        Reward = (int)Reward;
                    }

                    msg.transfer = Trasfer - Reward;


                    msg.reward = Reward;

                    
                    msgsend=msgsnd(msgid, &msg,sizeof(msg),IPC_NOWAIT);

                    if( msgsend < 0){
                        Try++;
                    while (msgsend < 0)
                    {
                        msgsend=msgsnd(msgid, &msg,sizeof(msg),IPC_NOWAIT);
                        if(msgsend < 0){
                            Try++;
                        }
                        if(Try >= SO_RETRY){
                            printf("Uccisione\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                        Try=0;
                    }
                
                releaseSem(semid,1);

                Budget = Budget - Trasfer;
                releaseSem(semid,0);
            nanosleep(&tim, &tim2);
        }
        else{
            Try++;
        }


        /**/
    }

    exit(EXIT_FAILURE);
    /*dati->MatrixUsers[atoi(argv[1])][2] = 1;*/
        
}