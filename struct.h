#ifndef PROJETO1_2
#define PROJETO1_2

#include <time.h>

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>

#include "funcoes.h"

using namespace std;

typedef struct {
  int prioridade;
  int senha = 0;
  string letra;
  time_t tempo;
  string descricao;
} info;

typedef struct {
  int prioridade;
  int senha;
  string letra;
  time_t tempo_maximo;
  time_t tempo_chegada;
  string descricao;
} info2;

typedef struct {
  int senha = 0;
  string letra;
} senha_cliente;

list<info> filas;
list<info2> clientes;
list<senha_cliente> senhas;
// FICA O ADENDO QUE FILA, REPRESENTA O NOME DE UMA LISTA

#endif  // PROJETO1_2