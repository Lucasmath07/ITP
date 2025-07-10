#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Cor{
    private:
    int R,G,B;

    public:
    Cor() : R(0), G(0), B(0){} //construtor padrão
    Cor(int r,int g, int b) : R(r), G(g), B(b){}  //construtor para receber valores rgb

    int getR() const { return R; }
    int getG() const { return G; }
    int getB() const { return B; }

    void imprimirCor(){
        cout << "(" << R << ", " << G << ", " << B << ")";
    }

};

class Paleta{
    private:
    int quantidade;
    Cor cores[100];
    double valores[100];

    public:
    Paleta(){
        quantidade = 0;
    }
    Paleta(int qtd, Cor c[],double v[]){
        quantidade = qtd;
        for(int i = 0; i< quantidade; i++){
            cores[i] = c[i];
            valores[i] = v[i];
        }
    }
    bool lerArquivo(string nomeArquivo){
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo: " << nomeArquivo << endl;
        return false;
    }

    arquivo >> quantidade;

    for (int i = 0; i < quantidade; i++) {
        int r, g, b;
        arquivo >> valores[i] >> r >> g >> b;
        cores[i] = Cor(r, g, b);
    }

    arquivo.close();
    return true;
}

    Cor consultarCor(double valor){
        for(int i =0;i<quantidade;i++){
            if(valor == valores[i]){
                return cores[i];
            }
        }
        cout << "Valor não encontrado!\n";
        return Cor();
}
};

class Imagem {
private:
    int Largura, Altura;
    Cor pixel[1][3]; // imagem 1x3 fixa

public:
    // Construtor fixo para imagem 1x3
    Imagem() : Largura(3), Altura(1) {
        for (int i = 0; i < Altura; i++) {
            for (int j = 0; j < Largura; j++) {
                pixel[i][j] = Cor(0, 0, 0); // preto por padrão
            }
        }
    }

    // Define um pixel
    void setPixel(int linha, int coluna, Cor cor) {
        if (linha == 0 && coluna >= 0 && coluna < 3) {
            pixel[linha][coluna] = cor;
        }
    }

    // Retorna um pixel
    Cor getPixel(int linha, int coluna) {
        if (linha == 0 && coluna >= 0 && coluna < 3) {
            return pixel[linha][coluna];
        }
        return Cor();
    }

    // Salvar no formato PPM
    void salvar(string nomeArquivo) {
        ofstream arquivo(nomeArquivo);
        if (!arquivo.is_open()) {
            cout << "Erro ao4245 abrir o arquivo para salvar\n";
            return;
        }

        arquivo << "P3\n";
        arquivo << Largura << " " << Altura << "\n";
        arquivo << "255\n";

        for (int i = 0; i < Altura; ++i) {
            for (int j = 0; j < Largura; ++j) {
                Cor c = pixel[i][j];
                arquivo << c.getR() << " " << c.getG() << " " << c.getB() << " ";
            }
            arquivo << "\n";
        }

        arquivo.close();
    }
};


int main() {
    Paleta p;
    double val;
    if (p.lerArquivo("teste.txt")) {
        Imagem img;

        cout << "Digite 3 valores (entre os que estão no arquivo) para os 3 pixels da imagem 1x3:\n";
        for (int i = 0; i < 3; i++) {
            cout << "Pixel " << i << ": ";
            cin >> val;
            Cor cor = p.consultarCor(val);
            img.setPixel(0, i, cor);  // Linha 0, coluna i
        }

        img.salvar("saida.ppm");
        cout << "Imagem salva como 'saida.ppm'\n";
    } else {
        cout << "Erro na leitura!\n";
        cout << "Arquivo não foi lido.\n";
    }

    return 0;
}
