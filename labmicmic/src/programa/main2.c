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

void recebe_ligacao();

void recebe_ligacao() {
    char valor_lido;
    char reading = 1;
    char equipamento = -1;
    char comando =0;
    char liga = 0;
	unsigned int i=0;
	unsigned int j=0;
   /* pulsa o primeiro rele para trocar de circuito */
    P0_0 = 1;
	for (i=0;i<4;i++)
	    for (j=0;j<50000;j++)	
	        Delay();
	        
    P0_5 = 1; /* debug */
    P0_0 = 0;

    P0_1 = 1;
    /* nivel alto no segundo rele, atende o telefone */
	for (i=0;i<4;i++)	
	    for (j=0;j<50000;j++)	
	        Delay();
    
	P0_6=1; /* debug */
    while(reading) {
		P0_7=1; /* debug */
		/* Enquanto o strobe não estiver alto (tecla pressionada), 
		   fica preso nesse loop. */
	    while(P1_4 != 1);
	    P0_3=0; /* debug */
        valor_lido = 1 * P1_0 + 2 * P1_1 + 4 * P1_2 + 8 * P1_3;
        /* if (valor_lido != * && valor_lido != #) */
        if (valor_lido <= 9 && valor_lido > 0){
            equipamento = valor_lido;
            P0_4=0; /* debug */
        }
        else {
        	if (equipamento != -1){
            	/* if (valor_lido == *) LIGA? */
            	if (valor_lido == 11){
               		reading = 0;
              		comando = 1;
            P0_5=0; /* debug */
            	}
            	/* if (valor_lido == #) DESLIGA? */
            	if (valor_lido == 12){
            		reading = 0;
            		comando = 0;
            P0_5=0; /* debug */
            	}
            	/* if (valor_lido == 0) Envia Estado */
            	if (valor_lido == 10){
            		reading = 0;
            		comando = 2;
            P0_5=0; /* debug */
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
		P0_6=0; /* debug */
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
	P0_7=0; /* debug */
}

void faz_ligacao(void){}

void main(void){
    //cria_estados
    EQUIPAMENTO_1 = 0;
    EQUIPAMENTO_2 = 0;
    EQUIPAMENTO_3 = 0;
    EQUIPAMENTO_4 = 0;
    EQUIPAMENTO_5 = 0;
    EQUIPAMENTO_6 = 0;
    EQUIPAMENTO_7 = 0;
    EQUIPAMENTO_8 = 0;
    EQUIPAMENTO_9 = 0;
    while (1) {
	    P0_3=0; /* debug */
	    P0_4=0; /* debug */
	    P0_5=0; /* debug */
	    P0_6=0; /* debug */
	    P0_7=0; /* debug */
        P0_3 = 1; /* debug */                            
        while (P0_2 != 1);
        P0_4 = 1; /* debug */
        recebe_ligacao();
    }
}
