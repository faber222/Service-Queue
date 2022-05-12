#include <time.h>

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>

// includes referentes as "bibliotecas" de funcao e struturas
#include "funcoes.h"
#include "struct.h"

using namespace std;

int main(int argc, char *argv[]) {
  // faz a leitura do arquivo passado como primeiro argumento de linha de
  // comando
  ifstream arq(argv[1]);
  info2 adicionado;
  int opcao = 1;
  // verifica se o arquivo passado foi aberto com sucesso ou se é um arquivo
  // valido, se não for, fecha o programa
  if (!arq.is_open()) {
    cout << "ARQUIVO INVALIDO OU INEXISTENTE" << endl;
    exit(1);
  }
  // faz a captura linha por linha dos dados do arquivo .csv
  string tipo;
  while (getline(arq, tipo)) leitura_de_dados(tipo);

  // menu que executa as chamadas principais, tais quais, retirar_senha,
  // chamar_cliente e adicionar_cliente

  while (1) {
    // retirar senha recebe como parametro a variavel inteira opcao, que é
    // vazia, e depois de passar pela função, ela deve retornar um valor acima
    // de 0,
    retirar_senha(opcao);

    // se o valor de opcao for maior que o valor da fila, que é definido pelo
    // numero de linhas; ou a opcao for menor que 0. Ele retorna uma mensagem de
    // valor invalido e executa a funcao novamente para receber um valor valido
    // FICA O ADENDO QUE FILA, REPRESENTA O NOME DE UMA LISTA
    while (opcao > filas.size() || opcao < 0) {
      cout << "OPCAO INVALIDA" << endl;
      retirar_senha(opcao);
    }
    // se a opcao for igual a 0, ele vai chamar a funcao chamar_clientes e ir
    // pegando as pessoas da fila, e isso não vai encerrar o codigo, e por isso
    // o codigo continue esta presente.
    // FICA O ADENDO QUE FILA, REPRESENTA O NOME DE UMA LISTA
    if (opcao == 0) {
      if (!clientes.empty()) {
        chamar_cliente();
        continue;
      } else
        cout << "A FILA ESTA VAZIA" << endl << endl;
      continue;
    }
    // apos o valor de opcao ser preenchido, ele é enviado para a função
    // adicionar clientes, no qual vai retornar um valor, que vai ser salvo na
    // estrutura chamada adicionado, referente aos clientes que foram
    // adicionados a fila, consequentemente, vai printar na tela o codigo da
    // chamada, senha, e a descricao, exemplo  A5 - Consulta a contrato
    // FICA O ADENDO QUE FILA, REPRESENTA O NOME DE UMA LISTA
    adicionado = adicionar_cliente(opcao);
    cout << "SUA SENHA PARA ATENDIMENTO: ";
    cout << adicionado.letra << adicionado.senha << " - "
         << adicionado.descricao << endl
         << endl;
  }
}
