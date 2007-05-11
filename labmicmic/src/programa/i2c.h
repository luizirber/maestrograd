#include <mcs51/at89x52.h>

#define SCLPin P0_6
#define SDAPin P0_7

char Dados;           /* Dados a serem enviados      */
__bit NoAck;          /* No Acknoledge Flag          */
__bit BusFault;       /* Bus Fault Flag              */
__bit I2CBusy;        /* I2C Busy Flag               */

void StopI2C( void );
void Delay( void );
int SendByte( unsigned int BitData[8] );
void StartI2C( void );
void SendData ( int Tom );

/* 
Delay - Para garantir mudanca nos niveis Alto e Baixo do clock do barramento I2C
	Causa um delay de 5 microssegundos quando eh usado um cristal de 24 Mhz
*/
void Delay( void ) {
    
    _asm
    	
    	NOP
    	NOP
    	NOP
    	NOP
    	NOP
    	NOP
    	
    _endasm ;
}

/*
SendByte - Envia um byte de dados para um dispositivo I2C slave
Entrada: unsigned int BitData[8] = Byte a ser enviado
Retorno: 0 - Caso a transmissao tenha ocorrido corretamente
      	 1 - Caso algum erro tenha ocorrido na transmissao 
*/
int SendByte( unsigned int BitData[8] ) {

	if ( NoAck == 0 ) { /* Verifica se o slave respondeu */
	    int BitCnt; /* Variavel para controle do loop */

	    /* Loop para enviar os 8 bits 
	       Envia 1 a cada descida de clock
	    */
	    for ( BitCnt = 0; BitCnt < 8; BitCnt++ ) {
		    /* Coloca o bit a ser enviado no barramento de dados */
		    SDAPin = BitData[BitCnt];
		    SCLPin = 1; /* Seta o clock do barramento */
		    while ( SCLPin != 1 ); /* Espera SCLPin ficar alto */
		    Delay();
		    SCLPin = 0; /* Reseta o clock do barramento */
		    Delay();
		}

		/* Libera o barramento de dados para receber 
		   o acknowledge do dispositivo escravo
		*/
		SDAPin = 1;
		
		SCLPin = 1; /* Seta o clock do barramento */		
		while ( SCLPin != 1 ); /* Espera SCLPin ficar alto */
		
		Delay();
		
		if ( SDAPin != 0 ) { /* Verifica se recebeu o Ackownledge */
			/* Caso nao tenha recebido seta a Flag para o erro */
			NoAck = 1;
		}
		
		SCLPin = 0; 
		Delay();
		
		return 0; /* Caso a transmissao tenha ocorrido corretamente */
	}
	else {
		StopI2C();
		return 1; /* Caso a transmissao tenha falhado */
	}
}

/*
StartI2C - envia o start ao I2C e o endereco do Slave
*/
void StartI2C( void ) {
    /* Endereco Slave do gerador de tons + R/W */
    unsigned int SlaveAddr[8] = { 0, 1, 0, 0, 1, 0, 0, 0 }; 

    I2CBusy = 1; /* Indica que uma transmissao sera feita */
    NoAck = 0; /* Apaga as flags de erro */
    BusFault = 0; 
    /* Verifica a liberacao do barramento */
    if ( SCLPin != 0 && SDAPin != 0 ) {
    
    	SDAPin = 0; /* Inicia o I2C Start */
    	Delay();
    	SCLPin = 0;
    	Delay(); /* Termina o I2C Start */
    	SendByte( SlaveAddr ); /* Envia o endereco do Slave */
    	 
    }
    else { /* Seta o Flag de erro */
    	
    	BusFault = 1;
    }
}

/*
StopI2C - Envia o Stop ao I2C e libera o Barramento
*/
void StopI2C( void ) {

	SDAPin = 0; /* Prepara o barramento pra receber o Stop */
	SCLPin = 1; /* Seta o clock para o Stop  */
	while ( SCLPin != 1 ); /* Espera SCLPin ficar alto */
	Delay();
	SDAPin = 1; /* Envia o Stop */
	Delay();
	I2CBusy = 0; /* Reseta o Flag de barramento ocupado*/
}

/*
SendData - 
Entrada - int Tom: numero que deve ser gerado como tom DTMF
*/
void SendData ( int Tom ) {

    unsigned int Buffer[8]; /* Armazena o codigo binario de Tom*/
    unsigned int DelayCnt; /* Contador para o delay */

	StartI2C();
	
	/* Converte o Tom para a sequencia de bits q o gerador de DTMF 
	   deve receber */
	Buffer[0] = 0;
	Buffer[1] = 0;
	Buffer[2] = 0;
	Buffer[3] = 1;
	
	switch( Tom ) {
		case 0: Buffer[4] = 0; Buffer[5] = 0; Buffer[6] = 0; Buffer[7] = 0; break;
		case 1: Buffer[4] = 0; Buffer[5] = 0; Buffer[6] = 0; Buffer[7] = 1; break;
		case 2: Buffer[4] = 0; Buffer[5] = 0; Buffer[6] = 1; Buffer[7] = 0; break;
		case 3: Buffer[4] = 0; Buffer[5] = 0; Buffer[6] = 1; Buffer[7] = 1; break;
		case 4: Buffer[4] = 0; Buffer[5] = 1; Buffer[6] = 0; Buffer[7] = 0; break;
		case 5: Buffer[4] = 0; Buffer[5] = 1; Buffer[6] = 0; Buffer[7] = 1; break;
		case 6: Buffer[4] = 0; Buffer[5] = 1; Buffer[6] = 1; Buffer[7] = 0; break;
		case 7: Buffer[4] = 0; Buffer[5] = 1; Buffer[6] = 1; Buffer[7] = 1; break;
		case 8: Buffer[4] = 1; Buffer[5] = 0; Buffer[6] = 0; Buffer[7] = 0; break;
		case 9: Buffer[4] = 0; Buffer[5] = 0; Buffer[6] = 0; Buffer[7] = 1; break;
	}
	
	SendByte( Buffer );
    
	StopI2C();
	
	/* Para permitir que no maximo um tom seja gerado a cada 1/4 segundo */
	for ( DelayCnt = 0; DelayCnt < 50000; DelayCnt++ ) {
		Delay();
	}
}
