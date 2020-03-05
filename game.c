
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int tabuleiro = 4;
void menuInicial(int matriz[][tabuleiro], int *placar, int * numerojogadas);


int gerarNum();
typedef struct dadosRecorde{//estrutura para guardar os dados dos 5 melhores recordes
	char nome[10];
	int valor;
}R;
typedef struct posicaoVazia{ // estrutura para guardar as posi��es vazias do tabuleiro
	int linha;
	int coluna;
	int tamanho; // tamanho � usado para alocar dinamicamente um vetor de posi��es vazias
}P;


void carregargame(int tabuleiro, int matriz[][tabuleiro],int * placar, int *numerodejogadas){
	FILE * fp;
	int i,j,a,b;
	//se tabuleiro for 3x3
	if(tabuleiro==3){
		fp=fopen("3salvo.txt","r");
		for(i=0;i<tabuleiro;i++){
			if(i==0){
				fscanf(fp,"%d %d",&a,&b);
			}
			for(j=0;j<tabuleiro;j++){
				fscanf(fp,"%d\t",&matriz[i][j]);
			}
		}
	}
	//se tabuleiro for 4x4
	if(tabuleiro==4){
		fp=fopen("4salvo.txt","r");
		for(i=0;i<tabuleiro;i++){
			if(i==0){
				fscanf(fp,"%d %d",&a,&b);
			}
			for(j=0;j<tabuleiro;j++){
				fscanf(fp,"%d\t",&matriz[i][j]);
			}
		}
	}
	//se tabuleiro for 5x5
	if(tabuleiro==5){
		fp=fopen("5salvo.txt","r");
		for(i=0;i<tabuleiro;i++){
			if(i==0){
				fscanf(fp,"%d %d",&a,&b);
			}
			for(j=0;j<tabuleiro;j++){
				fscanf(fp,"%d",&matriz[i][j]);
			}
		}
	}
	fclose(fp);
	*placar=a;
	*numerodejogadas=b;
}

void salvargame(int tabuleiro, int matriz[][tabuleiro],int * placar, int *numerodejogadas){

	FILE * fp;
	int i,j,a,b;

		if(tabuleiro==3){
			fp=fopen("3salvo.txt","w+");
			for(i=0;i<tabuleiro;i++){
				if(i==0){
					fprintf(fp,"%d %d\n\n",*placar,*numerodejogadas);
				}
				for(j=0;j<tabuleiro;j++){
					fprintf(fp,"%d\t",matriz[i][j]);
				}
			}

		}
		if(tabuleiro==4){
			fp=fopen("4salvo.txt","w+");
			for(i=0;i<tabuleiro;i++){
				if(i==0){
					fprintf(fp,"%d %d\n",*placar,*numerodejogadas);
				}
				for(j=0;j<tabuleiro;j++){
					fprintf(fp,"%d\t",matriz[i][j]);
				}
			}
		}
		if(tabuleiro==5){
			fp=fopen("5salvo.txt","w+");
			for(i=0;i<tabuleiro;i++){
				if(i==0){
					fprintf(fp,"%d %d\n",*placar,*numerodejogadas);
				}
				for(j=0;j<tabuleiro;j++){
					fprintf(fp,"%d\t",matriz[i][j]);
				}
			}
		}
	fclose(fp);
}



P * espacaovazio(int matriz[][tabuleiro]){  // preenche um vetor com as posi��es vazias do tabuleiro(posi��es que podem receber numeros aleat�rios ap�s alguma movimenta��o)
	int i,j,cont=0;
	P * vetor;
	for(i=0;i<tabuleiro;i++){
		for(j=0;j<tabuleiro;j++){
			if(matriz[i][j]==0){//  encontra uma posi��o da matriz com o valor 0
				cont++; //contador � incrementado
			}
		}
	}

	vetor=(P*)malloc(cont*sizeof(P)); // � alocado um vetor do tipo P de tamanho igual ao contador, ou seja, com o mesmo numero de posi�oes vazias do tabuleiro
	(vetor)[0].tamanho=cont; //a variavel tamanho,contida no vetor[0], recebe o valor de contador

	cont=0;
	for(i=0;i<tabuleiro;i++){
		for(j=0;j<tabuleiro;j++){
			if(matriz[i][j]==0){ //encontra uma posi��o da matriz com o valor 0
				(vetor)[cont].linha=i; // o campo linha do vetor recebe a linha que contem um elemento igual a  0
				(vetor)[cont].coluna=j; // o campo linha do vetor recebe a linha que contem um elemento igual a  0
				cont++;
			}
		}
	}

	return vetor; // retorna o vetor de posi��es vazias da matriz
}
//esssa funcao recebe como entrar o tamanho do tabuleiro e retorna um vetor de recordes
R * lerRecordes(int n){
	int i;
	FILE * fp;
	R *record=(R*)malloc(5*sizeof(R));//como foi especificado salvar no minimo 5 recordes, criamos um vetor de 5 posi��es
	//identificamos o tamanho do tabuleiro, seja 3x3/4x4/5x5

	if(n==3){
		fp=fopen("3recorde.txt","r+");
		for(i=0;i<5;i++){//pegamos os dados do arquivo, o valor do recorde e o nome dos 5  jogadores que o fizeram
			fscanf(fp,"%d %s\n", &record[i].valor,record[i].nome);
		}
		fclose(fp);
		return record;//retornamos o vetor de recoredes para que outras funcoes possam utilizalas
	}
	if(n==4){
		fp=fopen("4recorde.txt","r+");
		for(i=0;i<5;i++){//pegamos os dados do arquivo, o valor do recorde e o nome dos 5  jogadores que o fizeram
			fscanf(fp,"%d %s\n", &record[i].valor,record[i].nome);
		}
		fclose(fp);
		return record;//retornamos o vetor para que outras funcoes possam utilizalas
	}
	if(n==5){
		fp=fopen("5recorde.txt","r+");
		for(i=0;i<5;i++){//pegamos os dados do arquivo, o valor do recorde e o nome dos 5  jogadores que o fizeram
			fscanf(fp,"%d %s\n", &record[i].valor,record[i].nome);
		}
		fclose(fp);

		return record;//retornamos o vetor de recordes para que outras funcoes possam utilizalas
	}
	return NULL;
}
void Recordes(int recorde,R * record,int tabuleiro){//essa fun��o recebe como parametro o tamannho do tabuleiro, o valor de record, eo vetor de records salvos
	FILE * fp;//variavel para abrir o arquivo de recordes
	int i,indice,aux,menor=111111110;//variavel menor para encontrar o menor valor que ja temos em records para substituir
	char nome[10];



	for(i=0;i<5;i++){//aqui econtrarmos o menor valor salvo
	//	printf("\n%d %s\n",record[i].valor,record[i].nome);
		if(record[i].valor<menor){
			menor=record[i].valor;
			indice=i;

		}
	}

	if(recorde>menor){//aqui verificamos se o valor do jogo que acabou de se encerrar � menor que o menor record salvo
		record[indice].valor=recorde;//caso seja atualizamos o valor do menor record salvo
		printf("Informe o nome do jogador: \n");
		scanf("%s",record[indice].nome);//e atualizamos o nome do jogador tamb�m
	}

	fflush(stdout);
	//aqui reordenamos o valor dos recordes para que estejam sempre em ordem do maior para o menor
	for(i=0;i<4;i++){

			aux=record[i+1].valor;

			strcpy(nome,record[i+1].nome);
		if(record[i].valor<record[i+1].valor){//compara��o se o recorde da posicao atual do vetor � menor que o da posi��o da frente

			record[i+1].valor=record[i].valor;//caso seja aqui atulizamoos o valor passando o da posicao a frente para posicao anterior
			strcpy(record[i+1].nome,record[i].nome);
			record[i].valor=aux;
			strcpy(record[i].nome,nome);

		}
	}

	//agora identificamos se o recorde � do jogo de tabuleiro de tamanho 3,4 ou 5 para salvarmos os novos valores nos arquivos

	if(tabuleiro==3){
		fp=fopen("3recorde.txt","w+");//abrimos o arquivo para escrita
		for(i=0;i<5;i++){//salvmos os valores atualizados no arquivo
			printf("\naqui%d %s\n",record[i].valor,record[i].nome);
			fprintf(fp,"%d %s\n", record[i].valor,record[i].nome);

		}
		fclose(fp);
	}
	if(tabuleiro==4){//salvmos os valores atualizados no arquivo
		fp=fopen("4recorde.txt","w+");
		for(i=0;i<5;i++){
			printf("\n%d %s\n",record[i].valor,record[i].nome);
			fprintf(fp,"%d %s\n", record[i].valor,record[i].nome);

		}
		fclose(fp);
	}
	if(tabuleiro==5){//salvmos os valores atualizados no arquivo
		fp=fopen("5recorde.txt","w+");
		for(i=0;i<5;i++){
			printf("\n%d %s\n",record[i].valor,record[i].nome);
			fprintf(fp,"%d %s\n", record[i].valor,record[i].nome);

		}
		fclose(fp);
	}

}
void colisao_esquerda(int percurso,int * placar,int i,int matriz[0][tabuleiro]){//se dois numeros s�o iguais, um deles deve somar com o outro, essa fun��o trata esse caso para um movimento para a esquerda e para uma coluna inteira
  if(percurso >= tabuleiro-1)// se o percurso for maior igual a 3 a fun��o termina, percurso come�a com o valor 0
  	return;

  	if(matriz[i][percurso] == 0){//verifica se a posi�ao acessada no tabuleiro � igual a 0
  		percurso++;
	  }


   	if(matriz[i][percurso] != 0){// verifica se a posi��o acessada no tabuleiro � difente de 0
   			if(matriz[i][percurso] != matriz[i][percurso+1]){// verifica se a proxima posi�ao do tabuleiro � diferente da posi��o atual
   				percurso++;
   				return colisao_esquerda(percurso,placar,i,matriz); // retorna recursivamente a fun��o, agora com o valor de percurso incrementado;
			   }


   			if(matriz[i][percurso] == matriz[i][percurso+1]){ // verifica se a proxima posi��o do tabuleiro � igual a posi��o atual
   				matriz[i][percurso] += matriz[i][percurso+1]; // a posi��o atual � somada com o valor da proxima posi��o
   				*placar+=matriz[i][percurso]; // o placar � somado ao valor da posi��o atual(que ja cont�m o valor da soma com a sua proxima posi��o)
   				matriz[i][percurso+1] = 0; // a proxima posi��o recebe 0
   				percurso = percurso +1; // percurso � incrementado em 2, dessa forma n�o entra na proxima posi��o que possui o valor 0, e portanto nao ter� nenhuma colis�o
			 }
		}
	   return colisao_esquerda(percurso,placar,i,matriz); // retorna recursivamente a fun��o

}
void movimenta_esq(int mov,int percurso, int i,int matriz[0][tabuleiro]){ //fun��o responsavel pela movimenta��o de um linha toda para a esquerda
	  if(percurso == tabuleiro) // percurso inicia com valor = 0, se o valor for igual ao tabuleiro, fim da recurs�o
	  	return;

	  if(mov==0 && matriz[i][percurso] != 0){ // verifica se a mov = 0 e se a posi��o atual � diferente de 0
	  	percurso++; // incrementa percurso
	  	return movimenta_esq(mov,percurso,i,matriz);
	  }

	  if(matriz[i][percurso] == 0){ // verifica se a posic�o atual � igual a 0
	  	percurso++; // incrementa percurso
	  	mov++; // incrementa mov
	  	return movimenta_esq(mov,percurso,i,matriz);
	  }

	  if(matriz[i][percurso] != 0 && mov != 0){ // verifica se a posicao atual � diferente de 0 e se mov != 0
	  	matriz[i][percurso - mov] = matriz[i][percurso]; // a posicao que deve receber a movimentao (percurso - mov) a posicao atual
	  	matriz[i][percurso] = 0; // como a posicao atual ja foi deslocada para esquerda, a posicao atual = 0
	  	percurso++; // incrementa percurso
	  	return movimenta_esq(mov,percurso,i,matriz);
	  }

}


void movimenta_esquerda(int matriz[][tabuleiro], int * placar){	// fun��o que trata a movimenta��o do tabuleiro inteiro para o lado esquerdo
	int i;
	int percurso = 0;
	int mov = 0;
	for(i = 0; i<tabuleiro; i++){ //como os fun�oes que est�o dentro do for tratam os casos por coluna, nosso for deve ser executado com o mesmo numero de colunas do tabuleiro
		movimenta_esq(mov,percurso,i,matriz); // chama a movimenta��o para a esquerda
		colisao_esquerda(percurso,placar,i,matriz); //chama a fun��o que trata o somatorio de dois numeros iguais
		movimenta_esq(mov,percurso,i,matriz); // chama novamente a movimenta��o, consertando assim os numeros ap�s a colis�o
	}
}

void colisao_cima(int percurso,int* placar,int i,int matriz[0][tabuleiro]){//se dois numeros s�o iguais, um deles deve somar com o outro, essa fun��o trata esse caso para um movimento para cima e para uma linha inteira
	if(percurso >= tabuleiro-1) // se o percurso for maior igual a 3 a fun��o termina, percurso come�a com o valor 0
  		return;


  	if(matriz[percurso][i] == 0){ //verifica se a posi�ao acessada no tabuleiro for igual a 0
  		percurso++;
	  }


   	if(matriz[percurso][i] != 0){ // verifica se a posi��o acessada no tabuleiro for difente de 0
   			if(matriz[percurso][i] != matriz[percurso+1][i]){ // verifica se a proxima posi�ao do tabuleiro � diferente da posi��o atual
   				percurso++;
   				return colisao_cima(percurso,placar,i,matriz); // retorna recursivamente a fun��o, agora com o valor de percurso incrementado;
   			}

   			if(matriz[percurso][i] == matriz[percurso+1][i]){ // verifica se a proxima posi��o do tabuleiro � igual a posi��o atual
   				matriz[percurso][i] += matriz[percurso+1][i]; // a posi��o atual � somada com o valor da proxima posi��o
   				*placar+=matriz[percurso][i]; // o placar � somado ao valor da posi��o atual(que ja cont�m o valor da soma com a sua proxima posi��o)
   				matriz[percurso+1][i] = 0; // a proxima posi��o recebe 0
   				percurso = percurso +1; // percurso � incrementado em 2, dessa forma n�o entra na proxima posi��o que possui o valor 0, e portanto nao ter� nenhuma colis�o
			 }
		}
	   return colisao_cima(percurso,placar,i,matriz); // retorna recursivamente a fun��o
}


void movimenta_ci(int mov,int percurso, int i,int matriz[0][tabuleiro]){ //fun��o responsavel pela movimenta��o de uma coluna inteira para cima
	if(percurso == tabuleiro) // percurso inicia com valor = 0, se o valor for igual ao tabuleiro, fim da recurs�o
	  	return;

	  if(mov==0 && matriz[percurso][i] != 0){ // verifica se a mov = 0 e se a posi��o atual � diferente de 0
	  	percurso++; // incrementa percurso
	  	return movimenta_ci(mov,percurso,i,matriz);
	  }

	  if(matriz[percurso][i] == 0){ // verifica se a posic�o atual � igual a 0
	  	percurso++; // incrementa percurso
	  	mov++; // incrementa mov
	  	return movimenta_ci(mov,percurso,i,matriz);
	  }

	  if(matriz[percurso][i] != 0 && mov != 0){ // verifica se a posicao atual � diferente de 0 e se mov != 0
	  	matriz[percurso - mov][i] = matriz[percurso][i]; // a posicao que deve receber a movimentao (percurso - mov) a posicao atual
	  	matriz[percurso][i] = 0; // como a posicao atual ja foi deslocada para esquerda, a posicao atual = 0
	  	percurso++; // percurso++
	  	return movimenta_ci(mov,percurso,i,matriz);
	  }

}


void movimenta_cima(int matriz[][tabuleiro],int *placar){// fun��o que trata a movimenta��o do tabuleiro inteiro para cima
	int i;
	int percurso = 0;
	int mov= 0;

	for(i = 0; i<tabuleiro; i++){//como os fun�oes que est�o dentro do for tratam os casos por linha, nosso for deve ser executado com o mesmo numero de linhas do tabuleiro
		movimenta_ci(mov,percurso,i,matriz); // chama a movimenta��o para cima
		colisao_cima(percurso,placar,i,matriz); // trata o somatorio de dois numeros iguais
		movimenta_ci(mov,percurso,i,matriz); // chama novamente a movimenta��o, consertando assim os numeros ap�s a colis�o
	}
}

void colisao_direita(int percurso, int * placar,int i,int matriz[0][tabuleiro]){  //se dois numeros s�o iguais, um deles deve somar com o outro, essa fun��o trata esse caso para um movimento para a direita e para uma coluna inteira
  if(percurso <= 0) // se o percurso for memor igual a 0 a fun��o termina, percurso come�a com o valor 3
  	return;

  	if(matriz[i][percurso] == 0) //verifica se a posi�ao acessada no tabuleiro � igual a 0
   		percurso--;


   	if(matriz[i][percurso] != 0){ // verifica se a posi��o acessada no tabuleiro � difente de 0

   			if(matriz[i][percurso] != matriz[i][percurso-1]){ // verifica se a posi�ao anterior do tabuleiro � diferente da posi��o atual
   				percurso--;
   				return colisao_direita(percurso,placar,i,matriz); //  chama recursivamente a fun��o, agora com o valor de percurso decrementado;
			   }

   			if(matriz[i][percurso] == matriz[i][percurso-1]){ // verifica se a posi��o anterior do tabuleiro � igual a posi��o atual
   				matriz[i][percurso] += matriz[i][percurso-1]; // a posi��o atual � somada com o valor da posi��o anterior
   				*placar+=matriz[i][percurso]; // o placar � somado ao valor da posi��o atual(que ja cont�m o valor da soma com a sua proxima posi��o)
   				matriz[i][percurso-1] = 0; // a posi��o anterior recebe 0
   				percurso = percurso -1; // percurso � decrementado em 2, dessa forma n�o entra na posi��o anterior que possui o valor 0, e portanto nao ter� nenhuma colis�o
			   }
	}

	   return colisao_direita(percurso,placar,i,matriz); // retorna recursivamente a fun��o
}

void movimenta_dir(int mov, int percurso, int i,int matriz[0][tabuleiro]){ //fun��o responsavel pela movimenta��o de um linha toda para a direita
		if(percurso < 0) // percurso inicia com = tabuleiro -1, se percurso < 0 a fun��o termina
	  	return;

	  if(mov==0 && matriz[i][percurso] != 0){ // verifica se a mov = 0 e se a posi��o atual � diferente de 0
	  	percurso--; // decrementa percurso
	  	return movimenta_dir(mov,percurso,i,matriz);
	  }

	  if(matriz[i][percurso] == 0){ // verifica se a posic�o atual � igual a 0
	  	percurso--; // decrementa percurso
	  	mov++; // decrementa mov
	  	return movimenta_dir(mov,percurso,i,matriz);
	  }

	  if(matriz[i][percurso] != 0 && mov != 0){ // verifica se a posicao atual � diferente de 0 e se mov != 0
	  	matriz[i][percurso + mov] = matriz[i][percurso]; // a posicao que deve receber a movimentao (percurso + mov) a posicao atual
	  	matriz[i][percurso] = 0; // como a posicao atual ja foi deslocada para a direita, a posicao atual = 0
	  	percurso--; //decrementa percurso
	  	return movimenta_dir(mov,percurso,i,matriz);
	  }
}



void movimenta_direita(int matriz[][tabuleiro],int *placar){ // fun��o que trata a movimenta��o do tabuleiro inteiro para o lado direito
	int i;
	int percurso = tabuleiro -1;
	int mov=0;
	for(i=0; i<tabuleiro; i++){ //como os fun�oes que est�o dentro do for tratam os casos por coluna, nosso for deve ser executado com o mesmo numero de colunas do tabuleiro
		movimenta_dir(mov,percurso,i,matriz); // chama a movimenta��o para a direita
		colisao_direita(percurso,placar,i,matriz); // trata o somatorio de dois numeros iguais
		movimenta_dir(mov,percurso,i,matriz); // chama novamente a movimenta��o, consertando assim os numeros ap�s a colis�o
	}
}

void colisao_baixo(int percurso,int *placar,int i,int matriz[0][tabuleiro]){ //se dois numeros s�o iguais, um deles deve somar com o outro, essa fun��o trata esse caso para um movimento para baixo e para uma linha inteira
    if(percurso <= 0) // se o percurso for menor igual a 0 a fun��o termina, percurso come�a com o valor 3
  	return;

  	if(matriz[percurso][i] == 0) //verifica se a posi�ao acessada no tabuleiro � igual a 0
   		percurso--;


   	if(matriz[percurso][i] != 0){ // verifica se a posi��o acessada no tabuleiro � difente de 0
   			if(matriz[percurso][i] != matriz[percurso-1][i]){ // verifica se a posi�ao anterior do tabuleiro � diferente da posi��o atual
   				percurso--;
   				return colisao_baixo(percurso,placar,i,matriz); // chama recursivamente a fun��o, agora com o valor de percurso decrementado;
			   }



   			if(matriz[percurso][i] == matriz[percurso-1][i]){ // verifica se a posi��o anterior do tabuleiro � igual a posi��o atual
   				matriz[percurso][i] += matriz[percurso-1][i]; // a posi��o atual � somada com o valor da posi��o anterior
   				*placar+=matriz[percurso][i]; // o placar � somado ao valor da posi��o atual(que ja cont�m o valor da soma com a sua posi��o anterior)
   				matriz[percurso-1][i] = 0; // a posi��o anterior recebe 0
   				percurso = percurso -1; // percurso � decrementado em 2, dessa forma n�o entra na posi��o anterior que possui o valor 0, e portanto nao ter� nenhuma colis�o
			   }
	}
	   return colisao_baixo(percurso,placar,i,matriz); // retorna recursivamente a fun��o
}



void movimenta_bai(int mov,int percurso, int i,int matriz[0][tabuleiro]){ //fun��o responsavel pela movimenta��o de um linha toda para baixo
		if(percurso < 0) // percurso inicia com = tabuleiro -1, se percurso < 0 a fun��o termina
	  	return;

	  if(mov==0 && matriz[percurso][i] != 0){ // verifica se a mov = 0 e se a posi��o atual � diferente de 0
	  	percurso--; // decrementa percurso
	  	return movimenta_bai(mov,percurso,i,matriz);
	  }

	  if(matriz[percurso][i] == 0){ // verifica se a posic�o atual � igual a 0
	  	percurso--; // decrementa percurso
	  	mov++; // decrementa mov
	  	return movimenta_bai(mov,percurso,i,matriz);
	  }

	  if(matriz[percurso][i] != 0 && mov != 0){ // verifica se a posicao atual � diferente de 0 e se mov != 0
	  	matriz[percurso + mov][i] = matriz[percurso][i]; // a posicao que deve receber a movimentao (percurso + mov) a posicao atual
	  	matriz[percurso][i] = 0; // como a posicao atual ja foi deslocada para a direita, a posicao atual = 0
	  	percurso--; //decrementa percurso
	  	return movimenta_bai(mov,percurso,i,matriz);
	  }
}


void movimenta_baixo(int matriz[][tabuleiro],int * placar){ // fun��o que trata a movimenta��o do tabuleiro inteiro para baixo
	int i;
	int percurso = tabuleiro -1;
	int mov=0;
	for(i=0; i<tabuleiro; i++){//como os fun�oes que est�o dentro do for tratam os casos por linha, nosso for deve ser executado com o mesmo numero de linhas do tabuleiro
		movimenta_bai(mov,percurso,i,matriz);// chama a movimenta��o para a baixo
		colisao_baixo(percurso,placar,i,matriz);// trata o somatorio de dois numeros iguais
		movimenta_bai(mov,percurso,i,matriz); // chama novamente a movimenta��o, consertando assim os numeros ap�s a colis�o
	}
}// est�vel at� aqui




void copiaMatriz(int matriz[][tabuleiro],int aux[][tabuleiro]){ // fun��o que copia o tabuleiro para um tabuleiro auxiliar
	int i,j;
	for(i=0;i<tabuleiro;i++){
		for(j=0;j<tabuleiro;j++){
			aux[i][j]=matriz[i][j]; // cada posicao da matriz auxiliar recebe as posicoes da matriz principal
		}
	}

}
int  comparaMatriz(int matriz[][tabuleiro],int aux[][tabuleiro]){ // fun��o que compara o tabuleiro com outro tabuleiro auxiliar
	int i,j;
	for(i=0;i<tabuleiro;i++){
		for(j=0;j<tabuleiro;j++){
			if(aux[i][j]!=matriz[i][j]) // verifica se a posi��o de aux � diferente que a mesma posi��o do tabuleiro
				return 0; // tabuleiros diferentes
		}
	}
	return 1; // tabuleiros sao iguais
}

int gerarNum(){ // fun��o respons�vel por gerar os numeros 2 ou 4
	int valor;
	valor=rand() % 10;

	if(valor<8){ // 70 porcento de chance de gerar 2
		return 2;
	}
	return 4; // 30 porcento de chance de gerar 4
}

void  sorteiaposicao(P * vetor, int matriz[][tabuleiro],int *placar){  // sortei em qual posi��o vazia do tabuleiro o numero 2 ou 4 ser� inserido
	int tamanhovetor=(vetor)[0].tamanho; // tamanho vetor recebe o tamanho do vetor de posi�oes sem nenhum valor
	int aux[tabuleiro][tabuleiro]; // cria tabuleiro auxiliar
	copiaMatriz(matriz
	,aux); // copia o tabuleiro para o tabuleiro auxiliar
	int posicao,x,y, valoraleatorio;

	posicao = rand() % tamanhovetor; // posi�ao recebe uma posi��o aleat�ria do vetor de posi��es vazias
	x=(vetor)[posicao].linha; //x recebe a linha da posi��o vazia sorteada
	y=(vetor)[posicao].coluna; //y recebe a linha da posi��o vazia sorteada
	valoraleatorio=gerarNum(); // valor aleatorio recebe 2 ou 4
	matriz[x][y]= valoraleatorio; // a posi��o vazia do tabuleiro recebe 2 ou 4

}


void iniciarGame(int matriz[][tabuleiro]){ // fun��o que inicia o tabuleiro
	int i,j;
	for(i=0;i<tabuleiro;i++){
		for(j=0;j<tabuleiro;j++){
			matriz[i][j]=0; // completa o tabuleiro com 0
		}
	}
}


void Displayjogo(int matriz [][tabuleiro]){ // fun��o que mostra o tabuleiro na tela

		int i,j;
	if(tabuleiro==3){
		for(i=0;i<tabuleiro;i++){
			printf("\n");
			for(j=0;j<tabuleiro;j++){
				if(i==0 && j==0){
					//printf("\t|");
					printf("|-----------------------|-----------------------|-----------------------|");
					printf("\n");
				}
				if(matriz[i][j]==0)
					printf("|\t\t\t");

				if(matriz[i][j]!=0)
					printf("|        %5d\t\t", matriz[i][j]);

				if(j==2){
					printf("|");
					printf("\n|-----------------------|-----------------------|-----------------------|");
				}
			}
		}
	}
	if(tabuleiro==4){
		for(i=0;i<tabuleiro;i++){
			printf("\n");
			for(j=0;j<tabuleiro;j++){
				if(i==0 && j==0){
					//printf("\t|");
					printf("|-----------------------|-----------------------|-----------------------|-----------------------|");
					printf("\n");
				}
				if(matriz[i][j]==0)
					printf("|\t\t\t");

				if(matriz[i][j]!=0)
					printf("|        %5d\t\t", matriz[i][j]);

				if(j==3){
					printf("|");
					printf("\n|-----------------------|-----------------------|-----------------------|-----------------------|");
				}
			}
		}
	}
	if(tabuleiro==5){
		for(i=0;i<tabuleiro;i++){
		printf("\n");
		for(j=0;j<tabuleiro;j++){
			if(i==0 && j==0){
				//printf("\t|");
				printf("|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|");
				printf("\n");
			}
			if(matriz[i][j]==0)
				printf("|\t\t\t");

			if(matriz[i][j]!=0)
				printf("|        %5d\t\t", matriz[i][j]);

			if(j==4){
				printf("|");
				printf("\n|-----------------------|-----------------------|-----------------------|-----------------------|-----------------------|");
			}
		}
	}

	}

}
int fimjogo(int matriz[][tabuleiro],int *placar,P*vetor){ // verifica se o jogo acabou
	    int aux[tabuleiro][tabuleiro], valor,placarposteste;
	    int tamanho;
	    int *placaraux; // cria um placar auxiliar
	    placaraux=(int*)malloc(sizeof(int)); // aloca o placar
	    copiaMatriz(matriz,aux); // tabuleiro � copiado para um tabuleiro auxiliar
		valor=*placar; // valor recebe o placar atual
		*placaraux=valor; //o placar auxiliar recebe valor
		tamanho = vetor[0].tamanho; // tamanho recebe o tamanho do tabuleiro


		if(comparaMatriz(matriz,aux) == 1){ // se o tabuleiro estiver cheio
		movimenta_baixo(aux,placaraux);// chama os 4 movimentos possiveis
		movimenta_cima(aux,placaraux);
		movimenta_direita(aux,placaraux);
		movimenta_esquerda(aux,placaraux);
		placarposteste=*placaraux; // o placar teste recebe o valor do placar ap�s as 4 movimenta��es
		if(tamanho == 1 && (placarposteste==valor)){// se o tabuleiro estiver cheio e o placar ap�s as 4 movimenta��es se manteve igual
			printf("\n FIM DE JOGO!!"); // o usuario n�o tem mais movimenta��es, fim de jogo;
			return 1;	// fim de jogo
			}
		}
		return 0; // o jogo n�o terminou
}


void jogar(int matriz[][tabuleiro], int  * placar, int  * njogadas){ // dinamismo do jogo
		int historicoplacar,vitoria,placaratual;
		int aux[tabuleiro][tabuleiro]; // cria um tabuleiro auxiliar do tamanho do tabuleiro do jogo
		char tecla;
		R* vetorrecord;
		P* vetor;


//

		do{ //la�o para as movimenta��es

			//

			printf("\n Numero de jogadas : %d ",(*njogadas));printf("\t\t\t\t\t\t\tPlacar: %d ",(*placar));

			Displayjogo(matriz);
			printf("\nW- PARA ACIMA ");
			printf("\nS- PARA ABAIXO ");
			printf("\nA- PARA ESQUERDA");
			printf("\nD- PARA DIREITA");
			printf("\nT- NUMERO DE JOGADAS");
			printf("\nQ- PLACAR");
			printf("\nP- salvar");
			printf("\nR- SAIR\n");
			fflush(stdin);
			scanf("%c",&tecla);
			historicoplacar=*placar;



			switch(tecla){
				case 'w': // movimenta��o para cima
					copiaMatriz(matriz,aux);
					movimenta_cima(matriz,placar);
					if(comparaMatriz(matriz,aux)==0){ // verifica se ap�s a movimenta��o o tabuleiro � diferente do tabuleiro auxiliar
						vetor=espacaovazio(matriz); // vetor recebe os espa�os vazios do tabuleiro
						sorteiaposicao(vetor,matriz,placar); // um valor � colado em alguma posi��o vazia do tabuleiro
						*njogadas+=1; // numero de jogadas � incrementado
						break;
					}else{
						if(fimjogo(matriz,placar,vetor)==1){ // verifica se o jogo acabou
							vetorrecord=lerRecordes(tabuleiro);
							Recordes(*placar,vetorrecord,tabuleiro);
							return;
						}
						*njogadas+=1; // numero de jogadas � incrementado
						break;
					}
				case 's': // movimenta��o para baixo
					copiaMatriz(matriz,aux);
					movimenta_baixo(matriz,placar);
					if(comparaMatriz(matriz,aux)==0){// verifica se ap�s a movimenta��o o tabuleiro � diferente do tabuleiro auxiliar
						vetor=espacaovazio(matriz); // vetor recebe os espa�os vazios do tabuleiro
						sorteiaposicao(vetor,matriz,placar); // um valor � colado em alguma posi��o vazia do tabuleiro
						*njogadas+=1; // numero de jogadas � incrementado
						break;
					}else{
						if(fimjogo(matriz,placar,vetor)==1){ // verifica se o jogo acabou
							vetorrecord=lerRecordes(tabuleiro);
							Recordes(*placar,vetorrecord,tabuleiro);
							return;
						}
						*njogadas+=1; // numero de jogadas � incrementado
						break;
					}

				case 'a': // movimenta��o para esquerda
					copiaMatriz(matriz,aux);
					movimenta_esquerda(matriz,placar);
					if(comparaMatriz(matriz,aux)==0){// verifica se ap�s a movimenta��o o tabuleiro � diferente do tabuleiro auxiliar
						vetor=espacaovazio(matriz); // vetor recebe os espa�os vazios do tabuleiro
						sorteiaposicao(vetor,matriz,placar); // um valor � colado em alguma posi��o vazia do tabuleiro
						*njogadas+=1; // numero de jogadas � incrementado
						break;
					}else{
						if(fimjogo(matriz,placar,vetor)==1){ // verifica se o jogo acabou
							vetorrecord=lerRecordes(tabuleiro);
							Recordes(*placar,vetorrecord,tabuleiro);
							return ;
						}
						*njogadas+=1; // numero de jogadas � incrementado
						break;
					}
				case 'd': // movimenta��o para a direita
					copiaMatriz(matriz,aux);
					movimenta_direita(matriz,placar);
					if(comparaMatriz(matriz,aux)==0){ // verifica se ap�s a movimenta��o o tabuleiro � diferente do tabuleiro auxiliar
						vetor=espacaovazio(matriz); // vetor recebe os espa�os vazios do tabuleiro
						sorteiaposicao(vetor,matriz,placar); // um valor � colado em alguma posi��o vazia do tabuleiro
							*njogadas+=1; // numero de jogadas � incrementado
						break;
					}else{
						if(fimjogo(matriz,placar,vetor)==1){// verifica se o jogo acabou
							vetorrecord=lerRecordes(tabuleiro);
							Recordes(*placar,vetorrecord,tabuleiro);
							return ;
						}
						*njogadas+=1; // numero de jogadas � incrementado
						break;
					}
				case 'r':
					return menuInicial(matriz,placar,njogadas);
					break;
				case 't': // mostra o numero de jogadas
					printf("\n Numero de jogadas: %d ",*njogadas);
					break;
				case 'q': // mostra o placar
					printf("\n Placar : %d",*placar);
					break;
				case 'p':
					printf("\n Jogo salvo");
					salvargame(tabuleiro,matriz,placar,njogadas);
					break;
				default:
					printf("opcao invalida");
					break;
			}

					system("cls");
					placaratual=*placar; // placar atual recebe o valor de placar
					if(placaratual-historicoplacar >=2048 && vitoria!=1){ // verifica se a diferen�a entre o placar e historico placar � 2048, e se a pessoa ja conseguiu gerar um bloco de 2048
							printf("\n\t\t\t\t\tPARABENS VOCE GANHOU!");
							vitoria=1; // o usuario ja ganhou o jogo
						}

		}while(tecla!='r'); // o la�o termina quando o usuario aperta 0

}
void menuInicial(int matriz[][tabuleiro], int *placar, int * numerojogadas){ // primeiro menu
	int op,tamanho;
	R *vetorrecord=(R*)malloc(5*sizeof(R));

	do{

	 	fflush(stdin);
		printf("\n2048 --------------------------- GAME ");
		printf("\nMenu inical");
		printf("\n1 - Inicar Jogo");
		printf("\n2 - Ver Recordes");
		printf("\n3 - Definir Dificuldade");
		printf("\n4 - Carregar jogo");
		printf("\n0 - Sair\n");

		scanf("%d",&op);

		if(op==1){ // inicia o jogo
			iniciarGame(matriz); // inicia o jogo
			*placar=0;
			*numerojogadas=0;
			P *vetor=espacaovazio(matriz); // vetor de espa�os vazios receve os espa�os vazios do tabuleiro
			sorteiaposicao(vetor,matriz,placar); // um valor � sorteado para uma posi��o vazia do tabuleiro
			jogar(matriz,placar,numerojogadas);
			break;

		}
		if(op==2){// mostra os recordes

			vetorrecord=lerRecordes(tabuleiro);
			Recordes(*placar,vetorrecord,tabuleiro);
			return menuInicial(matriz,placar,numerojogadas);

		}
		if(op==3){ // define o tamanho do tabuleiro
			printf("Escolha a Dificuldade\n1-facil-5x5\n2-Medio-4x4\n3-dificil-3x3\n");
			scanf("%d",&tamanho);
			if(tamanho==1){
				tabuleiro=5;
				return menuInicial(matriz,placar,numerojogadas);
			}
			if(tamanho==2){
				tabuleiro=4;
				return menuInicial(matriz,placar,numerojogadas);
			}
			if(tamanho==3){
				tabuleiro=3;
				return menuInicial(matriz,placar,numerojogadas);
			}
			break;
		}
		if(op==4){
			carregargame(tabuleiro,matriz,placar,numerojogadas);
			jogar(matriz,placar,numerojogadas);
		}

	}while(op!=0); // la�o termina se o us�ario aperta 0

}


int main(){
	int 	*placar=(int*)malloc(sizeof(int)); // aloca dinamicamente a  placar do jogo
	int  *numerodejogadas=(int*)malloc(sizeof(int)); // aloca dinamicamente o numero de jogadas do jogo
	int   matriz[tabuleiro][tabuleiro]; // cria o tabuleiro do jogo
	*placar=0;
	*numerodejogadas=0;

	menuInicial(matriz,placar,numerodejogadas); // chama o menu

	free(numerodejogadas); // libera a vari�vel numerodejogadas
	free(placar); // libera a vari�vel placar

	return 0;
}
