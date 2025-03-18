#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

string palavra_secreta = "";
int erros = 1;

map <char, bool> chutou;

vector<char> chutes_errados;

bool letra_existe(char chute)
{
  for(char letra : palavra_secreta)
  {
    if (chute == letra)
    {
      return true;
    }
  }
  return false;
}

bool nao_acertou ()
{
  for (char letra : palavra_secreta)
  {
    if(!chutou[letra]) 
    {
      return true; 
    }
  }
  return false;
}

bool nao_enforcou()
{
  return chutes_errados.size() < 5;
}

void imprime_cabecalho()
{
  cout << "****************************************" << endl;
  cout << "****   Bem-vindo ao Jogo da Forca   ****" << endl;
  cout << "****************************************" << endl;
  cout << endl;

  cout << "Nesse jogo é permitido apenas 5 erros, sendo que depois do quinto cute errado o jogo acaba.";
  cout << endl;
}

void imprime_erros()
{
  if (!chutes_errados.empty()) 
  {
    cout << endl << "Quantos erros teve: " << erros << endl;

    cout << "Chutes errados: ";

    for (char letra : chutes_errados)
    {
      cout << letra << " ";
    }

    cout << endl;
  }
}

void imprime_palavra()
{
  for(char letra : palavra_secreta)
  {
    if (chutou[letra])
    {
      cout << letra << " ";
    }
    else
    {
      cout << "_ ";
    }
  }

  cout << endl;
}

void chuta()
{
  char chute;
  cout << endl << "Dê seu chute: ";
  cin >> chute;
  chute = toupper(chute);

  chutou[chute] = true;

  cout << endl << "Seu chute foi: " << chute << "!" << endl;

  if (letra_existe(chute))
  {
    cout << "Você acertou! Seu chute está na palavra!" << endl;
  } else
  {
    cout << "Você errou! Seu chute não está na palavra!" << endl;
    chutes_errados.push_back(chute);
    erros++;
  }

  cout << endl;
}

vector<string> le_arquivo()
{
  ifstream arquivo;
  arquivo.open("palavras.txt");
  
  if (arquivo.is_open())
  {
    int qtd_palavras;
    arquivo >> qtd_palavras;
    
    //cout << "O arquivo possui " << qtd_palavras << " palavras." << endl;

    vector<string> palavras_do_arquivo;
    
    for (int i = 0; i < qtd_palavras; i++)
    {
      string palavra_lida;
      arquivo >> palavra_lida;

      //cout << "Na linha " << i << " : " << palavra_lida << endl;
      
      palavras_do_arquivo.push_back(palavra_lida);
    }
    
    arquivo.close();
    return palavras_do_arquivo;
  }
  else
  {
    cout << "Não foi possivél acessar o banco de palavras do jogo.";
    exit(0);
  }
}

void sorteia_palavras()
{
  vector<string> palavras = le_arquivo();
  
  srand(time(NULL));
  int indice_sorteado = rand() % palavras.size();
  
  palavra_secreta = palavras[indice_sorteado];
}

void salvar_arquivo(vector<string> nova_lista)
{
  ofstream arquivo;
  arquivo.open("palavras.txt");

  if (arquivo.is_open())
  {
    arquivo << nova_lista.size() << endl;

    for (string palavra : nova_lista)
    {
      arquivo << palavra << endl;
    }

    arquivo.close();
  }
  else
  {
    cout << "Não foi possivél acessar o banco de palavras do jogo.";
    exit(0);
  }
}

void adiciona_palavra()
{
  cout << "Escreva a palavra com todas as letras em maiúsculas: ";
  string nova_palavra;
  cin >> nova_palavra;
  
  vector<string> lista_palavras = le_arquivo();
  lista_palavras.push_back(nova_palavra);

  salvar_arquivo(lista_palavras);
}

void fim_de_jogo()
{
  cout << "Fim de jogo!" << endl;
  cout << "A palavra secreta era: " << palavra_secreta << endl;
  if (nao_acertou())
  {
    cout << "Você perdeu. Tente novamente!";
  }
  else
  {
    cout << "Parabéns, você acertou a palavra secreta!";
  }
  
  cout << "Você deseja jogar novamente? (S/N): ";
  char resposta;
  cin >> resposta;
  resposta = toupper(resposta);
  if (resposta == 'S')
  {
    cout << "Por favor, adicione uma palavra ao banco de palavras!";
    adiciona_palavra();
  }
  else
  {
    exit(0);
  }
}

int main ()
{
  imprime_cabecalho();

  le_arquivo();

  sorteia_palavras();

  while (nao_acertou() && nao_enforcou())
  {
    imprime_erros();

    imprime_palavra();

    chuta();
  }

  fim_de_jogo();
}
