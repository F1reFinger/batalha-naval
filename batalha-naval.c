#include <stdio.h>
//vai validar a entrada e retornar se a entrada é valida;
int validaEntradaLinhaColuna(int linha, char coluna){
  //Entrada de letras;
	if(coluna<'A'||coluna>'J'){
    return 0;
  }
	//Entada de numeros;
  if(linha<0||linha>10){
    return 0;
  }
	//qualquer coisa retorna valida;
  return 1;
}
//valida a posição para colocar o barco;
int validaPosicao(int mat[10][10],int barco,int linha,int coluna,char orientacao){


	//auxiliares para ajudar como se fossem flags;
	int aux=0, litrao=1;
	//se as entradas forem invalidas quebram aqui tbm
  if(linha<0 || linha >9){
		return 0;
	}
  if(coluna<0 || coluna>9){
		return 0;
	}
	if(barco<1||barco>3){
		return 0;
	}
	if(orientacao!='H' && orientacao!='V'){
		return 0;
	}
	////////////////////////////////////////////////////
	//se o barco for igual a um tem uma condição diferente
	if(barco==1){
		if(mat[linha][coluna]!=0){
			return 0;
		}
		else if(mat[linha][coluna]==0){
			return 1;
		}
	}
	/////////////////////////////////////////////////////
	//se não for é a condição padrão para 2 ou 3
	else if(barco>1){
		if(orientacao=='V'){
			for(int i=linha;litrao<=barco;i++,litrao++){
				if(mat[i][coluna]==0 && (coluna<10 && coluna>=0) && (i<10 && i>=0)){
					aux++;
				}
			}
		}
		else if(orientacao=='H'){
			for(int i=coluna;litrao<=barco;i++,litrao++){
				if(mat[linha][i]==0 && (linha<10 && linha>=0) && (i<10 && i>=0)){
					aux++;
				}
			}
		}
	}
	////////////////////////////////////////////////////////
	//verifica se o barco ta valido
	if(aux==barco){
		return 1;
	 }
	else{
	return 0;
  }
  return 0;
}
//função pode atirar
int podeAtirar(int mat[10][10],int linha,int coluna){
	//se for diferente de qualquer um desses valores então o tiro é valido
	if(mat[linha][coluna]!=-2&&mat[linha][coluna]!=10&&mat[linha][coluna]!=20&&mat[linha][coluna]!=30&&mat[linha][coluna]!=50){
		//se entrou aqui pode atirar
		return 1;
	}
	//se ta aqui quebrou
	else{
	return 0;
	}
}
void imprimeMensagem(char msg[1000]){
	 printf("************************\n");
	 printf("*\n");
	 printf("* %s\n",msg);
	 printf("*\n");
	 printf("************************\n");
}
char imprimeCelula(int celula,int etapa){
		if(etapa==0){
			if(celula==0){
				return '.';
			}
			if(celula==-1){
				return '*';
			}
			if(celula==1){
				return '1';
			}
			if(celula==2){
				return '2';
			}
			if(celula==3){
				return '3';
			}
		}
		if(etapa==1){
			if(celula==0||celula==1||celula==-1||celula==2||celula==3){
				return '.';
			}
			if(celula==-2){
				return 'x';
			}
			if(celula==10||celula==20||celula==30){
				return 'N';
			}
			if(celula==50){
				return 'A';
			}
		}
}
void imprimeTabuleiro(int mat[10][10], int etapa){
  int i,j;
	char pinto;
		printf("     ");
    printf("A B C D E F G H I J");
    printf("\n");
    printf("   ");
  	printf("# # # # # # # # # # # #\n");
		for(i=0;i<10;i++){
      printf("%02d ",i+1);
			printf("# ");
        for(j=0;j<10;j++){
          pinto=imprimeCelula(mat[i][j],etapa);
						printf("%c ", pinto);
        }
				printf("#");
        printf("\n");
    }
  printf("   ");
	printf("# # # # # # # # # # # #\n");
}
void posicionaBarco(int mat[10][10],int barco){
	int linha,aux,h,b=1;
	char orientacao,coluna;
  int coluna1, linha1;
  //VALIDAÇÃO;
	if(barco==1){
     scanf("%d %c",&linha,&coluna);
     coluna1=coluna-65;
      linha1=linha-1;
      while(validaPosicao(mat,barco,linha1, coluna1, 'V')==0 || validaEntradaLinhaColuna(linha, coluna) == 0){
       printf("Posicao indisponivel!\n");
       scanf("%d %c",&linha,&coluna);
       coluna1=coluna-65;
       linha1=linha-1;
      }
  }
  if(barco>1){
    scanf("%d %c",&linha,&coluna);
    scanf(" %c", &orientacao);
    coluna1=coluna-65;
     linha1=linha-1;
      while(validaPosicao(mat,barco,linha1, coluna1, orientacao) == 0 || validaEntradaLinhaColuna(linha, coluna) == 0){
       printf("Posicao indisponivel!\n");
       scanf("%d %c",&linha,&coluna);
       scanf(" %c", &orientacao);
       coluna1=coluna-65;
       linha1=linha-1;
      }
  }
	//POSICIONAMENTO;
  if(barco==1){
			for(int i=linha1-1;i<=linha1+1;i++){
				for(int j=coluna1-1;j<coluna1+2;j++){
         if(i>=0 && i<=9 &&j>=0 && j<=9)mat[i][j]=-1;
				}
			}
			mat[linha1][coluna1]=1;
  }
	else if(barco==2){
   if(orientacao=='H'){
     mat[linha1][coluna1]=2;
     mat[linha1][coluna1+1]=2;
    for(int i=linha1-1;i<linha1+2;i++){
				for(int j=coluna1-1;j<coluna1+3;j++){
         if(i>=0 && i<=9 &&j>=0 && j<=9 && mat[i][j]!=2)mat[i][j]=-1;
		 }
		}
   }
    if(orientacao=='V'){
     mat[linha1][coluna1]=2;
     mat[linha1+1][coluna1]=2;
    for(int i=linha1-1;i<linha1+3;i++){
				for(int j=coluna1-1;j<coluna1+2;j++){
         if(i>=0 && i<=9 &&j>=0 && j<=9 && mat[i][j]!=2)mat[i][j]=-1;
		 }
		}
   }
  }
  else if(barco==3){
   if(orientacao=='H'){
     mat[linha1][coluna1]=3;
     mat[linha1][coluna1+1]=3;
     mat[linha1][coluna1+2]=3;
    for(int i=linha1-1;i<linha1+2;i++){
				for(int j=coluna1-1;j<coluna1+4;j++){
         if(i>=0 && i<=9 &&j>=0 && j<=9 && mat[i][j]!=3)mat[i][j]=-1;
		 }
		}
   }
    if(orientacao=='V'){
     mat[linha1][coluna1]=3;
     mat[linha1+1][coluna1]=3;
     mat[linha1+2][coluna1]=3;
    for(int i=linha1-1;i<linha1+4;i++){
				for(int j=coluna1-1;j<coluna1+2;j++){
         if(i>=0 && i<=9 &&j>=0 && j<=9 && mat[i][j]!=3)mat[i][j]=-1;
		 }
		}
   }
  }
}
//função atirar
void atirar(int mat[10][10],int linha,int coluna){
	if(mat[linha][coluna]==0||mat[linha][coluna]==-1){
		mat[linha][coluna]=-2;
	}
	if(mat[linha][coluna]==1){
		mat[linha][coluna]=10;
	}
	if(mat[linha][coluna]==2){
		mat[linha][coluna]=20;
	}
	if(mat[linha][coluna]==3){
		mat[linha][coluna]=30;
	}
}
//função calcular posição;
int calculaPontuacao(int mat[10][10],int linha,int coluna){
	//barco 1;
	if(mat[linha][coluna]==10){
    mat[linha][coluna]=50;
		return 2;
	}
	//barco 2;
	else if(mat[linha][coluna]==20 && mat[linha][coluna+1]==20){
		mat[linha][coluna]=50;
		mat[linha][coluna+1]=50;
		return 4;
	}
	else if(mat[linha][coluna]==20 && mat[linha][coluna-1]==20){
		mat[linha][coluna]=50;
		mat[linha][coluna-1]=50;
		return 4;
	}
	else if(mat[linha][coluna]==20 && mat[linha+1][coluna]==20){
		mat[linha][coluna]=50;
		mat[linha+1][coluna]=50;
		return 4;
	}
	else if(mat[linha][coluna]==20 && mat[linha-1][coluna]==20){
		mat[linha][coluna]=50;
		mat[linha-1][coluna]=50;
		return 4;
	}
	//barco 3
	//se for a parte do meio do barco na Vertical;
	else if(mat[linha][coluna]==30 && mat[linha+1][coluna]==30 &&  mat[linha-1][coluna]==30){
		mat[linha][coluna]=50;
		mat[linha+1][coluna]=50;
		mat[linha-1][coluna]=50;
		return 7;
	}
	//se for a parte do meio do barco na horizontal
	else if(mat[linha][coluna]==30 && mat[linha][coluna+1]==30 && mat[linha][coluna-1]==30){
		mat[linha][coluna]=50;
		mat[linha][coluna+1]=50;
		mat[linha][coluna-1]=50;
		return 7;
	}
	//se o barco for horizontal crescente;
	else if(mat[linha][coluna]==30 && mat[linha][coluna+1]==30 && mat[linha][coluna+2]==30){
     mat[linha][coluna]=50;
     mat[linha][coluna+1]=50;
     mat[linha][coluna+2]=50;
   return 7;
  }
  else if(mat[linha][coluna]==30 && mat[linha][coluna-1]==30 && mat[linha][coluna-2]==30){
     mat[linha][coluna]=50;
     mat[linha][coluna-1]=50;
     mat[linha][coluna-2]=50;
   return 7;
  }
  else if(mat[linha][coluna]==30 && mat[linha+1][coluna]==30 && mat[linha+2][coluna]==30){
     mat[linha][coluna]=50;
     mat[linha+1][coluna]=50;
     mat[linha+2][coluna]=50;
    return 7;
  }
  else if(mat[linha][coluna]==30 && mat[linha-1][coluna]==30 && mat[linha-2][coluna]==30){
     mat[linha][coluna]=50;
     mat[linha-1][coluna]=50;
     mat[linha-2][coluna]=50;
    return 7;
  }
 return 0;
}
void funcMSN(int tamBarco,int i,int jogador){
	if(tamBarco==1){
	 printf("************************\n");
	 printf("*\n");
	 printf("* Jogador %d - Posicione o barco de tamanho 1 (%d/6)\n",jogador,i+1);
	 printf("*\n");
	 printf("************************\n");
	}
	if(tamBarco==2){
		printf("************************\n");
	 	printf("*\n");
	 	printf("* Jogador %d - Posicione o barco de tamanho 2 (%d/4)\n",jogador,i+1);
	 	printf("*\n");
		printf("************************\n");
	}
	if(tamBarco==3){
		printf("************************\n");
	 	printf("*\n");
	 	printf("* Jogador %d - Posicione o barco de tamanho 3 (%d/2)\n",jogador,i+1);
	 	printf("*\n");
		printf("************************\n");
	}
 }
int main(){
	int player1[10][10]={0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0};
	int player2[10][10]={0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0,
											0,0,0,0,0,0,0,0,0,0};
    //posicionamento de barcos PLAYER 1
    for(int i=0;i<6;i++){
        funcMSN(1,i,1);
        imprimeTabuleiro(player1,0);
        posicionaBarco(player1,1);
    }
    for(int i=0;i<4;i++){
        funcMSN(2,i,1);
        imprimeTabuleiro(player1,0);
        posicionaBarco(player1,2);
    }
    for(int i=0;i<2;i++){
        funcMSN(3,i,1);
        imprimeTabuleiro(player1,0);
        posicionaBarco(player1,3);
    }
    //posicionamento de barcos PLAYER 2
    for(int i=0;i<6;i++){
        funcMSN(1,i,2);
        imprimeTabuleiro(player2,0);
        posicionaBarco(player2,1);
    }
    for(int i=0;i<4;i++){
        funcMSN(2,i,2);
        imprimeTabuleiro(player2,0);
        posicionaBarco(player2,2);
    }
    for(int i=0;i<2;i++){
        funcMSN(3,i,2);
        imprimeTabuleiro(player2,0);
        posicionaBarco(player2,3);
    }
    //agora a etapa de atirar;
		//Etapa 1;
		int jogadas=0,pontant=0,pontant1=0,glauber=0,pos=0,kleber=0,pts1=0,pts2=0;
		char L;
		while(jogadas!=41){


                if(pts1==42){
                    break;
                }
                if(pts2==42){
                    break;
                }
                if(jogadas==40){
                    break;
                }

			printf("************************\n");
	 		printf("*\n");
	 		printf("* PONTUACAO DO JOGADOR 1: %d\n",pts1);
			printf("* PONTUACAO DO JOGADOR 2: %d\n",pts2);
	 		printf("*\n");
	 		printf("************************\n");
		//player1 atira na player 2;
		if(jogadas%2==0){
			printf("************************\n");
	 		printf("*\n");
	 		printf("* VEZ DO JOGADOR 1\n");
	 		printf("*\n");
	 		printf("************************\n");
			imprimeTabuleiro(player2,1);
			scanf("%d %c",&pos,&L);
			kleber=L-65;
			pos=pos-1;
			while(validaEntradaLinhaColuna(pos,L)==0||podeAtirar(player2,pos,kleber)==0){
				printf("Posicao indisponivel!\n");
				scanf("%d %c",&pos,&L);
				kleber=L-65;
				pos=pos-1;
			}
			atirar(player2,pos,kleber);
			pts1+=calculaPontuacao(player2,pos,kleber);
			if(pontant<pts1){
				printf("************************\n");
	 			printf("*\n");
	 			printf("* JOGADOR 1 DERRUBOU UM NAVIO!\n");
	 			printf("*\n");
	 			printf("************************\n");
				printf("\n");
				pontant=pts1;
			}
		}
		//player2 atira na player 1;
		else{
			printf("************************\n");
	 		printf("*\n");
	 		printf("* VEZ DO JOGADOR 2\n");
	 		printf("*\n");
	 		printf("************************\n");
			imprimeTabuleiro(player1,1);
			scanf("%d %c",&pos,&L);
			kleber=L-65;
			pos=pos-1;
			while(validaEntradaLinhaColuna(pos,L)==0||podeAtirar(player1,pos,kleber)==0){
				printf("Posicao indisponivel!\n");
				scanf("%d %c",&pos,&L);
				kleber=L-65;
				pos=pos-1;
			}
			atirar(player1,pos,kleber);
			pts2+=calculaPontuacao(player1,pos,kleber);
			if(pontant1<pts2){
				printf("************************\n");
	 			printf("*\n");
	 			printf("* JOGADOR 2 DERRUBOU UM NAVIO!\n");
	 			printf("*\n");
	 			printf("************************\n");
				printf("\n");
				pontant1=pts2;
			}
		}
		jogadas++;

		}

		printf("************************\n");
	 	printf("*\n");
	 	printf("* FIM DE JOGO\n");
	 	printf("*\n");
	 	printf("************************\n");
		printf("************************\n");
	 	printf("*\n");
	 	printf("* PONTUACAO DO JOGADOR 1: %d\n",pts1);
		printf("* PONTUACAO DO JOGADOR 2: %d\n",pts2);
	 	printf("*\n");
	 	printf("************************\n");
	return 0;
}
//eu nao aguento maiss aaaaaa;
