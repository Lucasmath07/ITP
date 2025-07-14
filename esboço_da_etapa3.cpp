#include <iostream>
#include <random>
using namespace std;

const int tam = 5;  // Tamanho da matriz (deve ser 2^n + 1 para funcionar com diamond-square)

int aleatorio() {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 99);
    return dist(mt);
}

// Etapa diamond - calcula o centro do quadrado
void diamond(int mat[tam][tam], int x1, int y1, int x2, int y2) {
    int cx = (x1 + x2) / 2;
    int cy = (y1 + y2) / 2;
    int media = (mat[x1][y1] + mat[x1][y2] + mat[x2][y1] + mat[x2][y2]) / 4;
    mat[cx][cy] = media;
}

// Etapa square - calcula os centros dos lados
void square(int mat[tam][tam], int x1, int y1, int x2, int y2) {
    int cx = (x1 + x2) / 2;
    int cy = (y1 + y2) / 2;

    // Cima
    mat[x1][cy] = (mat[x1][y1] + mat[x1][y2] + mat[cx][cy]) / 3;
    // Baixo
    mat[x2][cy] = (mat[x2][y1] + mat[x2][y2] + mat[cx][cy]) / 3;
    // Esquerda
    mat[cx][y1] = (mat[x1][y1] + mat[x2][y1] + mat[cx][cy]) / 3;
    // Direita
    mat[cx][y2] = (mat[x1][y2] + mat[x2][y2] + mat[cx][cy]) / 3;
}

void printMatrix(int mat[tam][tam]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
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
    mat[0][N-1] = aleatorio();
    mat[N-1][0] = aleatorio();
    mat[N-1][N-1] = aleatorio();

    // Passo 1: Diamond
    diamond(mat, 0, 0, N-1, N-1);

    // Passo 2: Square
    square(mat, 0, 0, N-1, N-1);

    // Impressão
    cout << "Matriz gerada pelo algoritmo Diamond-Square:\n";
    printMatrix(mat);

    return 0;
}
