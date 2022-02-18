#include "headerData.h"

typedef struct LibroMastro {
  long LibroMastro[5][SO_REGISTRY_SIZE*SO_BLOCK_SIZE];
} data1;

typedef struct MatrixNodes {
  int PID[SO_NODES_NUM];
  int Wallet[SO_NODES_NUM];
  int TransactionPool[SO_NODES_NUM];
} data2;