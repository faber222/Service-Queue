#include "funcoes.h"

#include <time.h>

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>

using namespace std;

// tempo é a funcao que vai fazer a captura do tempo local da maquina, que vai
// ser usada para delimitar o tempo na fila de espera do cliente
int tempo() {
  time_t t = time(NULL);
  return t;
}
// teste para fazer o ordenamento da lista baseado na prioridade de atendimento
bool comp_prioridade(const info_dados2 &d1, const info_dados2 &d2) {
  return d1.prioridade < d2.prioridade;
}

// a funcao chamar clientes nao recebe nenhum parametro inicial e nem retorna
// nada, visto que ela é a funcao principal do atendente, aonde ela apenas faz a
// captura dos dados armazenados na lista principal, chamada info_dados2
// primeiro é feita a verificacao dos clientes que tem o tempo de atendimento
// superior ao descrito no arquivo csv, e depois de fazer a verificacao, se for
// falso, chama o primeiro cliente que tem o tempo vencido e o exclui da
// lista. Caso seja verdadeiro, ele executa a chamada de funcao sem verificacao
// de tempo, e chama um cliente de cada vez da fila de prioridade
void chamar_cliente() {
  bool continuar = true;
  info_dados2 verificacao;
  info_dados2 comparacao;
  cout << "PROXIMO: ";
  for (auto it = clientes.begin(); it != clientes.end(); it++) {
    verificacao = *it;
    // compara com o tempo atual - o tempo de chegada, e se esse tempo for maior
    // que o tempo maximo definido baseado nos dados do arquivo csv, chama o
    // cliente da lista
    if ((tempo() - verificacao.tempo_chegada) >= verificacao.tempo_maximo) {
      cout << verificacao.letra << verificacao.senha << " - "
           << verificacao.descricao << endl
           << endl;
      clientes.erase(it);
      continuar = false;
      break;
    }
  }
  // se for verdadeiro, ele vai chamar os clientes da lista, porem antes vai
  // chamar a funcao comp_prioridade, no qual vai fazer o ordenamento dos
  // clientes que chegaram, para armazenar na lista ordenada, que posteriormente
  // vai ser feito a chamada baseado nessa lista
  if (continuar == true) {
    list<info_dados2> ordenada;
    ordenada = clientes;
    ordenada.sort(comp_prioridade);
    verificacao = ordenada.front();
    for (auto it = clientes.begin(); it != clientes.end(); it++) {
      comparacao = *it;
      if (comparacao.senha == verificacao.senha &&
          comparacao.letra == verificacao.letra) {
        cout << verificacao.letra << verificacao.senha << " - "
             << verificacao.descricao << endl
             << endl;
        it = clientes.erase(it);
      }
    }
  }
}

// na funcao adicionar_clientes, o valor classificacao serve para definir em
// qual fila de atendimento o cliente vai ser encaixar
// fazemos a iteracao da fila_clientes e buscamos dentro dela o valor que seja
// igual ao nosso valor classificacao
// e quando encontrarmos, e for igual, armazenamos em uma variavel local chamada
// dados, que servira para podermos trabalhar sem alterar os dados originais
// apos ter a funcao dados toda preenchida, pegamos e criamos outras duas listas
// de estruturas locais
// que vamos usar para armazenar os dados obtidos da variavel dados, como
// dados.letra, dados.prioridade, etc
info_dados2 adicionar_cliente(int classificacao) {
  info_dados dados;
  int j = 1;
  for (auto x = filas_clientes.begin(); x != filas_clientes.end(); x++) {
    if (j == classificacao) {
      dados = *x;
      break;
    }
    j++;
  }
  info_dados2 armazenamento_local;
  senha_cliente pesquisar;
  int senha_atual;
  armazenamento_local.letra = dados.letra;
  armazenamento_local.prioridade = dados.prioridade;
  armazenamento_local.tempo_chegada = tempo();
  armazenamento_local.tempo_maximo = dados.tempo;
  armazenamento_local.descricao = dados.descricao;

  // esse iterador vai ser usado para encontrar os valores de senha para que
  // possamos contabilizar a quantidade de clientes que chegam e sao armazenados
  // na lista
  for (auto b = senhas.begin(); b != senhas.end(); b++) {
    pesquisar = *b;
    if (pesquisar.letra == armazenamento_local.letra) {
      senha_atual = pesquisar.senha + 1;
      pesquisar.senha = senha_atual;
      *b = pesquisar;
      break;
    }
  }
  // no fim da funcao, jogamos todos os valores coletados para dentro de uma
  // lista, chamada clientes e ao mesmo tempo retornamos o valor de
  // armazenamento local para a funcao main
  armazenamento_local.senha = senha_atual;
  clientes.push_back(armazenamento_local);
  return armazenamento_local;
}

// funcao usada para capturar o possivel valor de opcao_escolhida, e tambem
// printar na tela as senhas disponiveis, baseando apenas na letra e o numero
// correspondente para ser selecionado
void retirar_senha(int &num) {
  string entrada_teclado;

  int x = 1;
  cout << "+-----------------------------------------------+" << endl;
  cout << "|               RETIRE A SUA SENHA:             |" << endl;

  // funcao que vai percorrer a lista de estruturas principal, e
  // armazenamento_local cada valor da estrutura em uma nova estrutura chamada
  // saida, visto que como estamos iterando a lista em si, o valor dela não pode
  // ser usado para printar na tela, por isso armazenamos cada iterador em uma
  // nova lista de estrutura chamada saida, e a partir dela, printamos o valor
  // na tela
  for (auto iterador = filas_clientes.begin(); iterador != filas_clientes.end();
       iterador++) {
    info_dados saida = *iterador;

    cout << "+-----------------------------------------------+" << endl;
    cout << "             " << x << " - " << saida.letra << " "
         << saida.descricao << "                     " << endl;
    x++;
  }
  cout << "+-----------------------------------------------+" << endl;
  cout << "          PARA CHAMAR ALGUEM, DIGITE 0         " << endl;
  cout << "+-----------------------------------------------+" << endl;
  cout << "                  SUA OPCAO: ";

  getline(cin, entrada_teclado);
  if (entrada_teclado.find_first_not_of("0123456789") != string::npos)
    num = filas_clientes.size() + 1;
  else if (!entrada_teclado.empty()) {
    num = stoi(entrada_teclado);
  } else {
    num = filas_clientes.size() + 1;
  }
  cout << endl;
}

// a funcao leitura_de_dados nada mais é que um separador que usa como parametro
// a virgula, que contem em montes no arquivo csv. Ao mesmo tempo, ele pega os
// dados separados e armazena em duas listas de estruturas, a x e a y. Sendo que
// os valores da separação dos dados do arquivo csv, vao ser armazenados na fila
// chamada dados. Sendo que no final do loop, o valor de dados.front() é
// armazenado igualitariamente nas listas x e y
void leitura_de_dados(string texto) {
  info_dados x;
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
  // no fim, armazenamos as duas listas x e y nas listas principais,
  // filas_clientes e senhas a separacao em duas listas, serve para que possamos
  // criar um contador de numero de senhas fornecidas sem alterar a original,
  // exeplo, A1/A2/A3/.../An
  filas_clientes.push_back(x);
  senhas.push_back(y);
}