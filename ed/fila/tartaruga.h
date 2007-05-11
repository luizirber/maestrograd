#include "fila.h"

const int tam=10;

enum direcao {S,L,N,O};

class tartaruga{
  private:
    bool chao[tam][tam];
    bool caneta_risca;
    direcao frente;
    fila<int> comandos;
    int pos_h, pos_v;
  public:
    tartaruga();
    int getPos_v();
    int getPos_h();
    char* getFrente();
    void CanetaRisca();
    void CanetaNaoRisca();
    void GiraEsquerda();
    void GiraDireita();
    void Move(int);
    void Imprime();
    void InsereComando(int,int);
};

int tartaruga::getPos_v(){
  return pos_v;
}

int tartaruga::getPos_h(){
  return pos_h;
}
char* tartaruga::getFrente(){
  switch(frente){
   case S: return "Sul"; break;
   case N: return "Norte"; break;
   case L: return "Leste"; break;
   case O: return "Oeste"; break;
  }
}

tartaruga::tartaruga():frente(S),caneta_risca(false),pos_h(0),pos_v(0){
  for (int i=0;i<tam;i++)
    for (int j=0;j<tam;j++)
      chao[i][j]=false;
}

void tartaruga::CanetaRisca(){
  caneta_risca=true;
}

void tartaruga::CanetaNaoRisca(){
  caneta_risca=false;
}

void tartaruga::GiraEsquerda(){
  switch(frente)
  {
    case S: frente=L; break;
    case L: frente=N; break;
    case N: frente=O; break;
    case O: frente=S; break;
  }
}

void tartaruga::GiraDireita(){
  switch(frente)
  {
    case O: frente=N; break;
    case N: frente=L; break;
    case L: frente=S; break;
    case S: frente=O; break;
  }
}

void tartaruga::Move(int passos){
  switch(frente)
  {
    case S:
      if (caneta_risca)
        for ( int k = pos_h; (k != pos_h + passos) && (k < tam); k++)
        {
          chao[k][pos_v]=true;
          pos_h++;
        }
      else
        if (pos_h+passos>tam)
          pos_h=tam-1;
        else
          pos_h = pos_v + passos;
      if (pos_h > tam-1)
        pos_h = tam-1;
    break;
  case L:
    if (caneta_risca)
      for ( int k = pos_v; (k != pos_v + passos) && (k < tam); k++)
      {
        chao[pos_h][k]=true;
        pos_v++;
      }
    else
      if (pos_v + passos > tam)
        pos_v = tam-1;
      else
        pos_v = pos_v + passos;
    if (pos_v > tam-1)
      pos_v = tam-1;
  break;
  case N:
    if (caneta_risca)
      for ( int k = pos_h; (k != pos_h - passos) && (k >= 0); k--)
      {
        chao[k][pos_v]=true;
        pos_h--;
      }
    else
      if (pos_h - passos < 0)
        pos_h=0;
      else
        pos_h = pos_h - passos;
    if (pos_h < 0)
      pos_h = 0;
  break;
  case O:
  if (caneta_risca)
    for ( int k = pos_v; (k != pos_v - passos) && (k >=0 ); k--)
    {
      chao[pos_h][k]=true;
      pos_v--;
    }
  else
    if (pos_v - passos < 0)
      pos_v = 0;
    else
      pos_v = pos_v - passos;
  if (pos_v < 0)
    pos_v = 0;
  break;
  }
}
void tartaruga::Imprime(){
  int com;
  while ((comandos.vazia())==false){
    com=comandos.sai();
    switch(com){
      case 1:
        CanetaRisca();
      break;
      case 2:
        CanetaNaoRisca();
      break;
      case 3:
        GiraDireita();
      break;
      case 4:
        GiraEsquerda();
      break;
      default:
        Move(com-500);
      break;
    }
  }

  cout<<" ";
  for (int k=0;k<=tam;k++)
    cout<<" # ";
  cout<<endl;
  for (int i=0;i<tam; i++){
    cout<<" # ";
    for (int j=0;j<tam; j++){
      if (chao[i][j])
        cout<<" * ";
      else
        cout<<"   ";
      chao[i][j]=false;
    }
    cout<<" # "<<endl;
  }
  cout<<" ";
  for (int k=0;k<=tam;k++)
    cout<<" # ";
  cout<<endl;
}

void tartaruga::InsereComando(int comando,int passos){
  if (comando==5)
    comandos.entra(500+passos);
  else
    if (comando==6)
      Imprime();
    else
      comandos.entra(comando);
}
