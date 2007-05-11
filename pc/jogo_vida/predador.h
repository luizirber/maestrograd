#include

class predador {
    private:
        int idade=0;
        enum apetite{satisfeito, indiferente, faminto, voraz}=indiferente;
        char estado='V', sexo, caractere;
    public:
        predador();
        void comer();
        void aumenta_apetite();
        void incrementa_idade();
        void imprime();        
};
