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
