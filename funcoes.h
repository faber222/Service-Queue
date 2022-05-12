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

// funcao usada para capturar o possivel valor de opcao, e tambem printar na
// tela as senhas disponiveis, baseando apenas na letra e o numero
// correspondente para ser selecionado
void retirar_senha(int &num) {
  int x = 1;
  cout << "+-----------------------------------------------+" << endl;
  cout << "|               RETIRE A SUA SENHA:             |" << endl;

  // funcao que vai percorrer a lista de estruturas principal, e armazenar cada
  // valor da estrutura em uma nova estrutura chamada saida, visto que como
  // estamos iterando a lista em si, o valor dela não pode ser usado para
  // printar na tela, por isso armazenamos cada iterador em uma nova lista de
  // estrutura chamada saida, e a partir dela, printamos o valor na tela
  for (auto iterador = filas.begin(); iterador != filas.end(); iterador++) {
    info saida = *iterador;
    cout << "+-----------------------------------------------+" << endl;
    cout << "|                     " << x << " - " << saida.letra
         << "                     |" << endl;
    x++;
  }
  cout << "+-----------------------------------------------+" << endl;
  cout << "|          PARA CHAMAR ALGUEM, DIGITE 0         |" << endl;
  cout << "+-----------------------------------------------+" << endl;
  cout << "                  SUA OPCAO: ";
  cin >> num;
  cout << endl;
}

// a funcao leitura_de_dados nada mais é que um separador que usa como parametro
// a virgula, que contem em montes no arquivo csv. Ao mesmo tempo, ele pega os
// dados separados e armazena em duas listas de estruturas, a x e a y. Sendo que
// os valores da separação dos dados do arquivo csv, vao ser armazenados na fila
// chamada dados. Sendo que no final do loop, o valor de dados.front() é
// armazenado igualitariamente nas listas x e y
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
  // o valor da variavel tempo é multiplicada por 60 para termos uma comparacao
  // em segundos, visto que nosso codigo usa a funcao tempo, que conta a espera
  // em segundos e nos da uma diferenca em segundos, porem no codigo passamos o
  // valor em minutos
  x.tempo = stoi(dados.front()) * 60;
  dados.pop();
  x.descricao = dados.front();
  dados.pop();
  // no fim, armazenamos as duas listas x e y nas listas principais, filas e
  // senhas
  // a separacao em duas listas, serve para que possamos criar um contador de
  // numero de senhas fornecidas sem alterar a original, exeplo, A1/A2/A3/.../An
  filas.push_back(x);
  senhas.push_back(y);
}

#endif  // PROJETO1