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

int i = 0;

int tempo() {
  time_t t = time(NULL);
  return t;
}

bool comp_prioridade(const info2 &d1, const info2 &d2) {
  return d1.prioridade < d2.prioridade;
}

void chamar_cliente() {
  bool continuar = true;
  info2 verificacao;
  info2 comparacao;
  cout << "PROXIMO: ";
  for (auto it = clientes.begin(); it != clientes.end(); it++) {
    verificacao = *it;
    if ((tempo() - verificacao.tempo_chegada) >= verificacao.tempo_maximo) {
      cout << verificacao.letra << verificacao.senha << " - "
           << verificacao.descricao << endl
           << endl
           << endl;
      clientes.erase(it);
      continuar = false;
      break;
    }
  }
  if (continuar == true) {
    list<info2> ordenada;
    ordenada = clientes;
    ordenada.sort(comp_prioridade);
    verificacao = ordenada.front();
    for (auto d = clientes.begin(); d != clientes.end(); d++) {
      comparacao = *d;
      if (comparacao.senha == verificacao.senha &&
          comparacao.letra == verificacao.letra) {
        cout << verificacao.letra << verificacao.senha << " - "
             << verificacao.descricao << endl
             << endl
             << endl;
        d = clientes.erase(d);
      }
    }
  }
}

info2 adicionar_cliente(int classificacao) {
  info dados;
  int j = 1;
  for (auto x = filas.begin(); x != filas.end(); x++) {
    if (j == classificacao) {
      dados = *x;
      break;
    }
    j++;
  }
  info2 armazenar;
  senha_cliente pesquisar;
  int senha_atual;
  armazenar.letra = dados.letra;
  armazenar.prioridade = dados.prioridade;
  armazenar.tempo_chegada = tempo();
  armazenar.tempo_maximo = dados.tempo;
  armazenar.descricao = dados.descricao;
  for (auto b = senhas.begin(); b != senhas.end(); b++) {
    pesquisar = *b;
    if (pesquisar.letra == armazenar.letra) {
      senha_atual = pesquisar.senha + 1;
      pesquisar.senha = senha_atual;
      *b = pesquisar;
      break;
    }
  }
  armazenar.senha = senha_atual;
  clientes.push_back(armazenar);
  return armazenar;
}

void retirar_senha(int &num) {
  num = 1;
  cout << "+-----------------------------------------------+" << endl;
  cout << "|               RETIRE A SUA SENHA:             |" << endl;
  for (auto iterador = filas.begin(); iterador != filas.end(); iterador++) {
    info saida = *iterador;
    cout << "+-----------------------------------------------+" << endl;
    cout << "|                     " << num << " - " << saida.letra
         << "                     |" << endl;
    num++;
  }
  cout << "+-----------------------------------------------+" << endl;
  cout << "|          PARA CHAMAR ALGUEM, DIGITE 0         |" << endl;
  cout << "+-----------------------------------------------+" << endl;
  cout << "                  SUA OPCAO: ";
  cin >> num;
  cout << endl;
}

void leitura_de_dados(string texto) {
  info x;
  senha_cliente y;
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
  y.letra = dados.front();
  dados.pop();
  x.prioridade = stoi(dados.front());
  dados.pop();
  x.tempo = stoi(dados.front()) * 60;
  dados.pop();
  x.descricao = dados.front();
  dados.pop();
  i++;
  filas.push_back(x);
  senhas.push_back(y);
}

#endif  // PROJETO1