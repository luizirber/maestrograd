CODE 	SEGMENT
		ASSUME 	CS:CODE,DS:CODE
		ORG 	100H
	INICIO:	JMP	CODIGO	
		
                DISP01  DB      "eeeee$"
		DISP02	DB	"Seja bem Vindo !$"
	

	CODIGO:	MOV 	DX,0
		MOV 	DS,DX
		MOV 	DX,1000H
		MOV 	SP,DX		; Define segmento de pilha no endereço 1000h

		
                MOV     DX,400FH        ; Emdereco de programação do 8255 (paralela)
		MOV 	AL,88H		; Palavra de controle (88h)
		OUT 	DX,AL	

		; INICIALIZAÇÃO DO DISPLAY
   	  	MOV     DX,4002H; SAIDA DE DADOS DA PORTA C
		MOV 	BL,0
		MOV 	AL,BL	; ENDEREÇO DE PROGRAMAÇÃO DO DISPLAY
		OUT	DX,AL
		CALL	delay

		MOV	DX,4001H
		MOV	AL,38H	; TIPO DO DISPLAY USADO 2L,5X7
		OUT	DX,AL
		CALL	HABDISP
		CALL	delay
		
		MOV	DX,4001H
		MOV	AL,38H
		OUT	DX,AL
		CALL	HABDISP
		CALL	delay

		MOV	DX,4001H 
		MOV	AL,0FH	; Cursor piscante
		OUT	DX,AL
		CALL	HABDISP
		CALL 	delay

		MOV	DX,4001H 
		MOV	AL,06H	; Sentido do cursor
		OUT	DX,AL
		MOV	DX,4001H
		MOV 	AL,01H
		OUT	DX,AL
		CALL	HABDISP
		CALL	delay
		
		

	LACO:	MOV	DX,4002H ; Configura porta C para saída dos dados
		MOV	BL,01H
		MOV	AL,BL
		OUT	DX,AL


                LEA     DX,DISP01
		CALL	PSTR


		CALL DELAY
		CALL DELAY
		CALL DELAY

		CALL CLEAR
				
		JMP LACO

		
               ; JMP INICIO

		; -------------------------

	; Parametro de caracter AL
	PCHAR	PROC NEAR 
		PUSH 	DX
		MOV	DX,4001H 
		OUT	DX,AL
		CALL	HABDISP
		POP 	DX
		RET
	pCHAR	ENDP
	
	;Limpa display
	CLEAR	PROC NEAR
		PUSH	DX
		PUSH	BX
		PUSH	AX
   	  	MOV     DX,4002H; SAIDA DE DADOS DA PORTA C
		MOV 	BL,0
		MOV 	AL,BL	; ENDEREÇO DE PROGRAMAÇÃO DO DISPLAY
		OUT	DX,AL
		CALL	delay

		MOV	DX,4001H
		MOV	AL,01H	; LIMPA DISPLAY
		OUT	DX,AL
		CALL	HABDISP
		CALL	delay
		POP AX
		POP BX
		POP DX
		RET
	CLEAR	ENDP


	PSTR	PROC NEAR ; PARAMETRO DX
                PUSH    BX
		PUSH	AX
		MOV	BX,DX
                MOV     SI,00H
          PROX: MOV     AL,[100+DISP01+SI]
		CMP	AL,"$"
		JZ	FIM
		CALL	PCHAR
                INC     SI
		JMP 	PROX
		POP	AX
                POP     BX
	   FIM:	RET
	PSTR	ENDP



		
			

    	DELAY  	PROC NEAR
		PUSH 	CX
		MOV 	CX,8000H
	temp:	LOOP 	temp
		POP 	CX
		RET
	DELAY	ENDP

 	HABDISP PROC NEAR
		PUSH 	DX
		MOV 	DX, 4002H	;ENTRADA DE DADOS DA PORTA C
		MOV	AL,BL
		OR	AL,04h
		OUT 	DX,AL

		NOP
		NOP
		NOP
		NOP

		MOV 	AL,BL
		OUT 	DX,AL
		POP 	DX
		RET
	HABDISP	ENDP

		ORG 1ff0H
		JMP INICIO
		CODE 	ENDS
		END 	INICIO


 

