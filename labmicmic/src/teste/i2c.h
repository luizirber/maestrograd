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

void Delay( void ) {
    
    _asm
    	
    	NOP
    	
    _endasm ;
}

int SendByte( unsigned int BitData[8] ) {

	if ( NoAck == 0 ) {
	    int BitCnt;

	    for ( BitCnt = 0; BitCnt < 8; BitCnt++ ) {
		    //Codigo para enviar bit quando ocorre descida de clock
		    SDAPin = BitData[BitCnt];
		    SCLPin = 1;
		    while ( SCLPin != 1 ); /* Espera SCLPin ficar alto */
		    Delay();
		    SCLPin = 0;
		    Delay();
		}

		SDAPin = 1;
		
		SCLPin = 1;		
		while ( SCLPin != 1 ); /* Espera SCLPin ficar alto */
		
		Delay();
		
		if ( SDAPin != 0 ) {
			NoAck = 1;
		}
		
		SCLPin = 0;
		Delay();
		
		return 0; // Caso a transmissao tenha ocorrido normalmente
	}
	else {
		StopI2C();
		return 1; // Caso a transmissao tenha falhado
	}
}

/*
StartI2C - envia o start ao I2C e o endereco do Slave

*/
void StartI2C( void ) {
    /* Endereco Slave do gerador de Tons */
    unsigned int SlaveAddr[8] = { 0, 1, 0, 0, 1, 0, 0, 0 }; 

    I2CBusy = 1; /* Indica que uma transmissao sera feita */
    NoAck = 0; /* Apaga as flags de erro */
    BusFault = 0; 
    /* Verifica a liberacao do Bus*/
    if ( SCLPin != 0 && SDAPin != 0 ) {
    
    	SDAPin = 0;
    	Delay();
    	SCLPin = 0;
    	Delay();
    	SendByte( SlaveAddr ); /* Envia Endereco do Slave */
    	 
    }
    else { /* Erro */
    	
    	BusFault = 1;
    }
}

void StopI2C( void ) {
	SDAPin = 0;
	SCLPin = 1;
	while ( SCLPin != 1 ); /* Espera SCLPin ficar alto */
	Delay();
	SDAPin = 1;
	Delay();
	I2CBusy = 0;
}

void SendData ( int Tom ) {

    unsigned int Buffer[8];

	StartI2C();
	
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
}
