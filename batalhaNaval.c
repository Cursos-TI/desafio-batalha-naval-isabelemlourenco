#include <stdio.h>

// Zera o tabuleiro (tudo vira água)
void zerarTabuleiro(int tabuleiro[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            tabuleiro[i][j] = 0;
}

// Posiciona navio horizontal a partir de uma linha e coluna
void posicionarNavioHorizontal(int tabuleiro[10][10], int navio[3], int linha, int coluna) {
    for (int i = 0; i < 3; i++) {
        tabuleiro[linha][coluna + i] = navio[i]; // Copia o navio pro tabuleiro
    }
}

// Posiciona navio vertical a partir de uma linha e coluna
void posicionarNavioVertical(int tabuleiro[10][10], int navio[3], int linha, int coluna) {
    for (int i = 0; i < 3; i++) {
        tabuleiro[linha + i][coluna] = navio[i]; // Copia o navio pro tabuleiro
    }
}

// Mostra o tabuleiro
void mostrarTabuleiro(int tabuleiro[10][10]) {
    printf("   A B C D E F G H I J\n");
    for (int i = 0; i < 10; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < 10; j++)
            printf("%d ", tabuleiro[i][j]);
        printf("\n");
    }
}

int main() {
    int tabuleiro[10][10];
    int navioHorizontal[3] = {3, 3, 3};
    int navioVertical[3] = {3, 3, 3};
    
    // Zera o tabuleiro
    zerarTabuleiro(tabuleiro);
    
    // Coloca navio horizontal em D3-D5 (linha 2, coluna 3)
    posicionarNavioHorizontal(tabuleiro, navioHorizontal, 2, 3);
    
    // Coloca navio vertical em H7-H9 (linha 6, coluna 7)
    posicionarNavioVertical(tabuleiro, navioVertical, 6, 7);
    
    // Mostra o tabuleiro
    mostrarTabuleiro(tabuleiro);
    
    return 0;
}