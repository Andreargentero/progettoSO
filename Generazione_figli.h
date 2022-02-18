#include "includer.h"

void Utenti(int i, pid_t pid, int semid, char str[]){

        for( i = 0; i < SO_USERS_NUM; i++){
        switch(pid = fork()){
        case 0:
            reserveSem(semid,1);
            sprintf(str, "%d", i);
            execlp("./Utente", "./Utente", str);
            break;
        default:
            break;
        }

    }
}

void Nodi(int z, pid_t pid, int semid, char str[]){

        for( z = 0; z < SO_NODES_NUM; z++){
        switch(fork()){
        case 0:
            sprintf(str, "%d", z);
            reserveSem(semid,1);
            execlp("./Nodo", "./Nodo", str);
            break;
        default:
            break;
        }
    }

}