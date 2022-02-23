#include "includer.h"

void Utenti(int i, int *T, int semid, char str[]){

    int pid;

        for( i = 0; i < SO_USERS_NUM; i++){
        switch(pid = fork()){
        case 0: /*figlio*/
            reserveSem(semid,1);
            sprintf(str, "%d", i);
            execlp("./Utente", "./Utente", str);
            break;
        default: /*padre*/
            T[i] = pid;
            T[i+SO_USERS_NUM] = 0;
            break;
        }

    }
}

void Nodi(int z, int *T, int semid, char str[]){

int pid;
        for( z = (SO_USERS_NUM*2); z < (SO_USERS_NUM*2)+SO_NODES_NUM; z++){
        switch(pid = fork()){
        case 0: /*figlio*/
            sprintf(str, "%d", z);
            reserveSem(semid,1);
            execlp("./Nodo", "./Nodo", str);
            break;
        default: /*padre*/
            T[z] = pid;
            /*T[z+SO_USERS_NUM] = 0;*/
            break;
        }
    }

}