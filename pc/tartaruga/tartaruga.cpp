#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

struct caso5
{
  int jogada, passos;
};

int main()
{  
    int cont_5=0, cont_comando=0, comandos[100]={0};
    caso5 comando5[100];
    char virgula=',', orientacao='L';
    int comando=1, chao[20][20]={0}, posicao_caneta=1, pos_h=0, pos_v=0;
    while ( comando!=9 )
    {
        comando=1;
        cout<<"     ##     "<<"  Turtle Graphics"<<endl
            <<"    #  #    "<<"  A tartaruga esta na posicao ("<<pos_h<<","<<pos_v<<")"<<endl
            <<"### #  # ###"<<"  e virada para a direcao "<<orientacao<<endl
            <<"# #  ##  # #"<<"  Use os comandos: "<<endl 
            <<"####/| \\####"<<"  1 - Caneta para cima"<<endl
            <<"   /| | \\   "<<"  2 - Caneta para baixo"<<endl
            <<"  | | |  |  "<<"  3 - Giro à direita"<<endl
            <<"  | | |  |  "<<"  4 - Giro à esquerda"<<endl
            <<"###\\ | |/###"<<"  5,N - Move N espacos"<<endl
            <<"# ##\\ |/## #"<<"  6 - Executa os comandos e imprime o arranjo"<<endl
            <<"###  ##  ###"<<"  9 - Termina o programa"<<endl
            <<"Insira os comandos: "<<endl;
            
        for ( int i=0; comando!=6 && comando!=9; i++)
        { 
          cin>>setw(1)>>comando;
          if (comando>0 && comando<10 && comando!=7 && comando!=8)
          {  
            comandos[i]=comando;
            cont_comando++;
            if (comandos[i]==5)
            {
              comando5[cont_5].jogada=i;
              cin>>virgula>>setw(2)>>comando5[cont_5].passos;
              cont_5++;        
            }
            if (comandos[i]==6)
            {
              for (int j=0; comandos[j]!=9; j++)
              {
                int n=0;
                switch (comandos[j])
                {
                  case 1:
                     posicao_caneta=1; 
                    break;
                  case 2:
                     posicao_caneta=2; 
                    break;   
                  case 3:
                      switch(orientacao)
                      {
                        case 'S': orientacao='O'; break;
                        case 'O': orientacao='N'; break;
                        case 'N': orientacao='L'; break;                        
                        case 'L': orientacao='S'; break;                             
                      }    
                    break;   
                  case 4:
                      switch(orientacao)
                      {
                        case 'S': orientacao='L'; break;
                        case 'L': orientacao='N'; break;
                        case 'N': orientacao='O'; break;                        
                        case 'O': orientacao='S'; break;                             
                      }    
                    break;   
                  case 5:
                      while ( comando5[n].jogada != j)
                        n++;
                      int m;  
                      switch(orientacao)
                      {
                        case 'S':
                          m = pos_h + comando5[n].passos;  
                          if (posicao_caneta==2)
                            for ( int k = pos_h; k != m && k < 20; k++)
                            {
                              chao[k][pos_v]=1;
                              pos_h++;
                            }    
                          else
                            if (m>20)
                              pos_h=19;
                            else
                              pos_h=m;  
                          if (pos_h > 19)
                            pos_h = 19;
                        break;
                        case 'L':
                          m = pos_v + comando5[n].passos;  
                          if (posicao_caneta==2)
                            for ( int k = pos_v; k != m && k < 20; k++)
                            { 
                              chao[pos_h][k]=1;
                              pos_v++;
                            }    
                          else
                            if (m>20)
                              pos_v=19;
                            else
                              pos_v=m;  
                          if (pos_v > 19)
                            pos_v = 19;                              
                        break;
                        case 'N':
                          m = pos_h - comando5[n].passos;  
                          if (posicao_caneta==2)
                            for ( int k = pos_h; k != m && k >= 0 ; k--)
                            {
                              chao[k][pos_v]=1;
                              pos_h--;
                            }    
                          else  
                            if (m<0)
                              pos_h=0;
                            else
                              pos_h=m;  
                          if (pos_h < 0)
                            pos_h = 0;                              
                        break;
                        case 'O':
                          m = pos_v - comando5[n].passos;  
                          if (posicao_caneta==2)
                            for ( int k = pos_v; k != m && k >= 0; k--)
                            {
                              chao[pos_h][k]=1;
                              pos_v--;
                            }    
                          else
                            if (m<0)
                              pos_v=0;
                            else
                              pos_v=m;
                          if (pos_v < 0)
                            pos_v = 0;                              
                        break;  
                      }
                      break;
                  case 6:
                    cout<<"\n########################\n#\t\t       #\n";
                    for (int x=0; x<20; x++)
                    {
                      cout<<"# ";
                      for (int z=0; z<20; z++)
                      {
                        (chao[x][z]==1 ? cout<<'*' : cout<<' ');
                        chao[x][z]=0;
                      }      
                      cout<<" #\n";
                    }
                    cout<<"#\t\t       #\n########################\n";                    
                    for (int y=0; y<=cont_comando; y++)
                      comandos[y]=0;
                    break;   
                  case 9:
                    break;   
                }//fim switch    
              }//fim for     
            }//fim if (comando==6)
          }//fim if verificacao consistência 
          else
            cout<<"Comando invalido. Insira novo comando: ";
        } //fim for     
        cont_5=0;
        cont_comando=0;          
    }//fim while    
    system("PAUSE");
    return 0;
}
