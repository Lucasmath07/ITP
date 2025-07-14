#include <iostream>
#include <ctime>
using namespace std;

const int tam = 5;  // Deve ser 2^n + 1, elinha: 5 = 2^2 + 1

int aleatorio() {
    srand(time(NULL));
    return rand()/100;
}

// Diamond Step
void diamond(int mat[tam][tam], int linha, int coluna, int tamanho) {
    int pontocentral = tamanho / 2;
    int media = (
        mat[linha][coluna] +
        mat[linha + tamanho][coluna] +
        mat[linha][coluna + tamanho] +
        mat[linha + tamanho][coluna + tamanho]
    ) / 4;
    mat[linha + pontocentral][coluna + pontocentral] = media + aleatorio()*0.9; // variação aleatória
}

// Square Step
void square(int mat[tam][tam], int linha, int coluna, int tamanho) {
    int pontocentral = tamanho / 2;
    int linhacentro = linha + pontocentral;
    int colunacentro= coluna + pontocentral;

    // Cima
    if (linha >= 0 && colunacentro< tam) //delimita para não ir para indices fora da matriz
        mat[linha][colunacentro] = (mat[linha][coluna] + mat[linha][coluna + tamanho] + mat[linha + pontocentral][coluna + pontocentral]) / 3;

    // Bailinhao
    if (linha + tamanho < tam && colunacentro< tam)
        mat[linha + tamanho][colunacentro] = (mat[linha + tamanho][coluna] + mat[linha + tamanho][coluna + tamanho] + mat[linha + pontocentral][coluna + pontocentral]) / 3;

    // Esquerda
    if (coluna >= 0 && linhacentro < tam)
        mat[linhacentro][coluna] = (mat[linha][coluna] + mat[linha + tamanho][coluna] + mat[linha + pontocentral][coluna + pontocentral]) / 3;

    // Direita
    if (coluna + tamanho < tam && linhacentro < tam)
        mat[linhacentro][coluna + tamanho] = (mat[linha][coluna + tamanho] + mat[linha + tamanho][coluna + tamanho] + mat[linha + pontocentral][coluna + pontocentral]) / 3;
}

void printMatrilinha(int mat[tam][tam]) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            cout.width(3);
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int mat[tam][tam] = {0};

    // Define os 4 cantos com valores aleatórios
    mat[0][0] = aleatorio();
    mat[0][tam - 1] = aleatorio()-1;
    mat[tam - 1][0] = aleatorio()+1;
    mat[tam - 1][tam - 1] = aleatorio()-2;

    int tamanho = tam - 1;

    while (tamanho > 1) {
        int pontocentral = tamanho / 2;

        // Aplicar diamond em todos os quadrados
        for (int i = 0; i < tam - 1; i += tamanho) {
            for (int j = 0; j < tam - 1; j += tamanho) {
                diamond(mat, i, j, tamanho);
                printMatrilinha(mat);
                cout << "\n\n";
            }
        }

        // Aplicar square em todos os losangos
        for (int i = 0; i < tam - 1; i += tamanho) {
            for (int j = 0; j < tam - 1; j += tamanho) {
                square(mat, i, j, tamanho);
                printMatrilinha(mat);
                cout << "\n\n";
            }
        }

        tamanho /= 2;
       
        
    }

    cout << "Matriz gerada pelo algoritmo Diamond-Square:\n";
    printMatrilinha(mat);

    return 0;
}
