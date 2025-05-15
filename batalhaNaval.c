#include <stdio.h>
#include <stdlib.h> // para usar abs()

#define TAM 10      // Tamanho do tabuleiro
#define NAVIO 3     // Tamanho dos navios
#define HAB 5       // Tamanho das habilidades (5x5)

// Função que imprime o tabuleiro
void mostrarTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTABULEIRO:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0) printf("~ "); // Água
            else if (tabuleiro[i][j] == 3) printf("N "); // Navio
            else if (tabuleiro[i][j] == 5) printf("* "); // Habilidade
        }
        printf("\n");
    }
}

// Cria matriz em forma de cone (meio em cima, alargando embaixo)
void criarCone(int matriz[HAB][HAB]) {
    int meio = HAB / 2;
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (j >= meio - i && j <= meio + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz em forma de cruz (linha e coluna centrais)
void criarCruz(int matriz[HAB][HAB]) {
    int meio = HAB / 2;
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (i == meio || j == meio)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz em forma de octaedro (losango)
void criarOctaedro(int matriz[HAB][HAB]) {
    int meio = HAB / 2;
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (abs(meio - i) + abs(meio - j) <= meio)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica a habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int matriz[HAB][HAB], int origem_linha, int origem_coluna) {
    int centro = HAB / 2;

    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            int linhaTab = origem_linha - centro + i;
            int colTab = origem_coluna - centro + j;

            // Só aplica se estiver dentro do tabuleiro
            if (linhaTab >= 0 && linhaTab < TAM && colTab >= 0 && colTab < TAM) {
                if (matriz[i][j] == 1 && tabuleiro[linhaTab][colTab] != 3) {
                    tabuleiro[linhaTab][colTab] = 5;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int i, j;

    // Inicializa o tabuleiro com água (0)
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

    // Verifica se o navio vertical pode ser colocado (sem sobreposição)
    int pode = 1;
    for (i = 0; i < NAVIO; i++) {
        if (tabuleiro[linhaV + i][colV] != 0) {
            pode = 0;
        }
    }

    // Coloca navio vertical se puder
    if (pode) {
        for (i = 0; i < NAVIO; i++) {
            tabuleiro[linhaV + i][colV] = 3;
        }
    } else {
        printf("Navio vertical sobrepõe outro.\n");
        return 1;
    }

    // Criação das matrizes de habilidades
    int cone[HAB][HAB], cruz[HAB][HAB], octaedro[HAB][HAB];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Define ponto de origem das habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 1, 1);         // Cone na posição (1,1)
    aplicarHabilidade(tabuleiro, cruz, 5, 5);         // Cruz no centro
    aplicarHabilidade(tabuleiro, octaedro, 7, 2);     // Octaedro mais embaixo

    // Mostra o tabuleiro final com tudo
    mostrarTabuleiro(tabuleiro);

    return 0;
}
