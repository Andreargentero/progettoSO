#include "headerData.h"

typedef struct LibroMastro {
  long LibroMastro[SO_REGISTRY_SIZE];
} data1;

typedef struct {
  int PID[SO_NODES_NUM];
  int Wallet[SO_NODES_NUM];
  int TransactionPool[SO_NODES_NUM];

} Struttura_Stampa;