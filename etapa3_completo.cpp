#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

class MapaAltitudes {
private:
    int** matriz;
    int tamanho;
    int linhas;
    int colunas;

    double rugosidade;

    int aleatorio(double escala) {
        return static_cast<int>((rand() / (double)RAND_MAX) * 2 * escala - escala);
    }

    void etapaDiamond(int lin, int col, int tam, double escala) {
        int meio = tam / 2;
        int media = (
            matriz[lin][col] +
            matriz[lin + tam][col] +
            matriz[lin][col + tam] +
            matriz[lin + tam][col + tam]
        ) / 4;

        matriz[lin + meio][col + meio] = media + aleatorio(escala);
    }

    void etapaSquare(int lin, int col, int tam, double escala) {
        int meio = tam / 2;
        int centroLin = lin + meio;
        int centroCol = col + meio;

        // cima
        if (lin >= 0)
            matriz[lin][centroCol] = (
                matriz[lin][col] +
                matriz[lin][col + tam] +
                matriz[lin + meio][col + meio]
            ) / 3 + aleatorio(escala);

        // baixo
        if (lin + tam < tamanho)
            matriz[lin + tam][centroCol] = (
                matriz[lin + tam][col] +
                matriz[lin + tam][col + tam] +
                matriz[lin + meio][col + meio]
            ) / 3 + aleatorio(escala);

        // esquerda
        if (col >= 0)
            matriz[centroLin][col] = (
                matriz[lin][col] +
                matriz[lin + tam][col] +
                matriz[lin + meio][col + meio]
            ) / 3 + aleatorio(escala);

        // direita
        if (col + tam < tamanho)
            matriz[centroLin][col + tam] = (
                matriz[lin][col + tam] +
                matriz[lin + tam][col + tam] +
                matriz[lin + meio][col + meio]
            ) / 3 + aleatorio(escala);
    }

public:
    MapaAltitudes(int N, double rug) : rugosidade(rug) {
        tamanho = pow(2, N) + 1;
        linhas = tamanho;
        colunas = tamanho;

        matriz = new int*[linhas];
        for (int i = 0; i < linhas; ++i)
            matriz[i] = new int[colunas]{};

        // Inicializar cantos com valores aleatórios
        srand(time(nullptr));
        matriz[0][0] = rand() % 256;
        matriz[0][tamanho - 1] = rand() % 256;
        matriz[tamanho - 1][0] = rand() % 256;
        matriz[tamanho - 1][tamanho - 1] = rand() % 256;
    }

    ~MapaAltitudes() {
        for (int i = 0; i < linhas; ++i)
            delete[] matriz[i];
        delete[] matriz;
    }

    void gerarTerreno() {
        int passo = tamanho - 1;
        double escala = 128.0;

        while (passo > 1) {
            int meio = passo / 2;

            // Diamond
            for (int i = 0; i < tamanho - 1; i += passo) {
                for (int j = 0; j < tamanho - 1; j += passo) {
                    etapaDiamond(i, j, passo, escala);
                }
            }

            // Square
            for (int i = 0; i < tamanho - 1; i += passo) {
                for (int j = 0; j < tamanho - 1; j += passo) {
                    etapaSquare(i, j, passo, escala);
                }
            }

            passo /= 2;
            escala *= rugosidade;
        }
    }

    void imprimir() const {
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                cout << setw(4) << matriz[i][j] << " ";
            }
            cout << endl;
        }
    }

    int getAltura(int lin, int col) const {
        return matriz[lin][col];
    }

    int getLinhas() const {
        return linhas;
    }

    int getColunas() const {
        return colunas;
    }

    void salvarEmArquivo(const string& nome) const {
        ofstream arq(nome);
        if (!arq) {
            cerr << "Erro ao abrir o arquivo para escrita.\n";
            return;
        }

        arq << linhas << " " << colunas << "\n";
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                arq << matriz[i][j] << (j == colunas - 1 ? "" : " ");
            }
            arq << "\n";
        }

        arq.close();
    }

    void carregarDeArquivo(const string& nome) {
        ifstream arq(nome);
        if (!arq) {
            cerr << "Erro ao abrir o arquivo para leitura.\n";
            return;
        }

        int novasLinhas, novasColunas;
        arq >> novasLinhas >> novasColunas;

        // desalocar anterior
        for (int i = 0; i < linhas; ++i) delete[] matriz[i];
        delete[] matriz;

        linhas = novasLinhas;
        colunas = novasColunas;
        tamanho = linhas;

        matriz = new int*[linhas];
        for (int i = 0; i < linhas; ++i)
            matriz[i] = new int[colunas];

        for (int i = 0; i < linhas; ++i)
            for (int j = 0; j < colunas; ++j)
                arq >> matriz[i][j];

        arq.close();
    }
};

// Função main de teste
int main() {
    int N = 3;           // Define matriz 9x9
    double rug = 0.5;    // Fator de rugosidade

    MapaAltitudes mapa(N, rug);
    mapa.gerarTerreno();

    cout << "Mapa de Altitudes Gerado:\n";
    mapa.imprimir();

    mapa.salvarEmArquivo("altitudes.txt");

    // Testar leitura
    MapaAltitudes novoMapa(1, rug);
    novoMapa.carregarDeArquivo("altitudes.txt");
    cout << "\nMapa lido do arquivo:\n";
    novoMapa.imprimir();

    return 0;
}
