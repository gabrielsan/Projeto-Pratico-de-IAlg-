#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
// declaração da estrutura
struct farmacia {
  long int codigo;
  char preco[9];
  char nome[100];
  char estado[9];
  char situacao[9];
};
// guarda as informações da base no vetor de estrutura
void guarda(farmacia produto[]) {
  fstream lendo("base.dat");
  int i = 0;
  while (lendo.read((char *)&produto[i], sizeof(farmacia))) {
    i++;
  }
}
// insere uma informação no vetor de struct
void inserir(farmacia vet[], int inicio, int tam) {
  string aux;
  farmacia *novo = new farmacia[tam + 1];
  bool achei = false;
  // insere em uma posição demarcada excluida
  for (int i = inicio; i < tam; i++) {
    if (-1 == vet[i].codigo) {
      cin >> vet[i].codigo;
      cin >> vet[i].preco;
      getline(cin, aux);
      strcpy(novo[tam].nome, aux.c_str());
      cin >> vet[i].estado;
      cin >> vet[i].situacao;
      achei = true;
    }
  }
  if (!achei) {
    copy(vet, vet + tam, novo);
    // insere em uma posição nova

    cin >> novo[tam].codigo;
    cin >> novo[tam].preco;
    getline(cin, aux);
    strcpy(novo[tam].nome, aux.c_str());
    cin >> novo[tam].estado;
    cin >> novo[tam].situacao;
    vet = novo;
    delete[] novo;
  }
}
// armazena os valores do vetor no arquivo binario
/*void armazena(farmacia vet[], int inicio, int tam) {
  ofstream baseBin("base.dat", ios::binary);
  for (int i = inicio; i < tam; i++) {
    baseBin.write((const char *)&vet[i], sizeof(farmacia));
  }
}*/
// exxclui logicamente um valor do vetor de estrutura
void excluir(farmacia vet[], int inicio, int tam, long int codigo) {
  bool achei = false;
  for (int i = inicio; i < tam; i++) {
    if (codigo == vet[i].codigo) {
      vet[i].codigo = -1;
      achei = true;
      cout << "Excluido!!!" << endl;
    }
  }
  if (!achei) {
    cout << "codigo não existente" << endl;
  }
}
// mostra o vetor inteiro
void mostraTudo(farmacia produto[]) {
  for (int j = 0; j < 1000; j++) {
    cout << produto[j].codigo << " " << produto[j].preco << " "
         << produto[j].nome << " " << produto[j].estado << " "
         << produto[j].situacao << "\n ";
  }
}
// mostra um intervalo inserido pelo usuario
void mostraIntervalo(farmacia produto[], int inicio, int fim) {
  for (int i = inicio; i < fim; i++) {
    cout << produto[i].codigo << " " << produto[i].preco << " "
         << produto[i].nome << " " << produto[i].estado << " "
         << produto[i].situacao << "\n ";
  }
}
// ordena o vetor pelo campo codigo
void ordenaCodigo(farmacia produto[], int primeiro, int ultimo) {
  int i = primeiro;
  int j = ultimo;
  long int pivo = produto[(i + j) / 2].codigo;

  while (i <= j) {

    while (produto[i].codigo < pivo)
      i++;

    while (produto[j].codigo > pivo)
      j--;

    // Troca as informacoes de todos os atributos nas posicoes I e J
    // Garante integridade dos dados
    if (i <= j) {
      swap(produto[i].codigo, produto[j].codigo);
      swap(produto[i].preco, produto[j].preco);
      swap(produto[i].nome, produto[j].nome);
      swap(produto[i].estado, produto[j].estado);
      swap(produto[i].situacao, produto[j].situacao);

      i++;
      j--;
    }
  }

  // Recursivamente chama a função para as partes não ordenadas do vetor
  if (primeiro < j)
    ordenaCodigo(produto, primeiro, j);
  if (i < ultimo)
    ordenaCodigo(produto, i, ultimo);
}
// ordena o vetor pelo campo Preco
void ordenaPreco(farmacia produto[], int primeiro, int ultimo) {
  int i = primeiro;
  int j = ultimo;
  string pivo =
      produto[(i + j) / 2].preco; // mudança: agora o pivo é uma string

  while (i <= j) {

    while (produto[i].preco < pivo) // mudança: agora estamos comparando strings
      i++;

    while (produto[j].preco > pivo) // mudança: agora estamos comparando strings
      j--;

    // Troca as informacoes de todos os atributos nas posicoes I e J
    // Garante integridade dos dados
    if (i <= j) {
      swap(produto[i].codigo, produto[j].codigo);
      swap(produto[i].preco, produto[j].preco);
      swap(produto[i].nome, produto[j].nome);
      swap(produto[i].estado, produto[j].estado);
      swap(produto[i].situacao, produto[j].situacao);

      i++;
      j--;
    }
  }

  // Recursivamente ordena as duas metades do vetor
  if (primeiro < j) {
    ordenaPreco(produto, primeiro, j);
  }
  if (i < ultimo) {
    ordenaPreco(produto, i, ultimo);
  }
}
// busca uma posição inserida pelo usuario pelo campo codigo
int buscaCodigo(farmacia vet[], int comeco, int fim, long int x) {
  if (fim >= comeco) {
    int meio = comeco + (fim - comeco) / 2;
    if (vet[meio].codigo == x)
      return meio;
    if (vet[meio].codigo > x)
      return buscaCodigo(vet, comeco, meio - 1, x);
    return buscaCodigo(vet, meio + 1, fim, x);
  }
  return -1;
}
// busca uma posicao inserida pelo usuario pelo campo preco
int buscaPreco(farmacia vet[], int comeco, int fim, char preco[]) {
  if (fim >= comeco) {
    int meio = comeco + (fim - comeco) / 2;
    if (strcmp(vet[meio].preco, preco) == 0)
      return meio;
    if (strcmp(vet[meio].preco, preco) > 0)
      return buscaPreco(vet, comeco, meio - 1, preco);
    return buscaPreco(vet, meio + 1, fim, preco);
  }
  return -1;
}
// imprime o menu
void imprimeMenu() {
  cout << "MENU:" << endl;
  cout << "1. Inserir" << endl;
  cout << "2. Deletar" << endl;
  cout << "3. Mostrar" << endl;
  cout << "4. Ordenar" << endl;
  cout << "5. Buscar" << endl;
  cout << "6. Sair" << endl;
  cout << "Digite a opção desejada: ";
}

int main() {

  fstream lendo("base.dat");
  int tam = 1000, opcao, mostra, n1, n2;
  long int codigo;
  char preco[9];

  long int valor;
  farmacia *produto = new farmacia[tam];
  guarda(produto);
  do {
    system("clear");
    imprimeMenu();
    cin >> opcao;

    switch (opcao) {
    case 1:
      system("clear");
      cout << "Insira os valores" << endl;
      inserir(produto, 0, tam);
      break;
    case 2:
      system("clear");
      cin >> valor;
      excluir(produto, 0, tam, valor);

      break;
    case 3:
      system("clear");
      cout << "mostrar o vetor todo ou somente um intervalo: 1 ou 2" << endl;
      cin >> mostra;
      if (mostra == 1) {
        mostraTudo(produto);
        system("read -p \"Pressione enter para sair\" saindo");
      } else {
        cout << "insira o intervalo" << endl;
        cin >> n1 >> n2;
        mostraIntervalo(produto, n1, n2);
        system("read -p \"Pressione enter para sair\" saindo");
      }

      break;
    case 4:
      system("clear");
      cout << "ordenar pelo preço ou pelo codigo: 1 ou 2" << endl;
      cin >> mostra;
      if (mostra == 1) {
        ordenaPreco(produto, 0, tam);
      } else {
        ordenaCodigo(produto, 0, tam);
      }
      system("read -p \"Pressione enter para sair\" saindo");
      break;
    case 5:
      system("clear");
      cout << "buscar pelo preço ou pelo codigo: 1 ou 2" << endl;
      cin >> mostra;
      if (mostra == 1) {
        cin >> preco;
        if (buscaPreco(produto, 0, tam, preco) != 1) {
          ordenaPreco(produto, 0, tam);
          cout << "o preco esta na seguinte posição:"
               << buscaPreco(produto, 0, tam, preco) << endl;
          system("read -p \"Pressione enter para sair\" saindo");
        } else {
          cout << "o produto não existe na tabela" << endl;
          system("read -p \"Pressione enter para sair\" saindo");
        }
      } else {
        ordenaCodigo(produto, 0, tam);
        cin >> codigo;
        if (buscaCodigo(produto, 0, tam, codigo) != 1) {
          cout << "o codigo esta na seguinte posição:"
               << buscaCodigo(produto, 0, tam, codigo) << endl;
          system("read -p \"Pressione enter para sair\" saindo");
        } else {
          cout << "o produto não existe na tabela" << endl;
          system("read -p \"Pressione enter para sair\" saindo");
        }
      }
      break;
    case 6:
      system("clear");
      cout << "Encerrando o programa..." << endl;
      break;
    default:
      cout << "Opção inválida. Tente novamente." << endl;
      break;
    }
  } while (opcao != 6);
  lendo.close();
  // armazena(produto, 0, tam);
}
