program calcint;

const Pi=3.141592;

var valor,soma,intervalo:real;

function integral(valor,intervalo:real;var soma:real):real;
var intplus:real;
begin
  intplus:=0;
  while intplus<=valor do
  begin
    trapezio:=(sin(valor)+sin(x-intervalo))/2*(intervalo);
    soma:=soma + trapezio;
    intplus:=intplus+intervalo;
  end;
end;

begin
  writeln('entre com valor entre 0 e Pi');
  readln(valor);

  intervalo:=0.000001; {em intervalos de 0.01}
  integral(valor,intervalo,soma);
  writeln(soma:0:2);
  readln;
end.
