#include <time.h>

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>

using namespace std;

typedef struct {
  string letra;
  int prioridade;
  int tempo;
  string descricao;
} info;

list<info> filas;
int i = 0;

void retirar_senha(int &num) {
  num = 1;
  cout << "RETIRE A SUA SENHA: " << endl;
  for (auto iterador = filas.begin(); iterador != filas.end(); iterador++) {
    info saida = *iterador;
    cout << num << " - " << saida.letra << endl;
    num++;
  }
  cin >> num;
}

void leitura_de_dados(string texto) {
  info x;
  queue<string> dados;
  int pos1 = 0;
  int pos2 = 0;
  while (1) {
    pos1 = texto.find_first_not_of(",", pos2);
    pos2 = texto.find_first_of(",", pos1 + 1);
    if (pos2 == string::npos) {
      dados.push(texto.substr(pos1));
      break;
    } else if (pos2 != string::npos) {
      dados.push(texto.substr(pos1, pos2 - pos1));
    }
  }
  x.letra = dados.front();
  dados.pop();
  x.prioridade = stoi(dados.front());
  dados.pop();
  x.tempo = stoi(dados.front());
  dados.pop();
  x.descricao = dados.front();
  dados.pop();
  i++;
  filas.push_back(x);
}

int main(int argc, char *argv[]) {
  ifstream arq(argv[1]);
  int opcao = 1;
  if (!arq.is_open()) {
    cout << "ARQUIVO INVALIDO OU INEXISTENTE" << endl;
    exit(1);
  }
  string tipo;
  while (getline(arq, tipo)) leitura_de_dados(tipo);

  retirar_senha(opcao);

  while (opcao > filas.size() || opcao < 0) {
    cout << "OPCAO INVALIDA" << endl;
    retirar_senha(opcao);
  }
}
