#ifndef PROD

#define PROD
#include"auxfunc.h"

Product searchProductByID(const char* id);
void readProductById();
void addProduct();
void modifyProductByID();
bool loadProducts(Product products[], int& productCount);
void displayProducts(Product products[], int productCount);
void sortProducts(Product products[], int productCount);
void listProducts();
#endif