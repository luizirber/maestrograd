{
  Programa... : INTGREG.PAS
  Programador : Jonas Murilo Antunes
  Ult. Modif. : 02/11/1997
  Prop¢sito.. : Determinar o valor de uma f(x) em fun‡„o dos
                dados de entrada, utilizando o M‚todo da Interpola‡Æo pelos
                Polin“mios de Gregory Newton com Diferen‡as Divididas
  Aplica‡Æo.. : Dada a tabela abaixo, determinar o valor aproximado de f(0,4)
                x     :  0,0    0,2    0,3    0,5    0,6
                f(x)  :  1,008  1,064  1,125  1,343  1,512

}

program intgreg;
uses
  Crt;

const
   nPoints = 30;  { n§ de pontos }

type
  { estrutura padrÆo para os vetores }
  aStructure = Array[1..nPoints] of real;

var
  n, ordem           : integer;     { n£mero de dados e a ordem da dif.dividida}
  x                  : real;        { coordenada utilizada p/ determinar y=f(x) }
  aX, aY             : aStructure;  { valores de entrada }
  p, px              : real;        { polinomios }
  i,j                : integer;     { indices }
  cContinue          : char;        { controle de repeticao }


{
  Procedure  : SAY
  Finalidade : Exibe um texto na linha e coluna especifados em cores
  Sintaxe    : nLin       = coordenada da linha  ( 1..24 )
               nCol       = coordenada da coluna ( 1..78 )
               cSting     = texto a ser exibido
               nColorFore = n§ da cor de frente do texto (use constantes)
               nColorBack = n§ da cor de fundo  do texto (use constantes)
}
Procedure Say( nLin,nCol:integer; cString : string; nColorFore,nColorBack:integer);
begin
    TextColor(nColorFore);
    TextBackGround(nColorBack);
    GotoXY(nCol, nLin);
    Write(cString);
end;


{
  Procedure  : runData
  Finalidade : obtem os valores de n,x,y e a coordenada x
               estes valores sao passados por referencia
}
Procedure runData( var n :integer; var aX, aY :aStructure; var x: real);
begin
  Say(03,10,'Entre com o n£mero de pontos....... :',Green,Black);
  Say(03,48,'',White,Blue);
  Read(n);

  for i:=1 to n do
  begin
    Say(05,10,'                                         ',Green,Black);
    Say(06,10,'                                         ',Green,Black);
    Say(05,10,'Entre com o Valor de X(',Green,Black);
    Write(i-1);
    Write(').......... :');
    Say(05,48,'',White,Blue);
    Read(aX[i]);
    Say(06,10,'Entre com o Valor de Y(',Green,Black);
    Write(i-1);
    Write(').......... :');
    Say(06,48,'',White,Blue);
    Read(aY[i]);
  end;
  Say(07,10,'Entre com X p/ determinar Y........ :',Green,Black);
  Say(07,48,'',White,Blue);
  Read(x);

end;

{
  Procedure  : runProcess
  Finalidade : calcula o polin“mio de Gregory Newton
}
function difDiv( ordem, i: integer) : Real; forward;
Procedure runProcess( aX, aY :aStructure; var px : real);
var
  difDividida : real ;
begin
   ordem := n-1;
         px := 0;
   for i := 1 to ordem do
   begin
     p := 1;
     for j := 0 to i-1 do
       p := p * (x-aX[j+1]);
     difDividida := difDiv( i, 0);
     px := px + ( difDividida *p );
   end;
   px := aY[1] + px;
end;

function difDiv( ordem, i: integer) : real;
var
  vAux, difDiv1, difDiv2 : real;
begin
  if ordem = 0 then
     vAux := aY[i]
  else
    begin
      difDiv1 := difDiv(ordem-1,i+2);
      difDiv2 := difDiv(ordem-1,i+1);
      vAux :=  (difDiv1 - difDiv2) / (aX[i+1+ordem]-aX[i+1]);
  end;
  difDiv := vAux;
end;
{
  Procedure  : runResult
  Finalidade : exibe a equa‡Æo da reta
}
Procedure runResult;
begin
  Say(08,02,'O valor de f(',Yellow,Black);
  Write(x:8:4,')  ‚',px:8:4);
end;

{ Rotina Principal }
Begin
  cContinue := 'S';
  While NOT(UpCase(cContinue)='N') Do begin
    TextColor(White);
    TextBackGround(Black);
    ClrScr;
    Say( 01,01, 'Interpola‡Æo pelos Polin“mios de Lagrange',White, Red );
    runData(n, aX, aY, x);
    runProcess( aX, aY, px);
    runResult;

    Say(24,01,'Deseja novo C lculo ??? <S/N>',Magenta,Black);
    cContinue := readKey;
  end;

End.
