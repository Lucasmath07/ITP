#include <iostream>
#include <random>
#include <ctime>
#include <ctime>

using namespace std;


int aleatorio(){
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0,99);
    return dist(mt);
}



int main(){
    const int linha = 5;
    const int coluna= 5;

    int mat[linha][coluna]={0};
    mat[0][0] = aleatorio();
    mat[0][coluna-1] = aleatorio();
    mat[linha-1][0] = aleatorio();
    mat[linha-1][coluna-1] = aleatorio();

    for(int i = 0; i< 5; i++){
        for(int j = 0; j<5;j++){
            cout << mat[i][j] << " ";
        }
        cout  << endl;
    }
    
    for(int i = 5;i>2;){
        i = 5/2 + 1;
        for(int j = 5;j>2;){
            j = 5 / 2 + 1;
            mat[i][j] = aleatorio();

        }

    }
    for(int i = 0; i< 5; i++){
        for(int j = 0; j<5;j++){
            cout << mat[i][j] << " ";
        }
        cout  << endl;
    }

     

    return 0;
}
