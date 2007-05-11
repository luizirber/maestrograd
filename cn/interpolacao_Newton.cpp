#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

 //Fun��o recursiva que retorna o valor das combina��es k a k dos final-inicial+1 ra�zes

 double calculo_combinatorio (int inicial, int final, int combinacoes_k_a_k, double* vetor) {
  if (combinacoes_k_a_k == 1) {
   double somatoria = 0.0;
   for (int i = inicial; i < final+1; i++)
    somatoria -= vetor[i];
   return somatoria;
  }
  else {
   double soma_e_produto = 0.0;
   for (int i = inicial; i < final - combinacoes_k_a_k + 2; i++){
    soma_e_produto -= vetor[i]*calculo_combinatorio(i+1, final, combinacoes_k_a_k - 1, vetor);
   }
   return soma_e_produto;
  }
 }

 // O m�todo de polin�mios interpoladores de Newton � computado pelo programa abaixo

 int main(){
  bool controle_programa = 1;
  while (controle_programa){
   int n = 0;
   while (n < 1){
    cout<<"Entre com a ordem do polinomio interpolador a ser deduzido: ";
    cin>>n;
   }
   n++; // O n�mero de elementos do polin�mio � a ordem + 1 e esse ser� o valor de n ao longo do
        // programa
   cout<<endl;

   // Aloca��o de vetores e matrizes din�micas para o c�lculo da tabela de diferenciais divididas
   // (TDD) e do vetor dos coeficientes do polin�mio gerado, al�m de "zer�-los"

   double** TDD;
   double* x;
   double* coeficientes;
   x = new double[n];
   assert(x!=0);
   coeficientes = new double[n];
   assert(coeficientes!=0);
   TDD = new double*[n];
   assert( TDD != 0 );
   for (int i = 0; i < n; i++) {
    TDD[i] = new double[n-i+1];
    assert( TDD != 0 );
    x[i] = 0.0;
    coeficientes[i] = 0.0;
    for (int j=0; j < n-i+1; j++)
     TDD[i][j] = 0.0;
   }
   double minimo;
   double maximo;

   // Leitura dos valores de x -=- Durante a inser��o de x[i], verifica se o valor foi previamente
   // inserido entre x[0] e x[i-1] e tamb�m determina o intervalo do dom�nio do polin�mio
   // interpolador gerado

   for (int i = 0; i < n; i++) {
    bool repetido = 1;
    while (repetido){
     repetido = 0;
     double leitura;
     cout<<"Entre com o valor de x["<<i<<"]: ";
     cin>>leitura;
     for (int j=0; j<i; j++)
      if (x[j]==leitura){
       repetido = 1;
       cout<<"O valor de x["<<i<<"] digitado foi previamente inserido em x["<<j<<"]."<<endl;
      }
     if (!repetido){
      x[i] = leitura;
      if (i==0){
       minimo = leitura;
       maximo = leitura;
      }
      else {
       if (leitura < minimo)
        minimo = leitura;
       if (leitura > maximo)
        maximo = leitura;
      }
     }
    }
   }
   cout<<endl;

   // Leitura dos valores de y

   for (int i = 0; i < n; i++) {
    cout<<"Entre com o valor de y["<<i<<"]: ";
    cin>>TDD[i][0];
   }
   cout<<endl;

   // C�lculo da tabela de diferencas divididas

   for (int j = 1; j < n; j++)
    for (int i = 0; i < n-j; i++)
     TDD[i][j] = (TDD[i+1][j-1]-TDD[i][j-1])/(x[i+j]-x[i]);

   cout<<"TABELA DE DIFERENCAS DIVIDIDAS"<<endl<<endl;
   for (int i = 0; i < n; i++) {
    cout<<x[i]<<" | ";
    for (int j = 0; j < n-i; j++)
     cout<<TDD[i][j]<<"     ";
    cout<<endl;
   }
   cout<<endl;

   // Preenchimento dos vetores dos coeficientes dos polinomios onde i � o n�mero relativo ao
   // i-�simo termo pelo polin�mio interpolador de Newton descrita no anexo e j � o n�mero
   // relativo a j-�sima combina��o a ser calculada
   
   for (int i = 0; i < n; i++)
    for (int j = 0; j < i+1; j++)
     if (j == 0)
      coeficientes[n-i-1] += TDD[0][i];
     else
      coeficientes[n-i+j-1] += TDD[0][i]*calculo_combinatorio(0,i-1,j,x);
     
   // Amostra do polin�mio de interpola��o na forma "bruta"

   cout<<"O polinomio gerado eh P(x) = "<<setprecision(10)<<TDD[0][0]<<" + ";
   for (int i = 0; i < n-1; i++) {
    for (int j = 0; j<i+1; j++)
     if (x[j]<0)
      cout<<"(x+"<<setprecision(10)<<-x[j]<<")*";
     else
      cout<<"(x-"<<setprecision(10)<<x[j]<<")*";
    cout<<TDD[0][i+1];
    if (i!=n-2)
     cout<<" + ";
   }
   cout<<endl<<endl;

   // Amostra do polin�mio da forma usual
   
   cout<<"Equivalente a P(x) = ";
   for (int contagem = 0; contagem<n; contagem++) {
    cout<<setprecision(10)<<coeficientes[contagem];
    if (contagem!=n-1)
     cout<<"*x^"<<n-contagem-1<<" + ";
   }
   cout<<endl<<endl;
   
   // Teste do polin�mio interpolador gerado
   
   bool teste_polinomio = 1;
   while (teste_polinomio){
    double x_teste;
    bool x_dentro_do_intervalo = 0;
    while (!x_dentro_do_intervalo){
     cout<<"Entre com um valor para x: ";
     cin>>x_teste;
     if ((x_teste < minimo)||(x_teste > maximo))
      cout<<"O valor digitado estah fora do intervalo ["<<setprecision(10)<<minimo<<","
          <<setprecision(10)<<maximo<<"]."<<endl<<endl;
     else
      x_dentro_do_intervalo = 1;
    }
    double p_teste = coeficientes[n-1];
    for (int i = 0; i<n-1; i++){
     double produtorio = coeficientes[i];
     for (int j = 0; j<n-i-1; j++)
      produtorio = produtorio*x_teste;
     p_teste += produtorio;
    }
    cout<<"P("<<setprecision(10)<<x_teste<<") = "<<setprecision(10)<<p_teste<<endl<<endl;
      
    // Verifica��o se deseja testar com outro valor

    char char_teste = '\0';
    while ((char_teste!='s')&&(char_teste!='S')&&(char_teste!='n')&&(char_teste!='N')) {
     cout<<"Deseja testar o polinomio interpolador gerado com outro valor (S ou N)? ";
     cin>>char_teste;
    }
    cout<<endl;
    if ((char_teste=='n')||(char_teste=='N'))
     teste_polinomio = 0;
   }
   
   // Desaloca a mem�ria referente aos vetores e matrizes

   delete coeficientes;
   delete x;
   delete TDD;
   
   // Verifica��o se deseja gerar outro polin�mio interpolador

   char verifica = '\0';
   while (((verifica!='s')&&(verifica!='S'))&&((verifica!='n')&&(verifica!='N'))) {
    cout<<"Deseja gerar outro polinomio interpolador (S ou N)? ";
    cin>>verifica;
   }
   if ((verifica=='n')||(verifica=='N'))
    controle_programa = 0;
   cout<<endl;
  }
  return 0;
 }
