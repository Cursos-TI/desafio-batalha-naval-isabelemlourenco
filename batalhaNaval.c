#include <stdio.h>

// Zera o tabuleiro (tudo vira água)
void zerarTabuleiro(int tabuleiro[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            tabuleiro[i][j] = 0;
}

// Verifica se a posição do navio é válida
int validarPosicao(int tabuleiro[10][10], int linha, int coluna, int tamanho, int tipo) {
    // Tipo: 0=horizontal, 1=vertical, 2=diagonal crescente, 3=diagonal decrescente
    for (int i = 0; i < tamanho; i++) {
        int l, c;
        if (tipo == 0) { // Horizontal
            l = linha;
            c = coluna + i;
        } else if (tipo == 1) { // Vertical
            l = linha + i;
            c = coluna;
        } else if (tipo == 2) { // Diagonal crescente
            l = linha + i;
            c = coluna + i;
        } else { // Diagonal decrescente
            l = linha - i;
            c = coluna + i;
        }
        // Checa se está fora do tabuleiro ou se já tem navio
        if (l < 0 || l >= 10 || c < 0 || c >= 10 || tabuleiro[l][c] != 0)
            return 0;
    }
    return 1;
}

// Posiciona navio horizontal
void posicionarNavioHorizontal(int tabuleiro[10][10], int navio[3], int linha, int coluna) {
    for (int i = 0; i < 3; i++)
        tabuleiro[linha][coluna + i] = navio[i];
}

// Posiciona navio vertical
void posicionarNavioVertical(int tabuleiro[10][10], int navio[3], int linha, int coluna) {
    for (int i = 0; i < 3; i++)
        tabuleiro[linha + i][coluna] = navio[i];
}

// Posiciona navio diagonal crescente
void posicionarNavioDiagonalCrescente(int tabuleiro[10][10], int navio[3], int linha, int coluna) {
    for (int i = 0; i < 3; i++)
        tabuleiro[linha + i][coluna + i] = navio[i];
}

// Posiciona navio diagonal decrescente
void posicionarNavioDiagonalDecrescente(int tabuleiro[10][10], int navio[3], int linha, int coluna) {
    for (int i = 0; i < 3; i++)
        tabuleiro[linha - i][coluna + i] = navio[i];
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
    // Arrays para os navios (tamanho 3, valor 3)
    int navioHorizontal[3] = {3, 3, 3};
    int navioVertical[3] = {3, 3, 3};
    int navioDiagonalCrescente[3] = {3, 3, 3};
    int navioDiagonalDecrescente[3] = {3, 3, 3};
    
    // Zera o tabuleiro
    zerarTabuleiro(tabuleiro);
    
    // Navio horizontal em D3-D5 (linha 2, coluna 3)
    if (validarPosicao(tabuleiro, 2, 3, 3, 0)) {
        posicionarNavioHorizontal(tabuleiro, navioHorizontal, 2, 3);
    } else {
        printf("Erro: Navio horizontal inválido!\n");
        return 1;
    }
    
    // Navio vertical em H7-H9 (linha 6, coluna 7)
    if (validarPosicao(tabuleiro, 6, 7, 3, 1)) {
        posicionarNavioVertical(tabuleiro, navioVertical, 6, 7);
    } else {
        printf("Erro: Navio vertical inválido!\n");
        return 1;
    }
    
    // Navio diagonal crescente em B2-C3-D4 (linha 1, coluna 1)
    if (validarPosicao(tabuleiro, 1, 1, 3, 2)) {
        posicionarNavioDiagonalCrescente(tabuleiro, navioDiagonalCrescente, 1, 1);
    } else {
        printf("Erro: Navio diagonal crescente inválido!\n");
        return 1;
    }
    
    // Navio diagonal decrescente em J1-I2-H3 (linha 9, coluna 0)
    if (validarPosicao(tabuleiro, 9, 0, 3, 3)) {
        posicionarNavioDiagonalDecrescente(tabuleiro, navioDiagonalDecrescente, 9, 0);
    } else {
        printf("Erro: Navio diagonal decrescente inválido!\n");
        return 1;
    }
    
    // Mostra o tabuleiro
    mostrarTabuleiro(tabuleiro);
    
    return 0;
}