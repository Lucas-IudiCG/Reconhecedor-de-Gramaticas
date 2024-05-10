//Gabriel Ramires TIA:42080681
//Lucas Iudi Corregliano Gallinari TIA:32138628
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//O codigo funciona tentando recriar a expressao lida em "input.txt",
//array chamado "expressao",se o codigo rodaria sem problema, vai gerar uma expressao possivel
//que sera verificado, caso contrario, o programa vai identificar o erro
//e baseado na posição do caracter errado pode dizer em qual linha deu o problema

//no vetor expressao, os estados terminais são simplicados em letras, D= int, V=variavel,
//N= número,T= Termo(+,-), F=Fator(*,/),f='=', |=;, != fim do programa, S= erro.

char letra[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char digito[10]={'0','1','2','3','4','5','6','7','8','9'};
char Operadores[4]={'-','+','/','*'};
int Pulos[100];//as varaiveis pulos e Jump, servem para medir quando começa uma linha e termina a outra
int jump=0;
int y=0;// y é index de expressao, e z é o index do input.
int z=0;
int Par;//determina o numero de parenteses
int Parcoods;//determina o index do parenteses, que ocorreu o erro.
int linha=1;// quantidade total de linhas

void IgnoraEspaco(char *inputs,char *expressao){// a função ignora os espaços da função, conta linhas e determina aonde uma linha começa e finaliza
  while(inputs[z]== '\n' || inputs[z]==' '){
    if(inputs[z]== '\n'){
      linha++;
      Pulos[jump]=y;
      jump++;
    }
    z++;
  }
}

void FimComando(char *inputs,char *expressao){// determina aonde tem ';'
  if(inputs[z]==';' && expressao[y-1]!='|'){
    if(inputs[z+1]==';'){
      expressao[y]='|';
      y++;
    }
    expressao[y]='|';
      y++;
  }
}

bool Parenteses(char t){// conta os parenteses aberto e fechados.
  if(t=='('){//se abrir um parenteses, o Par aumenta em um
    Par++;
    Parcoods=y;
    return true;
  }
  if(t==')'){//se fechar um parenteses, o Par diminui em um
    Par--;
    Parcoods=y;
    return true;
  }
  return false;
}

bool Pertence(char l){// verifica se a é uma letra aceitavel.
  for(int a=0;a<26;a++){
    if(l==letra[a])
    return true;
  }
  return false;
}

bool Numero(char n){//verifica se e um numero aceitavel
  for(int a=0;a<10;a++){
    if(n==digito[a])
    return true;
  }
  return false;
}

bool Variavel(char* inputs,char* expressao,char parada){//verifica se tem variavel
  int a=z;
  IgnoraEspaco(inputs,expressao);
  if(Numero(inputs[z])){//em caso de alguém escrever um número no lugar de uma variavel, o que é errado.
     expressao[y]='N';
    y++;
  }
  while(inputs[z]!=parada && Pertence(inputs[z])){// verifica se tem uma variavel legivel
    z++;
  }
  if(z-a>0){//verifica se a variavel tem tamanho maior que 0.
    expressao[y]='V';
    y++;
    FimComando(inputs,expressao);
    return true;
  }
  return false;
}

bool funcao(char op){// verifica se for (*,/)
  for(int a=2;a<4;a++){
    if(op==Operadores[a])
    return true;
  }
  return false;
}

bool termo(char op){// verifica se for (+,-)
  for(int a=0;a<2;a++){
    if(op==Operadores[a])
    return true;
  }
  return false;
}

bool Expr(char* inputs,char* expressao){
  z++;
  IgnoraEspaco(inputs,expressao);
  if(termo(inputs[z]) && expressao[y-1]!='F'){//adicona um termo na função, ou seja(+,-)
      expressao[y]='T';
      y++;
      Expr(inputs,expressao);
  }
    int a=z;
  while(Numero(inputs[z])){// verifica se tem um número possivel
    z++;
  }
  if(inputs[z]==' ' && Numero(inputs[z+1])){//verifica se tem um espaço entre os números se sim, é adicionado um "lixo" na expressao para indicar no lixo.
    expressao[y]='S';
    y++;
  }
  if(Parenteses(inputs[z])){//verifica parenteses
    Expr(inputs,expressao);

  }
  if(z-a>0){// calcula e adiciona um número
    IgnoraEspaco(inputs,expressao);
    if(Numero(inputs[a])){
    expressao[y]='N';
    y++;
    FimComando(inputs,expressao);
    }
    //verifica se tem termo ou função depois
    if(funcao(inputs[z])){
      expressao[y]='F';
      y++;
      Expr(inputs,expressao);
      FimComando(inputs,expressao);
    }
    if(termo(inputs[z])){
      expressao[y]='T';
      y++;
      Expr(inputs,expressao);
      FimComando(inputs,expressao);
    }
    return true;
  }
  return false;
}

bool Atribuicao(char* inputs,char* expressao){//calcula a atribuição varivel + expressao;
  if(Variavel(inputs,expressao,'=')){
    expressao[y]='f';
    y++;
    IgnoraEspaco(inputs,expressao);
    Expr(inputs,expressao);


}
}

void Comando(char* inputs,char* expressao){
  if(Atribuicao(inputs,expressao)){
  }
}

void Declaracao(char* inputs,char* expressao){
  if(inputs[z]=='i'&& inputs[z+1]=='n' && inputs[z+2]=='t'){//verifica as declarações.
    expressao[y]='D';
  y++;
    z=z+3;
    IgnoraEspaco(inputs,expressao);
    if(Variavel(inputs,expressao,';')){
    }
  }
}

void programa(char* inputs,char * expressao, int x){
  for(z=0;z<x;z++){// repete os programa até acabar.
  IgnoraEspaco(inputs,expressao);
  //printf("| %c |",inputs[z]);
  Declaracao(inputs,expressao);
  IgnoraEspaco(inputs,expressao);
  //printf("! %c !",inputs[z]);
  Comando(inputs,expressao);
  //IgnoraEspaco(inputs);

}
}

int leitura(char *inputs){//le o "input.txt", e ignora se tiver comentario, e retorna o tamanho do arquivo.
  FILE  *textfile;// define um FILE
  int a=0;
  textfile = fopen("input.txt", "r");
  inputs[a]=fgetc(textfile);
  while(inputs[a]!=EOF){
    a++;
    inputs[a]=fgetc(textfile);
    if(inputs[a]=='/' && inputs[a-1]=='/'){
      inputs[a]='\0';
      inputs[a-1]='\n';
      a=a-1;
      while(fgetc(textfile)!='\n'){

      }
    }
}
  inputs[a]='\0';
fclose(textfile);
return a;
}

int VerificarGramatica(char* expressao,int i){
  //Declaração::=int <variavel>;, ou seja.
  //D->V|
  if(expressao[i]=='D'){
    if(expressao[i+1]=='V'){
      if(expressao[i+2]=='|' ){
      return VerificarGramatica(expressao,i+2);
    }
      if(expressao[i+2]=='!'){
        return VerificarGramatica(expressao,i+1);
      }
    }
  }
  //Atribuição::=<variavel>=<expr>, ou Declaração::=int <variavel>;.
  //V->f ,ou D->V|
  if(expressao[i]=='V'){
    if(expressao[i+1]=='f'|| expressao[i+1]=='|'){
      return VerificarGramatica(expressao,i+1);
    }
  }
  //'=' ::= <expr>,ou seja
  //f-> +,- N, F->N
  if(expressao[i]=='f'){
    if(expressao[i+1]=='T'){
      return VerificarGramatica(expressao,i+1); ;
    }
    if(expressao[i+1]=='!'){
      return i-1;
    }
    if(expressao[i+1]=='N' ){
      return VerificarGramatica(expressao,i+1);
    }
  }
  //basicamente só não pode ter variavel depois de número, tambem não pode declaração mas é impossivel gerar declaração depois de número antes de um ';', neste programa.
  if(expressao[i]=='N'){
    if(expressao[i+1]=='V'){
      return i;
    }
    if((expressao[i+1]=='F' ||expressao[i+1]=='T' || expressao[i+1]=='|')&& expressao[i-1]!='|' ){
      return VerificarGramatica(expressao,i+1);
    }
  }
  // se tiver (*,/), precisa term um número ou um +ou- depois.
  if(expressao[i]=='F'){
    if(expressao[i+1]=='N'|| expressao[i+1]=='T'){
     return  VerificarGramatica(expressao,i+1);
    }
  }
  // se tiver (+,-), precisa term um número depois.
  if(expressao[i]=='T'){
    if(expressao[i+1]=='N'){
     return  VerificarGramatica(expressao,i+1);
    }
  }
  //fim da expressão
  if(expressao[i]=='!'){
    return i;
  }
  // se tiver ; seguido de ;.
  if(expressao[i]=='|'){
    if(expressao[i+1]=='|'){
      return i;
    }
    //se tiver ; no final.
      if(expressao[i+1]=='!'){
      return i-1;
    }
    else{
    return VerificarGramatica(expressao,i+1);
  }
  }
  else{
    return i;
  }

}

int main(void) {
  char inputs[1000];//cria um inputs para armazena o aruivo txt.
  char expressao[100];
  Pulos[0]=0;
  jump++;
  int a;
  for (a=0;a<1000;a++){
    inputs[a]='\0';
  }
  for (a=0;a<100;a++){
    expressao[a]='\0';
  }
  int x=leitura(inputs);
 programa(inputs,expressao,x);//cria a expressão.
  Pulos[jump]=y;
  expressao[y]='!';
  int i=VerificarGramatica(expressao,0);
  if(i==y-1 && Par==0){
  printf("Entrada aceita sem erros");
  printf("\n%d linhas analisadas\n",linha);

  }
  else{
  printf("Falha na derivação");
  if(Par==0 ){
  for (a=1;a<jump+2;a++){
    if(Pulos[a-1]<=i && i<Pulos[a]){
      printf("\nErro na Linha %d",a);
    }

  }
  }
  else{// aqui é o parenteses
     for (a=1;a<jump+2;a++){
        if(Pulos[a-1]<=Parcoods && Parcoods<Pulos[a]){
          printf("\nErro na Linha %d",a);
    }
     }
  }
  }

  return 0;
}
