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
    int lista_comandos[100]={0}, cont_5=0, cont_comando=0, comandos[100]={0};
    caso5 comando5[100];
    char virgula=',', orientacao='L';
    int comando=1, chao[19][19]={0}, posicao_caneta=1, pos_h=0, pos_v=0;
    while ( comando!=9 )
    {
        comando=1;
        cout<<"Turtle Graphics\n"
            <<"A tartaruga esta na posicao ("<<pos_h<<","<<pos_v<<") e virada para a direcao Leste\n"
            <<"Insira os comandos:\n";
        for ( int i=0; comando!=6 && comando!=9; i++)
        { 
          cin>>setw(1)>>comando;
          /*verificacao de consistência*/
          comandos[i]=comando;
          cont_comando++;
          if (comandos[i]==5)
          {
            comando5[cont_5].jogada=i;  
            cin>>virgula>>setw(2)>>comando5[cont_5].passos;
            comando5[cont_5].passos--;
            cont_5++;        
          }
          if (comandos[i]==6)
          {
            int sentinela=0;  
            for (int j=0; comandos[j]!=9 && sentinela==0; j++)
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
                      if (orientacao=='S')
                        orientacao='O';
                      else
                        if (orientacao=='O')
                          orientacao='N';
                        else
                          if (orientacao=='N')
                            orientacao='L';
                          else
                            orientacao='S';
                    break;   
                  case 4:
                      if (orientacao=='S')
                        orientacao='L';
                      else
                        if (orientacao=='L')
                          orientacao='N';
                        else
                          if (orientacao=='N')
                            orientacao='O';
                          else
                            orientacao='S';
                    break;   
                  case 5:
                      while ( comando5[n].jogada != j)
                        n++;
                      if (orientacao=='S')
                      {
                        int m = pos_h + comando5[n].passos;  
                        if ( m < 20 )
                          for ( int k = pos_h; k != m+1; k++)
                          {  
                            chao[k][pos_v]=1;
                            pos_h++;
                          }
                        else
                          {
                            cout<<'Fora do tabuleiro. Interrompendo execução';
                            sentinela=1;
                          }      
                      }       
                      else
                        if (orientacao=='L')
                        {
                          int m = pos_v + comando5[n].passos;  
                          if ( m < 20 )
                            for ( int k = pos_v; k != m+1; k++)
                            {  
                              chao[pos_h][k]=1;
                              pos_v++;
                            }      
                          else
                            {
                              cout<<'Fora do tabuleiro. Interrompendo execução';
                              sentinela=1;
                            }                            
                        }
                        else
                          if (orientacao=='N')
                          {
                            int m = pos_h - comando5[n].passos;  
                            if ( m >= 0 )
                              for ( int k = pos_h; k != m-1; k--)
                              {  
                                chao[k][pos_v]=1;
                                pos_h--;
                              }      
                            else
                              {
                                cout<<'Fora do tabuleiro. Interrompendo execução';
                                sentinela=1;
                              }                              
                          }
                          else
                          {
                            int m = pos_v - comando5[n].passos;  
                            if ( m >= 0 )
                              for ( int k = pos_v; k != m-1; k--)
                              {  
                                chao[pos_h][k]=1;
                                pos_v--;
                              }      
                            else
                              {
                                cout<<'Fora do tabuleiro. Interrompendo execução';
                                sentinela=1;
                              }                              
                          }
                      break;
                  case 6:
                    cout<<"\n#######################\n# ";
                    for (int x=0; x<20; x++)
                    {
                      for (int z=0; z<20; z++)
                      {
                        (chao[x][z]==1 ? cout<<'*' : cout<<' ');
                        chao[x][z]=0;
                      }      
                      cout<<" #\n";
                    }
                    cout<<"#######################\n";                    
                    for (int y=0; y<=cont_comando; y++)
                      comandos[y]=0;
                    break;   
                  case 9:
                    break;   
               }    
               
            }
            cont_5=0;
            cont_comando=0;
          }    
        }      
    }    
    system("PAUSE");
    return 0;
}
