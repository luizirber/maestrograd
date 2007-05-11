#ifndef ponto_h
#define ponto_h

class ponto{
  private:
    int x;
    int y;
  public:
    ponto();
    ponto(int,int);
    void set_ponto(int, int);
    void get_ponto (int&, int&);
};

#endif

