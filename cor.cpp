// Cor.h
#ifndef COR_H
#define COR_H

// Estrutura para representar uma cor no formato RGB.
// Cada componente de cor é um valor entre 0 e 255.
struct Cor {
    unsigned char r, g, b;

    // Construtor padrão que inicializa a cor como preto.
    Cor() : r(0), g(0), b(0) {}

    // Construtor que inicializa a cor com valores específicos.
    Cor(unsigned char red, unsigned char green, unsigned char blue) : r(red), g(green), b(blue) {}
};

#endif // COR_H
