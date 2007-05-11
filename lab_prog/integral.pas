program calcint;

const Pi=3.141592;

var valor,intervalo:real;

function integral(valor,intervalo:real):real;
var intplus,soma:real;
begin
  intplus:=0;
  while intplus<=valor do
  begin
    soma:=soma + (sin(intplus+intervalo)+sin(intplus))*0.5*intervalo;
    intplus:=intplus+intervalo;
  end;
  integral:=soma;
end;

begin
  writeln('entre com valor entre 0 e Pi');
  readln(valor);
  while (valor<0) or (valor>Pi) do
  begin
    writeln('fora do intervalo. Insira valor novamente');
    readln(valor);
  end;
  intervalo:=0.000001; {em intervalos de 0.01}
  writeln(integral(valor,intervalo):0:2);
  readln;
end.