#include <stdio.h>

// Zera o tabuleiro (tudo vira água)
void zerarTabuleiro(int tabuleiro[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            tabuleiro[i][j] = 0;
}

// Verifica se a posição do navio é válida
int validarPosicao(int tabuleiro[10][10], int linha, int coluna, int tamanho, int tipo) {
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

// Cria matriz de habilidade Cone (5x5)
void criarHabilidadeCone(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            habilidade[i][j] = 0;
    // Cone: linha 0 tem 1 posição, linha 1 tem 3, linha 2-4 têm 5
    habilidade[0][2] = 1; // Topo
    for (int j = 1; j <= 3; j++) habilidade[1][j] = 1; // Meio
    for (int j = 0; j < 5; j++) habilidade[2][j] = 1; // Base
    for (int j = 0; j < 5; j++) habilidade[3][j] = 1;
    for (int j = 0; j < 5; j++) habilidade[4][j] = 1;
}

// Cria matriz de habilidade Cruz (5x5)
void criarHabilidadeCruz(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            habilidade[i][j] = 0;
    // Cruz: linha e coluna do centro (2,2)
    for (int i = 0; i < 5; i++) habilidade[i][2] = 1; // Coluna central
    for (int j = 0; j < 5; j++) habilidade[2][j] = 1; // Linha central
}

// Cria matriz de habilidade Octaedro (5x5)
void criarHabilidadeOctaedro(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            habilidade[i][j] = 0;
    // Octaedro: losango centrado em (2,2)
    habilidade[2][2] = 1; // Centro
    habilidade[1][2] = 1; habilidade[3][2] = 1; // Cima e baixo
    habilidade[2][1] = 1; habilidade[2][3] = 1; // Esquerda e direita
    habilidade[1][1] = 1; habilidade[1][3] = 1; // Diagonais cima
    habilidade[3][1] = 1; habilidade[3][3] = 1; // Diagonais baixo
}

// Sobrepoe habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[10][10], int habilidade[5][5], int linhaCentro, int colunaCentro) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = linhaCentro - 2 + i; // Ajusta pro centro
                int colunaTab = colunaCentro - 2 + j;
                // Só marca se estiver dentro do tabuleiro e não for navio
                if (linhaTab >= 0 && linhaTab < 10 && colunaTab >= 0 && colunaTab < 10 && tabuleiro[linhaTab][colunaTab] != 3)
                    tabuleiro[linhaTab][colunaTab] = 5;
            }
        }
    }
}

// Mostra o tabuleiro com caracteres
void mostrarTabuleiro(int tabuleiro[10][10]) {
    printf("   A B C D E F G H I J\n");
    for (int i = 0; i < 10; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < 10; j++) {
            if (tabuleiro[i][j] == 0) printf(". "); // Água
            else if (tabuleiro[i][j] == 3) printf("N "); // Navio
            else printf("* "); // Habilidade
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[10][10];
    // Arrays para os navios
    int navioHorizontal[3] = {3, 3, 3};
    int navioVertical[3] = {3, 3, 3};
    int navioDiagonalCrescente[3] = {3, 3, 3};
    int navioDiagonalDecrescente[3] = {3, 3, 3};
    // Matrizes para habilidades
    int habilidadeCone[5][5], habilidadeCruz[5][5], habilidadeOctaedro[5][5];
    
    // Zera o tabuleiro
    zerarTabuleiro(tabuleiro);
    
    // Posiciona navios
    if (validarPosicao(tabuleiro, 2, 3, 3, 0))
        posicionarNavioHorizontal(tabuleiro, navioHorizontal, 2, 3);
    if (validarPosicao(tabuleiro, 6, 7, 3, 1))
        posicionarNavioVertical(tabuleiro, navioVertical, 6, 7);
    if (validarPosicao(tabuleiro, 1, 1, 3, 2))
        posicionarNavioDiagonalCrescente(tabuleiro, navioDiagonalCrescente, 1, 1);
    if (validarPosicao(tabuleiro, 9, 0, 3, 3))
        posicionarNavioDiagonalDecrescente(tabuleiro, navioDiagonalDecrescente, 9, 0);
    
    // Cria habilidades
    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);
    
    // Aplica habilidades
    aplicarHabilidade(tabuleiro, habilidadeCone, 4, 4); // Centro em E5
    aplicarHabilidade(tabuleiro, habilidadeCruz, 6, 2); // Centro em G3
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 2, 7); // Centro em C8
    
    // Mostra o tabuleiro
    mostrarTabuleiro(tabuleiro);
    
    return 0;
}