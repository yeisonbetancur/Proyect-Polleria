#ifndef AUXF

#define AUXF

struct Product{
	char id[20];
	char name[30];
	double price;
};
Product searchProductByID(const char* id);
void readProductById();
void addProduct();
void modifyProductByID();
bool loadProducts(Product products[], int& productCount);
void displayProducts(Product products[], int productCount);
void sortProducts(Product products[], int productCount);
void listProducts();
#endif