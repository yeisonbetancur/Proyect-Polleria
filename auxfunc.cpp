#include<iostream>
#include<fstream>
#include<ctime>
#include<cstring>
#include<vector>
#include<algorithm>
#include <limits>
#include"auxfunc.h"
using namespace std;

bool checkBool(int x){
    if(x!=1&&x!=0){
        return false;
    }else return true;
}

bool discountCheck(int x){
    if(x<=99&&x>=0){
        return true;
    }else return false;
}

bool checkId(const char* id) {
    ifstream archivo("products.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    Product product;
    while (archivo.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        if (strcmp(product.id, id) == 0) {
            cerr<<"El ID ya esta registrado";
            return false;
        }
    }
    cout<<"\nSe registro con exito el id";
    archivo.close();
    return true;
}
bool checkBillId(const char* id) {
    ifstream archivo("bills.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return false;
    }

    Bill bill;
    while (archivo.read(reinterpret_cast<char*>(&bill), sizeof(Bill))) {
        if (strcmp(bill.id, id) == 0) {
            cerr<<"El ID ya esta registrado";
            return false;
        }
    }
    cout<<"\nSe registro con exito el id";
    archivo.close();
    return true;
}

double calculateTotal(Bill bill) {
    double total = 0;
    for (int i = 0; i < 20; i++) {
        if (bill.productId[i][0] == '\0') {
            break;
        }
        Product product = searchProductByID(bill.productId[i]);
        if (product.price > 0) {
            total += product.price * bill.amountProduct[i];
        }
    }
    total-=total*(bill.discount/100.0);
    return total;
}
