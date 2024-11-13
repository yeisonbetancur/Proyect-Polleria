#ifndef PROD

#define PROD
#include"auxfunc.h"

Product searchProductByID(const char*);
void readProductById();
void addProduct();
void modifyProductByID();
bool loadProducts(Product[], int& );
void displayProducts(Product[], int );
void sortProducts(Product[], int );
void listProducts();
#endif