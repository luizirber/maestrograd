#include <iostream>

using namespace std;

int main(void)
{
  int opcao=0;
  while (opcao != 5){
    cout<<" Loja de Ferramentas" <<endl
        <<" 1 para adicionar"<<endl
        <<" 2 para modificar"<<endl
        <<" 3 para consultar estoque"<<endl
        <<" 4 para remover item"<<endl
        <<" 5 para sair"<<endl
        <<" Digite opção: ";
    cin>>opcao;
    cout<<endl;
    while (opcao < 1 && opcao > 5){
      cout<<"opcao invalida, tente de novo: ";
      cin>>opcao;
      cout<<endl;
    }
    switch (opcao){
      case 1:

        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
    }
  }

  return 0;
}
