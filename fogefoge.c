#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fogefoge.h"
#include "mapa.h"
#include "ui.h"

MAPA m; 
POSICAO heroi;
int tempilula = 0;  

int praondefantasmavai(int xatual, int yatual, int* xdestino, int* ydestino){
    int opcoes [4][2] = {
        { xatual, yatual + 1},  //  direita
        { xatual + 1, yatual},  //  baixo
        { xatual, yatual - 1},  //  esquerda
        { xatual - 1, yatual},  //  cima
    };

    for(int i = 0; i < 10; i++){    // Tenta até 10 vezes sortear uma direção válida para evitar que o fantasma trave o jogo
        int posicao = rand() % 4;

        if(podeandar(&m, FANTASMA,opcoes[posicao][0], opcoes[posicao][1])){     // [2][2]
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];

            return 1;
        }
    }
    return 0;
}

void fantasmas(){
    MAPA copia;

    copiamapa(&copia, &m);  

    for(int i = 0; i < m.linhas; i++){
        for(int j = 0; j < m.colunas; j++){
            
            if(copia.matriz[i][j] == FANTASMA){ // m.matriz[1][2]      m.matriz[3][2]
                
                int xdestino;
                int ydestino;

                int encontrou = praondefantasmavai(i, j, &xdestino, &ydestino);

                if (encontrou){
                    andanomapa(&m, i, j, xdestino, ydestino);
                }
                
            }

        }
    }
    liberar_mapa(&copia);
}

int acabou(){

    POSICAO pos;
    int fogefogemapa = encontramapa(&m, &pos, HEROI);
    return !fogefogemapa;
}

int morreu(){
    POSICAO pos;
    int fantasma = encontramapa(&m, &pos, FANTASMA);
    return !fantasma;
}

int ehdirecao(char direcao){
    return (direcao == 'a' ||
            direcao == 'w' ||
            direcao == 's' ||
            direcao == 'd');
}

void move(char direcao){

    if(!ehdirecao(direcao)) return;

    int proximoX = heroi.x;
    int proximoY = heroi.y;

    switch(direcao){
        case ESQUERDA:                              // esquerda
        proximoY--;
        break;
        case CIMA:                              // cima
        proximoX--;
        break;
        case BAIXO:                              // baixo
        proximoX++;
        break;
        case DIREITA:                              // direita
        proximoY++;
        break;
    }
    
    if(!podeandar(&m, HEROI,proximoX, proximoY)) return;

    if(ehpersonagem(&m, PILULA, proximoX, proximoY)){
        tempilula = 1;
    }

    andanomapa(&m, heroi.x, heroi.y, proximoX, proximoY);
    heroi.x = proximoX;
    heroi.y = proximoY;
}

void explodepilula(){

    if(!tempilula) return;

    explodepilula2(heroi.x, heroi.y, 0, 1, 3);  // →  direita
    explodepilula2(heroi.x, heroi.y, 0, -1, 3); // ←  esquerda
    explodepilula2(heroi.x, heroi.y, 1, 0, 3);  // ↓  baixo
    explodepilula2(heroi.x, heroi.y, -1, 0, 3); // ↑  cima

    tempilula = 0;
}

void explodepilula2(int x, int y, int somax, int somay,int qtd){

    if(qtd == 0) return;

    int novox = x + somax;
    int novoy = y + somay;

    if(!ehvalida(&m, novox, novoy)) return;
    if(ehparede(&m, novox, novoy)) return;

    m.matriz[novox][novoy] = VAZIO;
    explodepilula2(novox, novoy, somax, somay,qtd - 1);
}

int main(){

    srand(time(0));
    lemapa(&m);                        // le e aloca o mapa do arquivo
    encontramapa(&m, &heroi, HEROI); // encontra a posicao atual do heroi

    boasvindas();

    do{

        printf("Tem pilula: %s\n", (tempilula ? "SIM" : "NAO"));
        imprimemapa(&m);               // mostra o estado atual do mapa 

        char comando;
        scanf(" %c", &comando);
        move(comando);
        if(comando == BOMBA) explodepilula();
        fantasmas();

    } while(!acabou() && !morreu());

    if(morreu()) voceganhou();
    else voceperdeu();

    liberar_mapa(&m);                  // libera a memória antes de sair
}