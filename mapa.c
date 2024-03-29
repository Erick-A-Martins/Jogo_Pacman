#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

void copiamapa(MAPA* destino, MAPA* origem) {
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;

    alocamapa(destino);
    for(int i = 0; i < origem->linhas; i++) {
        strcpy(destino->matrizmapa[i], origem->matrizmapa[i]);
    }
}

void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino) {
    char personagem = m->matrizmapa[xorigem][yorigem];
    m->matrizmapa[xdestino][ydestino] = personagem;
    m->matrizmapa[xorigem][yorigem] = VAZIO;
}

int ehvalida(MAPA* m, int x, int y) {
    if(x >= m->linhas) {
        return 0;
    }
    if(y >= m->colunas) {
        return 0;
    }
    return 1;
}

int ehvazia(MAPA* m, int x, int y) {
    return m->matrizmapa[x][y] == VAZIO;
}

int ehparede(MAPA* m, int x, int y) {
    return m->matrizmapa[x][y] == PAREDE_VERTICAL || m->matrizmapa[x][y] == PAREDE_HORIZONTAL;
}

int ehpersonagem(MAPA* m, char personagem, int x, int y) {
    return m->matrizmapa[x][y] == personagem;
}

int podeandar(MAPA* m, char personagem, int x, int y) {
    return ehvalida(m, x, y) && !ehparede(m, x, y) && !ehpersonagem(m, personagem, x, y);
}

int encontramapa(MAPA* m, POSICAO* p, char c) {
    // Descobre a direção do herói e armazena nas variaveis X e Y
    for(int i = 0; i < m->linhas; i++) {
        for(int j = 0; j < m->colunas; j++) {
            if(m->matrizmapa[i][j] == c) {
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }
    return 0;
}

void liberamapa(MAPA* m) { // Ponteiro de struct
    for(int i = 0; i < m->linhas; i++) {
        free(m->matrizmapa[i]);
    }
    free(m->matrizmapa);    
}

void alocamapa(MAPA* m) {
    m->matrizmapa = malloc(sizeof(char*) * m->linhas);
    for(int i = 0; i < m->linhas; i++) {
        m->matrizmapa[i] = malloc(sizeof(char) * (m->colunas+1)); 
    }
}

void lemapa(MAPA* m) {

    FILE* f;

    f = fopen("mapa.txt", "r");
    if (f == 0) {
        printf("Erro na leitura do mapa\n");
        exit(1);
    }

    fscanf(f, "%d %d", &(m->linhas), &(m->colunas));

    // Alocação Dinâmica
    alocamapa(m);
    // Fim alocação dinâmica

    for(int i = 0; i < m->linhas; i++) {
        fscanf(f, "%s", m->matrizmapa[i]);
    }
    fclose(f);

}

/*

Exemplo de mapa alternativo para jogar
6 10
|--------|
|FFF|....|
|........|
|FF...@|.|
|..F...|.|
|--------|

*/