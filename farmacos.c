// esse projeto foi desenvolvido em uma máteria de programação imperativa onde a professora trouxe o codigo base
// e foi necessario que eu implementasse algumas melhorias no código (melhorias essas que estão identificadas) e criasse novas funções.
#include <stdio.h>
#include <stdlib.h>  //usado system
#include <ctype.h>   //usado toupper
#include <string.h>  //usado strcmp

struct TpFarma{
	char Nome[21];
	float Preco;
	int QEstoque;
  };
  
typedef struct TpFarma TpFARMA;


TpFARMA RgFarma;
  
FILE *ArqFarma;

long int Tamanho= sizeof(TpFARMA);//21*sizeof(char)+sizeof(float)+sizeof(int);

void Incluir() {
  char R; char nome[21]; int Achou=0,estoque_temp;
  do{
    //system("cls");
     printf("*** inclusao ***\n\n");
     printf("Nome: ");
     scanf("%s",nome);
     Achou = 0;
     fseek(ArqFarma,0,SEEK_SET);
      do{
	     fread(&RgFarma,Tamanho,1,ArqFarma);
	     if (strcmp(RgFarma.Nome,nome)==0 ){
	    Achou=1;	
	    printf("o remedio ja esta no sistema ou foi excluido");
      return;}}
  while (!feof(ArqFarma) && (Achou==0));
  if (Achou==0)
    strcpy (RgFarma.Nome, nome);
    printf("Preco: ");
    scanf("%f",&RgFarma.Preco);
    do{
    
    printf("Estoque: ");
    scanf("%d",&estoque_temp);
    if(estoque_temp>=0){
    RgFarma.QEstoque = estoque_temp;
    }
    else{
      printf("digite um numero positivo!\n");
      // foi realizada uma melhoria ao impossibilitar o usuário de colocar estoques negativos, evitando assim possiveis erros no funcionamento do programa.
    }} while (estoque_temp < 0);
    fseek(ArqFarma,0,2);
    fwrite(&RgFarma,Tamanho,1,ArqFarma);
    printf("\nNova inclusao? S/N ");
    scanf(" %c",&R);
    R=toupper(R);}
 while (R!='N');
  return;}
  //system("pause");

long int TArquivo(){
	fseek(ArqFarma,0,2);
	long int R=ftell(ArqFarma)/Tamanho;
	return R;}
  
void Excluir(){
   if (TArquivo()!=0){
    fclose(ArqFarma); //modo a + b
    ArqFarma=fopen("Farmacos.dat","r+b");
    //system("cls");
    printf("*** excluir ***\n\n");  
    fseek(ArqFarma,0,0);
    printf("Qual farmaco voce deseja excluir ? ");
    char Farmaco[21];
    scanf("%s",Farmaco);
    int Achou=0;
    do {
	    fread(&RgFarma,Tamanho,1,ArqFarma);
	    if (strcmp(RgFarma.Nome,Farmaco)==0){
	      Achou=1;	
	     }}
    while (!feof(ArqFarma) && (Achou==0));
    if (Achou==0) {
      printf("Registro inexistente!"); }
    else{
    
     RgFarma.QEstoque = -1;
      fseek(ArqFarma,-Tamanho,1);
      fwrite(&RgFarma,Tamanho,1,ArqFarma);
      printf(">>> exclusao efetuada com sucesso! <<<\n");}
      //system("pause");
    fclose(ArqFarma);
    ArqFarma=fopen("Farmacos.dat","a+b");}
  else{
    printf("Arquivo Vazio.  Nao existem dados para excluir.");}
    //system("pause");
  return;
}
	
void Alterar(){
  if (TArquivo()!=0){
    fclose(ArqFarma); //modo a + b
    ArqFarma=fopen("Farmacos.dat","r+b");
    //system("cls");
    printf("*** alterar ***\n\n");  
    fseek(ArqFarma,0,0);
    printf("Qual farmaco? ");
    char Farmaco[21];
    scanf("%s",Farmaco);
    int Achou=0;
    do {
	    fread(&RgFarma,Tamanho,1,ArqFarma);
	    if (strcmp(RgFarma.Nome,Farmaco)==0){
	      Achou=1;	
	      printf("Nome: %s\n",RgFarma.Nome);
        printf("Valor: %f\n",RgFarma.Preco);
        printf("Estoque: %d\n",RgFarma.QEstoque);}}
    while (!feof(ArqFarma) && (Achou==0));
    if (Achou==0) {
      printf("Registro inexistente!"); }
    else{
      printf("Qual o novo preco? \n"); 
      scanf("%f",&RgFarma.Preco);
      printf("Qual a nova quantidade? \n");
      scanf("%d",&RgFarma.QEstoque);
      fseek(ArqFarma,-Tamanho,1);
      fwrite(&RgFarma,Tamanho,1,ArqFarma);
      printf(">>> Alteracao efetuada com sucesso! <<<\n");}
      //system("pause");
    fclose(ArqFarma);
    ArqFarma=fopen("Farmacos.dat","a+b");}
  else{
    printf("Arquivo Vazio.  Nao existem dados a alterar.");}
    //system("pause");
  return;}

void Consultar(){
  //system("cls");
  printf("*** consulta ***\n\n");  
  fseek(ArqFarma,0,0);
  printf("Qual farmaco? ");
  char Farmaco[21];
  scanf("%s",Farmaco);
  int Achou=0;
  do{
	  fread(&RgFarma,Tamanho,1,ArqFarma);
	  if (strcmp(RgFarma.Nome,Farmaco)==0 && RgFarma.QEstoque >= 0 ){
	    Achou=1;	
	    printf("Nome: %s\n",RgFarma.Nome);
      printf("Valor: R$%.2f\n",RgFarma.Preco);
      printf("Estoque: %d\n",RgFarma.QEstoque);}}
  while (!feof(ArqFarma) && (Achou==0));
  if (Achou==0) {
    printf("Registro inexistente!");
    }
  //system("pause");
  return;}

void LTodos(){
  //system("cls");
  printf("*** lista todos ***\n\n"); 
  fseek(ArqFarma,0,0);
  while (fread(&RgFarma,Tamanho,1,ArqFarma)== 1) {
	
	     if (RgFarma.QEstoque != -1){
	    printf("Nome: %s\n",RgFarma.Nome);
      printf("Valor: R$%.2f\n",RgFarma.Preco);
      printf("Estoque: %d\n",RgFarma.QEstoque);
      printf("***\n\n");}}

  //system("pause");
  }
  
void Dbug(){
  //system("cls");
  printf("*** lista todos ***\n\n"); 
  fseek(ArqFarma,0,0);
  while (fread(&RgFarma,Tamanho,1,ArqFarma)== 1) {
	
	    printf("Nome: %s\n",RgFarma.Nome);
      printf("Valor: R$%.2f\n",RgFarma.Preco);
      printf("Estoque: %d\n",RgFarma.QEstoque);
      printf("***\n\n");}
  
  //system("pause");
  }
void Recuperar(){ // melhoria dois, foi criada uma função para recuperar farmacos excluidos anteriormente.
  //system("cls");
  printf("*** recuperar itens excluidos ***\n\n");  
  fseek(ArqFarma,0,0);
  printf("Qual item voce quer recuperar? ");
  char item[21];
  scanf("%s",item);
  int Achou=0 , posicao= -1;
  do{ 
    posicao++;
	  fread(&RgFarma,Tamanho,1,ArqFarma);
	  if (strcmp(RgFarma.Nome,item)==0 && RgFarma.QEstoque >= 0 ){
	   	
	    printf("esse item nao foi excluido");
      break;}
    if (strcmp(RgFarma.Nome,item)==0 && RgFarma.QEstoque < 0) {
      RgFarma.QEstoque = 0;
       Achou=1;
      fclose(ArqFarma);
      ArqFarma=fopen("Farmacos.dat","r+b");
      fseek(ArqFarma,posicao*Tamanho,0);
      fwrite(&RgFarma,Tamanho,1,ArqFarma);
      fclose (ArqFarma);
      ArqFarma=fopen("Farmacos.dat","a+b");
      printf("o item foi recuperado");
      break;
      }}
   
  while (!feof(ArqFarma) && (Achou==0));
  if (Achou == 0) {
  printf("esse item nao foi encontrado");
  }
  
  //system("pause");
  return;
}


int main(){
  ArqFarma=fopen("Farmacos.dat","a+b");
  char Opcao;
  do{
	  //system("cls");
    printf("\n\n> > > Pague Pouco < < < \n\n");
    printf("Que deseja fazer? \n\n");
    printf("I - Incluir \n");  
    printf("E - Excluir \n");
    printf("A - Alterar \n");
    printf("C - Consultar \n");
    printf("T - Listar Todos \n");
    printf("R- Recuperar\n");
    printf("S - Sair \n\n");
  
    scanf(" %c", &Opcao);
    Opcao=toupper(Opcao);
    switch (Opcao){
      case 'I': Incluir(); break; 
      case 'E': Excluir(); break; 
      case 'A': Alterar(); break; 
      case 'C': Consultar(); break; 
      case 'T': LTodos(); break;
      case 'R': Recuperar(); break;
      case 'D': Dbug ();break;
      }} 
  while (Opcao != 'S');
  fclose(ArqFarma);
  return 0;}
