#ifndef PROJETO1
#define PROJETO1

#include <time.h>

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>

#include "struct.h"

using namespace std;

int tempo();

bool comp_prioridade(const info_dados2 &d1, const info_dados2 &d2);

void chamar_cliente();

info_dados2 adicionar_cliente(int classificacao);

void retirar_senha(int &num);

void leitura_de_dados(string texto);

#endif  // PROJETO1
