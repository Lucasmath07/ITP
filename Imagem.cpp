#include <iostream>
#include "paleta.cpp"
#include "cor.h";

using namespace std;

class Imagem{

    private:
    int const Largura, Altura;
    Cor pixel[Altura][Largura];
    public:
    Imagem(){
        Largura = 0;
        Altura = 0;
        pixel();
    }
};

int main(){
    return 0;
}
