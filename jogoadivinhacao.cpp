#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main ()
{
  cout << "****************************************" << endl;
  cout << "*   Bem-vindo ao Jogo da adivinhação   *" << endl;
  cout << "****************************************" << endl;

  bool jogar_novamente = true;

  while (jogar_novamente)
  {
    cout << "Escolha o nivel de dificuldade F (Fácil), M (Médio) ou D (Difícil): ";
    char dificuldade;
    cin >> dificuldade;

    int numero_de_tentativas;

    if (dificuldade == 'F' || dificuldade == 'f')
    {
      numero_de_tentativas = 15;
    } else if (dificuldade == 'M' || dificuldade == 'm')
    {
      numero_de_tentativas = 10;
    } else if (dificuldade == 'D' || dificuldade == 'd')
    {
      numero_de_tentativas = 5;
    } else
    {
      cout << endl << "Por favor, insira uma dificuldade valida." << endl;
      continue;
    }

    srand(time(NULL));

    const int NUMERO_SECRETO = rand() % 100;
    //cout << "O número secreto é " << NUMERO_SECRETO << ". Não conte para ninguém!" << endl;

    bool nao_acertou = true;

    int tentativas = 0;

    double pontos = 1000.0;

    for (tentativas = 1; tentativas <= numero_de_tentativas; tentativas++)
    {
      cout << endl << "Tentativa atual: " << tentativas << endl;
      int chute;
      cout << endl << "Dê seu chute: ";
      cin >> chute;

      double pontos_perdidos = abs(chute - NUMERO_SECRETO) / 2.0;
      pontos -= pontos_perdidos;
  
      cout << "O valor do seu chute é " << chute << "!" << endl;
  
      bool maior_que = chute > NUMERO_SECRETO;
      bool menor_que = chute < NUMERO_SECRETO;
      
      if (maior_que) {
        cout << "O seu chute é maior que o numero secreto!" << endl;
      }
      else if (menor_que)
      {
        cout << "O seu chute é menor que o numero secreto!" << endl;
      }
      else
      {
        nao_acertou = false;
        break;
      }
    }

    if (nao_acertou)
    {
      cout << "Você perdeu! Tente novamente." << endl;
      cout << "O numero secreto era: " << NUMERO_SECRETO << endl;
    } else
    {
      cout << endl << "Fim de jogo!" << endl;
      cout << "Parabéns, você ganhou na tentativa de número " <<tentativas << "!" << endl;
      cout.precision(2);
      cout << fixed;
      cout << "Sua pontuação foi de: " << pontos << "!" << endl;
    }

    char resposta;
    cout << endl << "Deseja jogar novamente? (S/N): ";
    cin >> resposta;

    if (resposta == 'N' || resposta == 'n') break;
  }
}
