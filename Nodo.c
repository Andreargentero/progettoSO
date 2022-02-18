#include "includer.h"

/*void handler_nodes(int s){

        shmdt(dati);
        shmctl(shmid, 0, IPC_RMID);

}*/

int main(int argc, char** argv){

    struct LibroMastro *dati;
    struct MatrixNodes *datiNodi;
    
    int msgid,shmid;
    time_t t;
    int i,j;
    int timerand = (SO_MAX_TRANS_PROC_NSEC-SO_MIN_TRANS_PROC_NSEC)+1;
    long block[5][SO_BLOCK_SIZE];
    long msg_to_rec = 0;

    struct timespec tim, tim2;
    struct my_msg Transaction;

    /*signal(SIGKILL, handler_nodes);*/

    srand((unsigned) time(&t)*getpid()/*aggiungere portafoglio*/);

    tim.tv_sec = 0;
    tim.tv_nsec = rand() % timerand + SO_MIN_TRANS_PROC_NSEC;
    msgid = msgget(getpid(), IPC_CREAT| 666);
    shmid = shmget(SHM_KEY, sizeof(struct MatrixNodes), 0);
    datiNodi = (struct MatrixNodes *)shmat(shmid,NULL,0);

    datiNodi->PID[atoi(argv[1])] = getpid();

    while(1){

            block[0][0] = 0/*timestamp*/;
            block[1][0] = -1 /*Sender*/;
            block[2][0] = getpid()/*Reciver*/;
            block[3][0] = 0/*Transfer*/;
            block[4][0] = 0/*Reward*/;

        i=1;

            while(i != SO_BLOCK_SIZE-1){
                msgrcv(msgid, (void *)&Transaction, BUFSIZ, msg_to_rec, 0);
                /*block[0][i] = Transaction.Timestamp;
                block[1][i] = Transaction.sender;
                block[2][i] = Transaction.reciver;
                block[3][i] = Transaction.transfer;
                block[4][i] = Transaction.reward;
                SetWalletNodes(Transaction.reward);*/

                block[0][i] = Transaction.some_text[0];
                /*printf("%d\n", block[0][i]);*/
                /*printf("\n%d, %d", GetPidNodes(), GetWalletNodes());*/
                i++;
            }


        nanosleep(&tim, &tim2);

        /*SetTransaction_pool(GetTransaction_pool()-GetBlock_size());*/

        j = 0;

            while(j != SO_BLOCK_SIZE-1){
                dati -> LibroMastro[0][0/**/] = 0;
            }

 
    }

}