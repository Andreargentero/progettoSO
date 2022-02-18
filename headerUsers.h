#include "headerLIB.h"

int wallet;
int Nid;
pid_t pid;
struct LibroMastro *dati;

void SetWallet(int budget);
void SetPid(pid_t id);

void Users(int i,int budget, pid_t id){

    int shmid = shmget(SHM_KEY, sizeof(struct LibroMastro), 0);
    dati = (struct LibroMastro *)shmat(shmid,NULL,0);

    Nid = i;
    SetWallet(budget);
    SetPid(id);

}

void SetWallet(int budget){

    wallet = budget;
    dati->MatrixUsers[Nid][1] = budget;

}

void SetPid(pid_t id){
    pid = id;
    dati->MatrixUsers[Nid][0] = id;
}

int GetWallet(){
    return wallet;
}

pid_t GetPid(){
    return pid;
}