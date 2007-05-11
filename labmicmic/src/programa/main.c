#include <mcs51/at89x52.h>
#include <stdio.h>
#include "i2c.h"

#define EQUIPAMENTO_1 P2_0
#define EQUIPAMENTO_2 P2_1
#define EQUIPAMENTO_3 P2_2
#define EQUIPAMENTO_4 P2_3
#define EQUIPAMENTO_5 P2_4
#define EQUIPAMENTO_6 P2_5
#define EQUIPAMENTO_7 P2_6
#define EQUIPAMENTO_8 P2_7
#define EQUIPAMENTO_9 P3_7 /* TODO: esse vai ficar em que porta? */

//9 é um número de maquinas que serao no máximo.
#define NUMERO_MAQUINAS 9

void recebe_ligacao() __interrupt IE0_VECTOR;
/*
void cria_estados() __critical;
void carrega_estado(int maquina);
void verificar_estados();
void faz_ligacao();


int numero_maquinas = NUMERO_MAQUINAS ;
unsigned char estados[NUMERO_MAQUINAS];
unsigned char estados_padrao[NUMERO_MAQUINAS];
unsigned data portas[NUMERO_MAQUINAS];
int problema_ocorrido;
int maquina_com_problema[NUMERO_MAQUINAS];


void cria_estados() __critical {
    portas[0] = 0x80;
}

//Carrega para o vetor estado, o valor na porta da (int maquina)
void carrega_estado(int maquina){
    //Arrumar um jeito de no lugar de 0x80 por portas[maquina]
    __sbit __at 0x80 value;
    estados[maquina] = value;
}

//Percorre pelo vetor de estados verificando se o estado atual da maquina é
//equivalemte ao estado padrao, se for, o vetor de problemas recebe 0  na
//posicao, se nao recebe 1 e muda o indicador problema_ocorrido para 1.
void verificar_estados(){
    int i=0;
    for (i=0;i<numero_maquinas-1;i++){
        carrega_estado(i);
        if (estados[i] != estados_padrao[i]){
            problema_ocorrido = 1;
            maquina_com_problema[i] = 1;
        }
        else
            maquina_com_problema[i] = 0;
    }
}
*/

/**	Quando a interrupção 0 é ativada, ou seja, quando o detector de toque está em alto,
	é coletado um equipamento ( 1-9 ) e qual ação deve ser tomada:
	* - Liga o Equipamento
	# - Desliga o Equipamento
	0 - Retorna o tom do estado do Equipamento
*/
void recebe_ligacao() __interrupt IE0_VECTOR {
    char valor_lido;
    char reading = 1;
    char equipamento = -1;
    char comando =0;
    char liga = 0;

    /* pulsa o primeiro rele para trocar de circuito */
    P0_0 = 0;    
    P0_0 = 1;
    Delay();
    Delay();
    Delay();
    Delay();
    Delay();
    Delay();
    Delay();
    Delay();
    P0_0 = 0;
    Delay();
    /* nivel alto no segundo rele, atende o telefone */
    P0_1 = 1;
    
    while(reading) {
		/* Enquanto o strobe não estiver alto (tecla pressionada), 
		   fica preso nesse loop. */
	    while(P1_4 != 1);
        valor_lido = 1 * P1_0 + 2 * P1_1 + 4 * P1_2 + 8 * P1_3;
        /* if (valor_lido != * && valor_lido != #) */
        if (valor_lido <= 9 && valor_lido > 0){
            equipamento = valor_lido;
        }
        else {
        	if (equipamento != -1){
            	/* if (valor_lido == *) LIGA? */
            	if (valor_lido == 11){
               		reading = 0;
              		comando = 1;
            	}
            	/* if (valor_lido == #) DESLIGA? */
            	if (valor_lido == 12){
            		reading = 0;
            		comando = 0;
            	}
            	/* if (valor_lido == 0) Envia Estado */
            	if (valor_lido == 10){
            		reading = 0;
            		comando = 2;
            	}
            } /* fim IF */
        } /* fim ELSE */
    } /* fim while(reading) */ 

	/* Estando com as variáveis Equipamento e Liga com seus devidos valores, 
	   alterar o valor das portas. */
	if (comando == 2){
		switch(equipamento) {
			case 1: SendData(EQUIPAMENTO_1);
			        break;
			case 2: SendData(EQUIPAMENTO_2);
			        break;
			case 3: SendData(EQUIPAMENTO_3);
			        break;
			case 4: SendData(EQUIPAMENTO_4);
			        break;
			case 5: SendData(EQUIPAMENTO_5);
			        break;
			case 6: SendData(EQUIPAMENTO_6);
			        break;
			case 7: SendData(EQUIPAMENTO_7);
			        break;
			case 8: SendData(EQUIPAMENTO_8);
			        break;
			case 9: SendData(EQUIPAMENTO_9);
			        break;
			default: break;
		}	
	}
	else {
		//Comando será 0 para desligar, 1 para ligar.
		char liga = comando;
		switch(equipamento) {
			case 1: EQUIPAMENTO_1 = liga;
			        break;
			case 2: EQUIPAMENTO_2 = liga;
			        break;
			case 3: EQUIPAMENTO_3 = liga;
			        break;
			case 4: EQUIPAMENTO_4 = liga;
			        break;
			case 5: EQUIPAMENTO_5 = liga;
			        break;
			case 6: EQUIPAMENTO_6 = liga;
			        break;
			case 7: EQUIPAMENTO_7 = liga;
			        break;
			case 8: EQUIPAMENTO_8 = liga;
			        break;
			case 9: EQUIPAMENTO_9 = liga;
			        break;
			default: break;
		}
	}	
	
	/* baixa o nivel do rele */
	P0_1 = 0;
}

void faz_ligacao(void){}

void main(void){
    //cria_estados();
    EQUIPAMENTO_1 = 0;
    EQUIPAMENTO_2 = 0;
    EQUIPAMENTO_3 = 0;
    EQUIPAMENTO_4 = 0;
    EQUIPAMENTO_5 = 0;
    EQUIPAMENTO_6 = 0;
    EQUIPAMENTO_7 = 0;
    EQUIPAMENTO_8 = 0;
    EQUIPAMENTO_9 = 0;                            
    while (1); /*  {
        problema_ocorrido = 0;
        //Zerar vetor de maquinas com problemas ?
        verificar_estados();
        if (problema_ocorrido != 0){
            faz_ligacao();
            // precisa adicionar um delay grande aqui (15 min) 
        }
    }*/
}
