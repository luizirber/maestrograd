program banco;

const max=10;

type conta = record
              nome:string[25];
              saldo_cc:real;
              saldo_p:real;
              tempo:integer;
             end;
     vetor = array[1..max] of conta;

var dados:vetor;

 procedure cadastra(var vet:vetor);
 var i:integer;
 begin
   writeln;
   for i:=1 to max do
   begin
     writeln('Cadastro de correntista');
     write('Nome do Correntista: ');
     readln(vet[i].nome);
     write('Saldo em conta corrente: ');
     readln(vet[i].saldo_cc);
     write('Saldo na poupanca: ');
     readln(vet[i].saldo_p);
     write('Tempo (em dias) da conta: ');
     readln(vet[i].tempo);
     writeln;
   end;
 end;

 procedure troca_campo(var dx:vetor;i,j:integer);
 var aux:conta;
 begin
   aux:=dx[i];
   dx[i]:=dx[j];
   dx[j]:=aux;
 end;

 procedure escreva(v:vetor);
 var i:integer;
 begin
   writeln;
   for i:=1 to max do
   begin
     writeln('อออออออออออออออออออออออออออออออออออออออออออออออออออออออ');
     writeln(' Correntista ',v[i].nome,', cliente h  ',v[i].tempo,' dias');
     writeln(' Saldo em conta: ',v[i].saldo_cc:0:2,'   Saldo em Poupanca: ', v[i].saldo_p:0:2);
     writeln('อออออออออออออออออออออออออออออออออออออออออออออออออออออออ');
     writeln;
   end;
 end;

 procedure ordena(var dy:vetor;tipo:integer);
 var i,j:integer;
 begin
   for i:=1 to max-1 do
     for j:=i+1 to max do
     begin
       case tipo of
         1: if dy[i].nome>dy[j].nome then troca_campo(dy,i,j);
         2: if dy[i].tempo<dy[j].tempo then troca_campo(dy,i,j);
         3: if dy[i].saldo_cc<dy[j].saldo_cc then troca_campo(dy,i,j);
         4: if dy[i].saldo_p<dy[j].saldo_p then troca_campo(dy,i,j);
       end;
     end;
     escreva(dy);
 end;

 procedure makemenu(var dt:vetor);
 var op:integer;
 begin
   repeat
     writeln('ษออออออออออออออออออออออออออออออออออป');
     writeln('บ        Sistema de Controle       บ');
     writeln('บ             de contas            บ');
     writeln('ฬออออออออออออออออออออออออออออออออออน');
     writeln('บ 1 - Cadastro                     บ');
     writeln('บ 2 - Ordena por nome              บ');
     writeln('บ 3 - Ordena por tempo de conta    บ');
     writeln('บ 4 - Ordena por saldo C. Corrente บ');
     writeln('บ 5 - Ordena por saldo Poupanca    บ');
     writeln('บ 6 - Sair                         บ');
     writeln('ศออออออออออออออออออออออออออออออออออผ');
     write('Digite sua opฦo: ');
     readln(op);
     while (op<1) or (op>6) do
     begin
       writeln;
       write('opcao invalida. tente novamente');
       readln(op);
     end;
     case op of
       1:cadastra(dt);
       2:ordena(dt,1);
       3:ordena(dt,2);
       4:ordena(dt,3);
       5:ordena(dt,4);
     end;
   until op=6;
 end;

begin
  makemenu(dados);
end.
