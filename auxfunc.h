#ifndef AUXF

#define AUXF
#include<ctime>
struct Product{
	char id[20];
	char name[30];
	double price;
};
struct Bill{
	char id[20];
	tm* date;
	char productId[20][20];
	int amountProduct[20];
	bool delivery;
	char direction[20];
	int discount;
	double totalPrice;
};
// Declaración de una función simple
#endif
