#include <stdio.h>

#define TAM 10
#define NAVIO 3

int main() {
    int tabuleiro[TAM][TAM];
    int i, j;

    // Inicializa o tabuleiro com 0
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Posição inicial do navio horizontal
    int linhaH = 2;
    int colH = 4;

    // Coloca navio horizontal
    for (i = 0; i < NAVIO; i++) {
        tabuleiro[linhaH][colH + i] = 3;
    }

    // Posição inicial do navio vertical
    int linhaV = 5;
    int colV = 6;

    // Verifica se não sobrepõe
    int pode = 1;
    for (i = 0; i < NAVIO; i++) {
        if (tabuleiro[linhaV + i][colV] != 0) {
            pode = 0;
        }
    }

    if (pode) {
        for (i = 0; i < NAVIO; i++) {
            tabuleiro[linhaV + i][colV] = 3;
        }
    } else {
        printf("Navio vertical sobrepõe outro.\n");
        return 1;
    }

    // Mostra o tabuleiro
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
