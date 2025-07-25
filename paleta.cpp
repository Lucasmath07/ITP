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

        if(!arquivo.is_open()){
            cout << "Erro ao abrir arquivo\n";
        }
        arquivo >> quantidade;
        for(int i = 0; i < quantidade; i++){
            int r,g,b;

            arquivo >> valores[i] >> r >> g >> b;

            Cor leitura(r,g,b);

            cores[i] = leitura;

           
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

int main(){
    Paleta p;
    double val;
    if(p.lerArquivo("teste.txt")){
        cout << "Digite o valor que deseja verificar:\n";
        cin >> val;
        Cor resultado = p.consultarCor(val);
        cout << "Cor correspondente: ";
        resultado.imprimirCor();
        cout << endl;
    }
    else{
        cout << "Erro na leitura!\n";
        cout << "Arquivo não foi lido.\n";
    }

    return 0;
}
