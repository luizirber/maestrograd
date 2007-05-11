// Alexandre Yukio Harano - RA: 254274 - k = 1
// Cálculo Numérico - Turma A - Professor Fernando

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;

 // Função Fatorial
 
 int fatorial (int n) {
  if ( n == 0 )
   return 1;
  else
   return n*fatorial(n-1);
 }

 // Função recursiva que retorna o valor das combinações k a k dos final-inicial+1 raízes

 double calculo_combinatorio (int inicial, int final, int combinacoes_k_a_k, int* vetor) {
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

 // O método de polinômios interpoladores de Newton é computado pelo programa abaixo

 int main(){
  bool controle_programa = 1;
  while (controle_programa){
   int n = 0;
   while (n < 1){
    cout<<"Entre com a ordem do polinomio interpolador a ser deduzido: ";
    cin>>n;
   }
   n++; // O número de elementos do polinômio é a ordem + 1 e esse será o valor de n ao longo
        // do programa
   cout<<endl;

   // Alocação de vetores e matrizes dinâmicas para o cálculo da tabela de diferenciais
   // finitas (TDF) e do vetor dos coeficientes do polinômio gerado, além de "zerá-los"

   double** TDF;
   int* u;
   double* coeficientes;
   u = new int[n];
   assert(u!=0);
   coeficientes = new double[n];
   assert(coeficientes!=0);
   TDF = new double*[n];
   assert( TDF != 0 );
   for (int i = 0; i < n; i++) {
    TDF[i] = new double[n-i+1];
    assert( TDF != 0 );
    u[i] = i;
    coeficientes[i] = 0.0;
    for (int j=0; j < n-i+1; j++)
     TDF[i][j] = 0.0;
   }
   double minimo = 0.0;
   double maximo = 0.0;
   double h = 0.0;
   double x0;

   // Leitura dos valores x0 e h e a determinação do intervalo do domínio do polinômio gerado

   cout<<"Entre com o valor de x[0]: ";
   cin>>x0;
   while ( h == 0.0 ) {
    cout<<"Entre com o intervalo h: ";
    cin>>h;
   }
   if ( h < 0 ) {
    maximo = x0;
    minimo = x0 + (n-1)*h;
   }
   else {
    maximo = x0 + (n-1)*h;
    minimo = x0;
   }
   cout<<endl;

   // Leitura dos valores de y

   for (int i = 0; i < n; i++) {
    cout<<"Entre com o valor de y["<<i<<"]: ";
    cin>>TDF[i][0];
   }
   cout<<endl;

   // Cálculo da tabela de diferencas finitas

   for (int j = 1; j < n; j++)
    for (int i = 0; i < n-j; i++)
     TDF[i][j] = (TDF[i+1][j-1]-TDF[i][j-1]);

   cout<<"TABELA DE DIFERENCAS FINITAS"<<endl<<endl;
   cout<<"u | x";
   for (int j = 0; j < n; j++)
    cout<<" | delta"<<j;
   cout<<endl;
   for (int i = 0; i < n; i++) {
    cout<<i<<" | "<<setprecision(10)<<(x0+i*h)<<" | ";
    for (int j = 0; j < n-i; j++)
     cout<<setprecision(10)<<TDF[i][j]<<"     ";
    cout<<endl;
   }
   cout<<endl;

   // Preenchimento dos vetores dos coeficientes dos polinomios onde i é o número relativo ao
   // i-ésimo termo pelo polinômio interpolador de Newton descrita no anexo e j é o número
   // relativo a j-ésima combinação a ser calculada
   
   for (int i = 0; i < n; i++)
    for (int j = 0; j < i+1; j++)
     if (j == 0)
      coeficientes[n-i-1] += TDF[0][i]/fatorial(i);
     else
      coeficientes[n-i+j-1] += calculo_combinatorio(0,i-1,j,u)*TDF[0][i]/fatorial(i);
     
   // Amostra do polinômio de interpolação na forma "bruta"

   cout<<"O polinomio gerado eh P(u) = "<<setprecision(10)<<TDF[0][0]<<" + ";
   for (int i = 0; i < n-1; i++) {
    for (int j = 0; j<i+1; j++)
     cout<<"(u-"<<setprecision(10)<<u[j]<<")*";
    cout<<"("<<setprecision(10)<<TDF[0][i+1]<<")/("<<i+1<<"!)";
    if (i!=n-2)
     cout<<" + ";
   }
   cout<<endl<<endl;

   // Amostra do polinômio da forma usual
   
   cout<<"Equivalente a P(u) = ";
   for (int contagem = 0; contagem<n; contagem++) {
    cout<<"("<<setprecision(10)<<coeficientes[contagem]<<")";
    if (contagem!=n-1)
     cout<<"*x^"<<n-contagem-1<<" + ";
   }
   cout<<endl<<endl;
   
   // Teste do polinômio interpolador gerado
   
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
    double u_teste = (x_teste - x0)/h;
    double p_teste = coeficientes[n-1];
    for (int i = 0; i<n-1; i++){
     double produtorio = coeficientes[i];
     for (int j = 0; j<n-i-1; j++)
      produtorio = produtorio*u_teste;
     p_teste += produtorio;
    }
    cout<<"u = (x - x0)/h ==> u = (("<<setprecision(10)<<x_teste<<") - ("
        <<setprecision(10)<<x0<<"))/"<<setprecision(10)<<h<<" ==> u = "
        <<setprecision(10)<<u_teste<<endl;
    cout<<"P("<<setprecision(10)<<u_teste<<") = "<<setprecision(10)<<p_teste<<endl<<endl;
      
    // Verificação se deseja testar com outro valor

    char char_teste = '\0';
    while ((char_teste!='s')&&(char_teste!='S')&&(char_teste!='n')&&(char_teste!='N')) {
     cout<<"Deseja testar o polinomio interpolador gerado com outro valor (S ou N)? ";
     cin>>char_teste;
    }
    cout<<endl;
    if ((char_teste=='n')||(char_teste=='N'))
     teste_polinomio = 0;
   }
   
   // Desaloca a memória referente aos vetores e matrizes

   delete coeficientes;
   delete u;
   delete TDF;
   
   // Verificação se deseja gerar outro polinômio interpolador

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
