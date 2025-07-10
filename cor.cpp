// Cor.h
#ifndef COR_H
#define COR_H

class Cor{
    private:

    int R,G,B;

    public:

    Cor() : R(0), G(0), B(0){} //construtor padrão

    Cor(int r,int g, int b) : R(r), G(g), B(b){}  //construtor para receber valores rgb

    void imprimirCor(){

        cout << "(" << R << ", " << G << ", " << B << ")";

    }
#endif // COR_H
