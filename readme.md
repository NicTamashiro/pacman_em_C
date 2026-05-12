#  Foge Foge

Jogo estilo Pac-Man rodando no terminal, desenvolvido em C.

O jogador controla um herói que deve coletar pílulas e explodir os fantasmas antes de ser capturado.

---

## Como jogar

| Tecla | Ação |
|-------|------|
| `W` | Mover para cima |
| `S` | Mover para baixo |
| `A` | Mover para esquerda |
| `D` | Mover para direita |
| `B` | Detonar bomba (requer pílula) |

Colete a pílula `P` e pressione `B` para explodir os fantasmas ao redor. Cuidado — se um fantasma te alcançar, você perde!

---

## Compilação e execução

```bash
gcc fogefoge.c mapa.c ui.c -o fogefoge
./fogefoge
```

---

## Estrutura do projeto

```
.
├── fogefoge.c   # Lógica principal do jogo (movimento, fantasmas, explosão)
├── fogefoge.h
├── mapa.c       # Leitura, alocação e manipulação do mapa
├── mapa.h
├── ui.c         # Renderização do mapa no terminal
├── ui.h
└── mapa.txt     # Arquivo de mapa (editável)
```

---

## Formato do mapa

O mapa é lido de `mapa.txt`. A primeira linha define as dimensões (`linhas colunas`), seguida pela matriz de caracteres:

```
11 20
|------------------|
|.F...|...P...|..F.|
|.-.-.|.-----.|.-.-|
|.P...|.F..F.|.....|
|.--..|......|.....|
|.....|..@...|.....|
|.--..|......|.....|
|.F...|.F..P.|.....|
|.-.-.|.-----.|.-.-|
|.P..F|...P...|..F.|
|------------------|
```

| Caractere | Significado |
|-----------|-------------|
| `@` | Herói |
| `F` | Fantasma |
| `P` | Pílula |
| `.` | Espaço vazio |
| `\|` | Parede vertical |
| `-` | Parede horizontal |

O jogo suporta qualquer tamanho de mapa — basta editar `mapa.txt` e ajustar as dimensões na primeira linha.

---

## Destaques técnicos

- Alocação dinâmica da matriz com base nas dimensões lidas do arquivo
- Movimentação dos fantasmas por sorteio aleatório com até 10 tentativas por turno
- Explosão da pílula implementada recursivamente nas quatro direções
- Cópia do mapa a cada turno para evitar que fantasmas se movam duas vezes
- Sem vazamento de memória: toda memória alocada é liberada antes do encerramento