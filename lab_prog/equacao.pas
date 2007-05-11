{ Universidade Federal de Sao Carlos
  Engenharia da Computacao
  Disciplina de Laboratorio de Programacao
  Luiz Carlos Irber Junior , RA 254258}

{Programa que calcula uma funcao de X e Y e retorna o valor da mesma}

{editado e compilado com o FPC}

program equation;

var valorX, valorY,denominador:integer; {valorX e valorY recebem os valores de X e Y}
    valorF:real; {denominador recebe o valor do denominador da funcao e valorF o valor total da funcao}

begin
  for valorX:=1 to 10 do {este laco controla o valor de x}
  begin
    writeln('Valores da funcao para X = ',sqr(valorX),' e para Y variando de 0 a 5');
    for valorY:=0 to 5 do {este laco controla o valor de y}
    begin
      denominador:=(sqr(valorX) * valorY - 5 * valorY - 3 * sqr(valorX) + 15); {calcula o denominador}
      if denominador = 0 then {CONDICAO: verifica se o denominador ‚ igual a zero, o que torna a funcao indefinida}
        writeln('Valor da funcao f( ',sqr(valorX),' , ',valorY,' ) : Funcao Indefinida (denominador eh zero)')
      else {se o denominador eh diferente de 0, continua o calculo}
      begin
        valorF:=(sqr(sqr(valorX))+3*sqr(valorX)+sqr(valorY))/denominador;
        writeln('Valor da funcao f( ',sqr(valorX),' , ',valorY,' ) : ',valorF:0:2);
      end;
    end;
    writeln;
  end;
  readln;
end.
