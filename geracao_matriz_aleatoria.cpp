#include <iostream>
#include <ctime>
#include <iomanip>
#include <cmath>
using namespace std;

const int tam = 5.0;  // Deve ser 2^n + 1, elinha: 5 = 2^2 + 1

double aleatorio() {
    double a = static_cast<double>(rand()) / RAND_MAX;//deixa entre 0 e 1
   // a = round(a * 100.0) / 100.0; //deixa com apenas duas casa decimais depois do ponto
    return a;
}

// Diamond Step
void diamond(double mat[tam][tam], int linha, int coluna, int tamanho) {
    int pontocentral = tamanho / 2;
    double media = (
        mat[linha][coluna] +
        mat[linha + tamanho][coluna] +
        mat[linha][coluna + tamanho] +
        mat[linha + tamanho][coluna + tamanho]
    ) / 4;
    mat[linha + pontocentral][coluna + pontocentral] = media + aleatorio()*0.9; // variação aleatória
}

// Square Step

void square(double mat[tam][tam], int linha, int coluna, int tamanho) {
    int meio   = tamanho / 2;
    int l_meio = linha  + meio;
    int c_meio = coluna + meio;

    //aresta de cima
    if (linha >= 0 && c_meio < tam) {
        
        double canto_esq  = mat[linha][coluna];
        double canto_dir  = mat[linha][coluna + tamanho];
        mat[linha][c_meio] = (canto_esq + canto_dir) / 2;
    }

    //aresta de baixo
    if (linha + tamanho < tam && c_meio < tam) {
        double canto_esq  = mat[linha + tamanho][coluna];
        double canto_dir  = mat[linha + tamanho][coluna + tamanho];
        mat[linha + tamanho][c_meio] = (canto_esq + canto_dir) / 2;
    }

    //Aresta da esquerda
    if (coluna >= 0 && l_meio < tam) {
        double canto_cima = mat[linha][coluna];
        double canto_baixo = mat[linha + tamanho][coluna];
        mat[l_meio][coluna] = (canto_cima + canto_baixo) / 2;
    }

    //aresta da direita
    if (coluna + tamanho < tam && l_meio < tam) {
        double canto_cima = mat[linha][coluna + tamanho];
        double canto_baixo = mat[linha + tamanho][coluna + tamanho];
        mat[l_meio][coluna + tamanho] = (canto_cima + canto_baixo) / 2;
    }

}

void printMatrilinha(double mat[tam][tam]) {
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            cout.width(3);
            cout << mat[i][j] << "     ";
        }
        cout << endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));     // semente única
   

    double mat[tam][tam] = {0};

    // Define os 4 cantos com valores aleatórios
    mat[0][0] = aleatorio();
    mat[0][tam - 1] = aleatorio();
    mat[tam - 1][0] = aleatorio();
    mat[tam - 1][tam - 1] = aleatorio();

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

        tamanho = tamanho / 2;
       
        
    }

    cout << "Matriz gerada pelo algoritmo Diamond-Square:\n";
    printMatrilinha(mat);

    return 0;
}
