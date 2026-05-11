#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

// copia o conteúdo de um mapa origem para um mapa destino
// aloca nova memória para o destino e copia linha por linha
void copiamapa(MAPA* destino, MAPA* origem){
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;

    alocamapa(destino);
    for(int i = 0; i < origem->linhas; i++){
        strcpy(destino->matriz[i], origem->matriz[i]);
    }
}

// move um personagem de uma posição para outra no mapa
// coloca o personagem na posição destino e deixa a origem como vazio
void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino){
    char personagem = m->matriz[xorigem][yorigem];
    m->matriz[xdestino][ydestino] = personagem;
    m->matriz[xorigem][yorigem] = VAZIO;
}

int ehvalida(MAPA* m, int x, int y){
    if(x < 0) return 0;  
    if(y < 0) return 0;
    if(x >= m->linhas) return 0;
    if(y >= m->colunas) return 0;
    return 1;
}

int ehvazia(MAPA* m, int x, int y){
    return m->matriz[x][y] == VAZIO;
}

//percorre a matriz procurando o caractere 'c' quando acha, salva a posição (i, j) no struct 'p'
int encontramapa(MAPA* m, POSICAO* p, char c){
    for(int i = 0; i < m->linhas; i++){
        for(int j = 0; j < m->colunas; j++){
            if(m->matriz[i][j] == c){ 
                p->x = i;   // salva a linha
                p->y = j;   // salva a coluna
                return 1;
            }
        }
    }
    return 0;
}

int ehparede(MAPA* m, int x, int y){
    return m->matriz[x][y] == PAREDE_VERTICAL || m->matriz[x][y] == PAREDE_HORIZONTAL;
}

int ehpersonagem(MAPA* m, char personagem, int x, int y){
    return m->matriz[x][y] == personagem;
}

int podeandar(MAPA* m, char personagem, int x, int y){
    return ehvalida(m,x,y) && !ehparede(m,x,y) && !ehpersonagem(m, personagem, x, y);
}

void liberar_mapa(MAPA* m){
    for(int i = 0; i < m->linhas; i++){
        free(m->matriz[i]);     // libera cada linha 
    }
    free(m->matriz);            // libera o array de ponteiros
}

// aloca a matriz dinamicamente com base em linhas e colunas já preenchidos
void alocamapa(MAPA* m){
    m->matriz = malloc(sizeof(char*) * m->linhas);
    for(int i = 0; i < m->linhas; i++){
        m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1)); // +1 para o '\0'
    }
}

// abre o arquivo, lê dimensões, aloca e preenche a matriz
void lemapa(MAPA* m){
    
    FILE* f;
    f = fopen("mapa.txt", "r");
    if(f == 0){
        printf("Erro na leitura do mapa\n");
        exit(1);
    }

    fscanf(f, "%d %d", &(m->linhas), &(m->colunas));    // lê dimensões do mapa

    alocamapa(m);   // agora que sabe o tamanho, aloca a matriz

    for(int i = 0; i < m->linhas; i++){
        fscanf(f, "%s", m->matriz[i]);  // lê cada linha do mapa como string
    }

    fclose(f);
}