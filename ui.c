#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"
#include "ui.h"

void boasvindas(){
    printf("\n");
    printf("  +-+-+-+-+ +-+-+-+-+\n");
    printf("  |F|O|G|E| |F|O|G|E|\n");
    printf("  +-+-+-+-+ +-+-+-+-+\n");
    printf("\n");
    printf("   .-.        Aperte WASD para mover, B para bomba!\n");
    printf("  | OO|       Pegue a pilula (P) e exploda os fantasmas!\n");
    printf("  |   |       \n");
    printf("  '^^^'       Pressione ENTER para comecar...\n");
    printf("\n");
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void voceganhou(){
    printf("\n");
    printf("  +-+-+-+-+ +-+-+-+-+-+-+-+\n");
    printf("  |V|O|C|E| |G|A|N|H|O|U|!\n");
    printf("  +-+-+-+-+ +-+-+-+-+-+-+-+\n");
    printf("\n");
    printf("  Todos os fantasmas foram eliminados! Parabens!\n");
    printf("\n");
}

void voceperdeu(){
    printf("\n");
    printf("  +-+-+-+-+ +-+-+-+-+-+-+\n");
    printf("  |V|O|C|E| |P|E|R|D|E|U|\n");
    printf("  +-+-+-+-+ +-+-+-+-+-+-+\n");
    printf("\n");
    printf("  Um fantasma te pegou! Mais sorte da proxima vez...\n");
    printf("\n");
}

char desenhofantasma[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char desenhoparede[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char desenhoheroi[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char desenhopilula[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char desenhovazio[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void imprimeparte(char desenho[4][7], int parte){
    printf("%s", desenho[parte]);
}

void imprimemapa(MAPA* m){
    for(int i = 0; i < m->linhas; i++){

        for(int parte = 0; parte < 4; parte++){
            for(int j = 0; j < m->colunas; j++){
                switch(m->matriz[i][j]){
                    case FANTASMA:
                        imprimeparte(desenhofantasma, parte);
                        break;
                    case HEROI:
                        imprimeparte(desenhoheroi, parte);
                        break;
                    case PILULA:
                        imprimeparte(desenhopilula, parte);
                        break;
                    case PAREDE_VERTICAL:
                    case PAREDE_HORIZONTAL:
                        imprimeparte(desenhoparede, parte);
                        break;
                    case VAZIO:
                        imprimeparte(desenhovazio, parte);
                        break;
                }
            }
            printf("\n");
        }
    }
}