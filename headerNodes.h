#include "headerLIB.h"

int Transaction_pool;
int Block_size;
int Wallet;
pid_t pid;
int Nid;
struct LibroMastro *dati;

void SetTransaction_pool(int Pool);
void SetBlock_size(int Size);
void SetWalletNodes(int budget);
void SetPidNodes(pid_t id);

void Nodes(int z, int Pool, int Size, int budget, pid_t id){

    int shmid = shmget(SHM_KEY, sizeof(struct LibroMastro), 0);
    dati = (struct LibroMastro *)shmat(shmid,NULL,0);

    Nid = z;
    SetTransaction_pool(Pool);
    SetBlock_size(Size);
    SetWalletNodes(budget);
    SetPidNodes(id);

}

void SetTransaction_pool(int Pool){

    Transaction_pool = Pool;
    dati->MatrixNodes[Nid][2] = Transaction_pool;

}

void SetBlock_size(int Size){

    Block_size = Size;

}

void SetWalletNodes(int budget){

    Wallet = budget;
    dati->MatrixNodes[Nid][1] = budget;

}

void SetPidNodes(pid_t id){
    pid = id;
    dati->MatrixNodes[Nid][0] = getpid();
}

int GetTransaction_pool(){
    return Transaction_pool;
}

int GetBlock_size(){
    return Block_size;
}

int GetWalletNodes(){
    return Wallet;
}

pid_t GetPidNodes(){
    return pid;
}