#include <sys/time.h>
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
  int count = 1;
} info;

struct senhas {
  string cod_Senha;
  int horario;
};

struct dados_cliente {
  info classe;
  senhas senha;
};

list<info> filas2;
list<dados_cliente> classe;
list<dados_cliente> filas;

void gerar_senha(dados_cliente dados) {
  cout << dados.classe.letra << dados.classe.descricao << endl;
  for (auto &x : classe) {
    if (x.classe.letra == dados.classe.letra) {
      dados.classe.count++;
    }
  }
  dados.senha.cod_Senha = dados.classe.letra + to_string(dados.classe.count);
  timeval chegada;
  gettimeofday(&chegada, NULL);
  dados.senha.horario = chegada.tv_sec;

  cout << "-------------------------------------------------" << endl;
  cout << "Sua senha é: " << dados.senha.cod_Senha << endl;
  cout << "-------------------------------------------------" << endl;

  classe.push_back(dados);
}

void tempo_de_espera() {}

void retirar_senha(string &num) {
  int j = 1;
  cout << "RETIRE A SUA SENHA: " << endl;
  for (auto iterador = filas2.begin(); iterador != filas2.end(); iterador++) {
    info saida = *iterador;
    cout << " - " << saida.letra << endl;
    j++;
  }
  cin >> num;

  for (auto &dados_aux : filas) {
    if (num == dados_aux.classe.letra) {
      gerar_senha(dados_aux);
    }
  }
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
  // i++;
  filas2.push_back(x);
}

int main(int argc, char *argv[]) {
  ifstream arq(argv[1]);
  string opcao;
  if (!arq.is_open()) {
    cout << "ARQUIVO INVALIDO OU INEXISTENTE" << endl;
    exit(1);
  }
  string tipo;
  while (getline(arq, tipo)) leitura_de_dados(tipo);

  retirar_senha(opcao);

  /*
while (opcao > filas.size() || opcao <= 0) {
  cout << "OPCAO INVALIDA" << endl;
  retirar_senha(opcao);
}
*/
}
