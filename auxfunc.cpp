#include<iostream>
#include<fstream>
#include<ctime>
#include<cstring>
#include<vector>
#include<algorithm>
#include <limits>
#include"auxfunc.h"
using namespace std;

bool checkId(const char* id) {
    ifstream archivo("products.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return 0;
    }

    Product product;
    while (archivo.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        if (strcmp(product.id, id) == 0) {
            cerr<<"El ID ya esta registrado";
            return 0;
        }
    }
    cout<<"\nSe registro con exito el id";
    archivo.close();
    return 1;
}