#if !defined(ferramenta_H)
  #define ferramenta_H
#endif // ferramenta_H
#include<iostream>

using namespace std;

class ferramenta {
  private:
    int numero, quantidade;
    char nome[30];
    double preco;
  public:
    ferramenta(int n, int q, char n, double p){
       set_nome(n);
       set_preco(p);
       set_quantidade(q);
       set_numero(n);
     }
    void set_numero(const int n) { ( n >= 0 : numero = n ? (cout<<"\nValor inválido. Definindo como 0\n") ); }
    void set_quantidade(const int n) {
      ( n >= 0 : numero = n ? (cout<<"\nValor inválido. Definindo como 0\n"); )
      if (preco < 5){ cout>>"efetue reposicao do item " numero };
      }
    void set_nome(const char n){ nome = n }
    void set_preco(const double p){ ( p >= 0 : preco = p ? (cout<<"\nValor inválido. Definindo como 0\n") ); }
    int get_numero() {return numero}
    int get_quantidade() {return quantidade}
    char get_nome() {return nome}
    double get_preco() {return preco}
};


