#include <time.h>

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>

#include "funcoes.h"
#include "struct.h"

using namespace std;

int main(int argc, char *argv[]) {
  ifstream arq(argv[1]);
  info2 adicionado;
  int opcao = 1;
  if (!arq.is_open()) {
    cout << "ARQUIVO INVALIDO OU INEXISTENTE" << endl;
    exit(1);
  }

  string tipo;
  while (getline(arq, tipo)) leitura_de_dados(tipo);

  while (1) {
    retirar_senha(opcao);
    while (opcao > filas.size() || opcao < 0) {
      cout << "OPCAO INVALIDA" << endl;
      retirar_senha(opcao);
    }

    if (opcao == 0) {
      if (!clientes.empty()) {
        chamar_cliente();
        continue;
      } else
        cout << "A FILA ESTA VAZIA" << endl << endl;
      continue;
    }
    adicionado = adicionar_cliente(opcao);
    cout << "SUA SENHA PARA ATENDIMENTO: ";
    cout << adicionado.letra << adicionado.senha << " - "
         << adicionado.descricao << endl
         << endl;
  }
}
