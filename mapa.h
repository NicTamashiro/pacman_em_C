#ifndef _MAPA_H_
#define _MAPA_H_
#define HEROI '@'
#define VAZIO '.'
#define FANTASMA 'F'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define PILULA 'P'

struct mapa{
    char** matriz;
    int linhas;
    int colunas;
};

typedef struct mapa MAPA;

struct posicao {
    int x;
    int y;
};

typedef struct posicao POSICAO;

void liberar_mapa(MAPA* m);
void lemapa(MAPA* m);
void alocamapa(MAPA* m);
int encontramapa(MAPA* m, POSICAO* p, char c);
int ehvalida(MAPA* m, int x, int y);
void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino);
int ehvazia(MAPA* m, int x, int y);
void copiamapa(MAPA* destino, MAPA* origem);
int podeandar(MAPA* m, char personagem, int x, int y);
int ehpersonagem(MAPA* m, char personagem, int x, int y);
int ehparede(MAPA* m, int x, int y);

#endif