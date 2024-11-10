#include "auxfunc.h"
#include<iostream>
#include<fstream>
#include<ctime>
#include<cstring>
#include<vector>
#include<algorithm>
#include <limits>
using namespace std;

Product searchProductByID(const char* id) {
    Product product={};
    ifstream archivo("products.dat", ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return product ;
    }

    while (archivo.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        if (strcmp(product.id, id) == 0) {
            archivo.close();
            return product;
        }
    }
    archivo.close();
    return product;
}

  void readProductById(){
  	char id[20];
  	cout<<"Ingresa el ID ";
  	cin.ignore(numeric_limits<streamsize>::max(), '\n');
  	cin.getline(id,20);
  	Product product=searchProductByID(id);
  	if(product.id[0] != '\0'&& strcmp(product.id, id)==0){
    	cout <<"\nProducto encontrado:\n";
            cout <<"ID: "<<product.id<<"\n";
            cout <<"Nombre: "<<product.name<<"\n";
            cout <<"Precio: $"<<product.price<<"\n";
        }else{
        	cout<<"No se encontro el producto,"<<product.id[0];
		}
	}
	
void addProduct(){
	Product product;
	ofstream file("products.dat",ios::binary | ios::app);
	if (!file){
		cerr<<"No se pudo abrir el archivo product.dat";
		return ;
	}
	cout << "Ingresa el ID (debe ser unico): ";
    cin >> product.id;
    
    if (!checkId(product.id)) {
        cerr << "El ID ya existe. Intenta con otro ID." << endl;
        return;
    }
	cout<<"Ingresa el nombre del producto (maximo 30 caracteres)";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.getline(product.name, 30);
	cout << "Ingresa el precio unitario del producto: ";
	while (!(cin >> product.price)) {
    	cin.clear();
    	cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    	cout << "Entrada invalida. Ingresa un n�mero valido para el precio: ";
	}
	file.write(reinterpret_cast<const char*>(&product), sizeof(Product));
	file.close();
	cout<<"Producto ingresado correctamente\n";

}

void modifyProductByID() {
	char id[20];
  	cout<<"Ingresa el ID ";
  	cin.ignore(numeric_limits<streamsize>::max(), '\n');
  	cin.getline(id,20);
    fstream archivo("products.dat", ios::binary | ios::in | ios::out);
    
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    Product product;
    while (archivo.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        if (strcmp(product.id, id) == 0) {
            cout << "\nProducto encontrado!";
            cout << "\nIngresa el nuevo nombre del producto: ";
            cin.getline(product.name, 30);
            cout << "Ingresa el nuevo precio del producto: ";
            cin >> product.price;
            archivo.seekp(-static_cast<int>(sizeof(Product)), ios::cur);
            archivo.write(reinterpret_cast<const char*>(&product), sizeof(Product));
            archivo.close();
            cout << "Producto modificado con �xito." << endl;

        }
    }

    archivo.close();
    cout << "No se encontr� el producto con el ID: " << id << endl;

}

bool loadProducts(Product products[], int& productCount) {
    ifstream file("products.dat", ios::binary);
    if (!file) {
        cerr << "Error al abrir el archivo products.dat" << endl;
        return false;
    }

    Product product;
    productCount = 0;
    while (file.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        products[productCount++] = product;
    }

    file.close();
    return true;
}
void displayProducts(Product products[], int productCount){
    for (int i = 0; i < productCount; i++) {
        cout << "ID: " << products[i].id << ", Nombre: " << products[i].name << ", Precio: $" << products[i].price << endl;
    }
}
void sortProducts(Product products[], int productCount) {
    for (int i = 0; i < productCount - 1; i++) {
        for (int j = i + 1; j < productCount; j++) {
            if (strcmp(products[i].id, products[j].id) > 0) {
                Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
}

void listProducts(){
	 const int MAX_PRODUCTS = 100;
    Product products[MAX_PRODUCTS];
    int productCount = 0;
    if (!loadProducts(products, productCount)) {
        return; 
    }

    sortProducts(products, productCount);

    cout << "Lista de productos ordenada por ID (de menor a mayor):" << endl;
    displayProducts(products, productCount);

    return ;
}
