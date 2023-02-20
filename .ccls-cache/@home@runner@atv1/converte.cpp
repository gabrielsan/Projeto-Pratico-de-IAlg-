/*#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct farmacia {
  long int codigo;
  char preco[9];
  char nome[100];
  char estado[9];
  char situacao[9];
};

int main() {

  ofstream baseBin("base.dat", ios::binary); // abrir arquivo em modo binário
  ifstream base("base.csv");
  farmacia produto;

  string input;

  while (getline(base, input)) {

    sscanf(input.c_str(), "%ld;%9[^;];%99[^;];%8[^;];%8s", &produto.codigo,
           produto.preco, produto.nome, produto.estado, produto.situacao);
    baseBin.write((const char *)&produto, sizeof(farmacia));
    cout << produto.codigo << " " << produto.preco << " " << produto.nome << " "
         << produto.estado << " " << produto.situacao << "\n ";
  }

  return 0;
}*/