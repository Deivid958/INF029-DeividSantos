// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Deivid Santos de Souza
//  email: 20251160028@ifba.edu.br
//  Matrícula: 20251160028
//  Semestre: 2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
  int datavalida = 1;
  int bissexto = 0;
  //quebrar a string data em strings sDia, sMes, sAno
  DataQuebrada da = quebraData(data);
  if(da.valido == 1){    
    if(da.iAno >= 10 && da.iAno < 100){
      da.iAno = da.iAno + 2000;
    }
    if((da.iAno % 400 == 0)||(da.iAno % 4 == 0 && da.iAno % 100 != 0)){
      bissexto = 1;
    } 
    switch (da.iMes){
      case 1:case 3:case 5:case 7:case 8:case 10:case 12:{          
        if(da.iDia < 1 || da.iDia > 31)
          datavalida = 0;
        break;
      }
      case 2:{
        if(bissexto == 1){
          if(da.iDia < 1 || da.iDia > 29)
            datavalida = 0;
        }
        else{
          if(da.iDia < 1 || da.iDia > 28)
            datavalida = 0;
        }
        break;
      }
      case 4:case 6:case 9:case 11:{
        if(da.iDia < 1 || da.iDia > 30)
          datavalida = 0;
        break;
      } 
      default:{
        datavalida = 0;
        break;
      }
    }
  }
  else{ 
    datavalida = 0;
  } 
  //printf("%s\n", data);
 
  if (datavalida)
      return 1;
  else
      return 0;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;
    int passa,inicioDia,inicioMes,inicioAno,i,fimDia,fimMes,fimAno;
    inicioDia = inicioMes = inicioAno = fimDia = fimMes = fimAno = 0;
    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else{
      //verifique se a data final não é menor que a data inicial
      passa = 0;
      for(i = 0;datainicial[i] != '\0';i++){
        if(datainicial[i] == '/'){
          passa++;
        }
        else if(passa == 0){
          inicioDia = inicioDia * 10 + (datainicial[i] - '0');
        }
        else if(passa == 1){
          inicioMes = inicioMes * 10 + (datainicial[i] - '0');
        }
        else{
          inicioAno = inicioAno * 10 + (datainicial[i] - '0');
        }
      }
      passa = 0;
      for(i = 0;datafinal[i] != '\0';i++){
        if(datafinal[i] == '/'){
          passa++;
        }
        else if(passa == 0){
          fimDia = fimDia * 10 + (datafinal[i] - '0');
        }
        else if(passa == 1){
          fimMes = fimMes * 10 + (datafinal[i] - '0');
        }
        else{
          fimAno = fimAno * 10 + (datafinal[i] - '0');
        }
      }
      if(inicioAno > fimAno || inicioMes > fimMes || inicioDia > fimDia){
        dma.retorno = 4;
        return dma;
      }
      //calcule a distancia entre as datas
      
      dma.qtdAnos = fimAno - inicioAno;
      dma.qtdMeses = fimMes - inicioMes;
      if(inicioDia == fimDia)
        dma.qtdDias = 0;
      else
        dma.qtdDias = fimDia - inicioDia;
      //se tudo der certo
      dma.retorno = 1;
      return dma;

    }
    
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0,i,j;
    if(isCaseSensitive == 1){
      for(i = 0;texto[i] != '\0';i++){
        if(texto[i] == c){
          qtdOcorrencias++;
        }
      }
    }
    else{
      for(i = 0;texto[i] != '\0';i++){
        if(texto[i] == c){
          qtdOcorrencias++;
        }
        else{
          for(j = 0;j < 27;j++){
            if((texto[i] == 'a'+j && c == 'A'+j) || (texto[i] == 'A'+j && c == 'a'+j)){
              qtdOcorrencias++;
              break;
            }
          }
        }
      }
    }
    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int i,j,ipos;
    int valido = 1,aux;
    j = ipos = aux =0;
    for(i = 0;strTexto[i] != '\0';i++){
      if(strTexto[i] < 0 || strTexto[i] > 128){
        aux++;
        i++;
        continue;
      }
      else if(strTexto[i] == strBusca[j]){
        posicoes[ipos] = i+1-aux;
        for(j = 1;strBusca[j] != '\0';j++){
          if(strTexto[i] < 0 || strTexto[i] > 128){
            aux++;
            i++;
            valido = 0;
            break;
          }
          else if(strTexto[i+j] != strBusca[j]){
            valido = 0;
            break;
          }
        }
        if(valido){
          posicoes[++ipos] = i+j-aux;
          ipos++;
          qtdOcorrencias++;
        }
        valido = 1;
        j = 0;
      }
    }
    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
  int aux = 0;
  for(num;num != 0;num /= 10){
    aux = aux*10 + (num%10);
  }
  num = aux;
  return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0,qtdbusca = 0,aux;
    for(aux = numerobusca;aux != 0;aux/=10){
      if(qtdbusca == 1)
        qtdbusca *= 10;
      else
        qtdbusca++;
    }
    if(qtdbusca != 0){
      for(numerobase;numerobase != 0;numerobase /= 10){
        aux = numerobase % (10*qtdbusca);
        if(aux == numerobusca){
          qtdOcorrencias++;
        }
      }
    }
    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */
int acha(char matriz[8][10],int i, int j,char palavra[6],int a,int b){
  int k = 1;
  while(matriz[i][j] != '\0' && i >= 0 && i >= 0){
    if(a == 1)
      i++;
    else if(a == -1)
      i--;
    if(b == 1)
      j++;
    else if( b == -1)
      j--;

    if(matriz[i][j] != palavra[k] || k == 5){
      break;
    }
    k++;
  }
  if(k == 5)
    return 1;
  else
    return 0;
}
int q7(char matriz[8][10], char palavra[6])
{
  int a = 0;
  int i,j;
  for(i = 0;matriz[i][0] != '\0';i++){
    for(j = 0;matriz[i][j] != '\0';j++){
      if(matriz[i][j] == palavra[0]){

        if(i > 0 && (i != 0 && matriz[i-1][j] == palavra[1])){
          a = acha(matriz,i,j,palavra,-1,0);
          if(a == 1){
            return a;
          }
        }

        if(j > 0 &&(j != 0 && matriz[i][j-1] == palavra[1])){
          a = acha(matriz,i,j,palavra,0,-1);
          if(a == 1){
            return a;
          }
        }

        if(i < 8 &&(matriz[i+1][j] == palavra[1])){
          a = acha(matriz,i,j,palavra,1,0);
          if(a == 1){
            return a;
          }
        }
        
        if(j < 10 &&(matriz[i][j+1] == palavra[1])){
          a = acha(matriz,i,j,palavra,0,1);
          if(a == 1){
            return a;
          }
        }

        if(i < 8 && j > 0 &&(matriz[i+1][j-1] == palavra[1])){
          a = acha(matriz,i,j,palavra,1,-1);
          if(a == 1){
            return a;
          }
        }

        if(i < 8 && j < 10 &&(matriz[i+1][j+1] == palavra[1])){
          a = acha(matriz,i,j,palavra,1,1);
          if(a == 1){
            return a;
          }
        }
        

        if(i > 0 && j > 0 &&(matriz[i-1][j-1] == palavra[1])){
          a = acha(matriz,i,j,palavra,-1,-1);
          if(a == 1){
            return a;
          }
        }

        if(i > 0 && j < 10 &&(matriz[i-1][j+1] == palavra[1])){
          a = acha(matriz,i,j,palavra,-1,1);
          if(a == 1){
            return a;
          }
        } 
      }
    }
    j = i;
  }
  return a;
}

DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}

